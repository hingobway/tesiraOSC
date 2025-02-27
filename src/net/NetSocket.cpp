#include "NetSocket.h"

#include <string>
#include <sstream>

#include <osc/OscOutboundPacketStream.h>
#include <osc/OscReceivedElements.h>

#define BUFFER_SIZE (1024)

NetSocket::NetSocket()
{
  // SETTINGS
  destination_ = "127.0.0.1";
  port_ = 53000;

  // TODO there should definitely be timeouts everywhere
}

NetSocket::~NetSocket()
{
  udp.shutdown();
  tcp.close();
}

bool NetSocket::connect(SocketType type)
{
  if (type == SocketType::UDP)
  {
    // prepare UDP
    udp.bindToPort(0);
    int ready = udp.waitUntilReady(false, -1);
    return ready == 1;
  }

  if (type == SocketType::TCP)
  {
    // prepare TCP
    bool success = tcp.connect(destination_, port_, 0);

    if (!success)
      return false;
    int ready = tcp.waitUntilReady(false, -1);
    return ready == 1;
  }

  return false;
}

bool NetSocket::send(SocketType type, const std::string &cmd)
{
  std::string msg{cmd + "\n"};
  return this->sendBytes(type, msg.c_str(), (int)msg.size());
}

bool NetSocket::send(SocketType type, const std::vector<unsigned char> &arr)
{
  return this->sendBytes(type, arr.data(), (int)arr.size());
}

bool NetSocket::sendBytes(SocketType type, const void *bytes, const int size)
{
  int written =
      (type == SocketType::UDP)
          ? udp.write(
                destination_, port_,
                bytes, size)
          : tcp.write(bytes, size);

  return written != -1;
}

// -------------------------------------------------

juce::String NetSocket::getSelectedCueNumber(SocketType type)
{

  bool success = connect(type);
  if (!success)
    jassertfalse;

  // send OSC packet
  char buf[BUFFER_SIZE];
  osc::OutboundPacketStream p(buf, BUFFER_SIZE);
  p << osc::BeginBundleImmediate;

  if (type == SocketType::UDP)
    p << osc::BeginMessage("/udpReplyPort")
      << udp.getBoundPort()
      << osc::EndMessage;

  p << osc::BeginMessage("/cue/selected/number")
    << osc::EndMessage;

  p << osc::EndBundle;

  this->sendBytes(type, p.Data(), (int)p.Size());

  // READ

  char readbuf[BUFFER_SIZE];

  while (true)

  {
    int ready = (type == SocketType::UDP) ? udp.waitUntilReady(true, -1)
                                          : tcp.waitUntilReady(true, -1);
    if (ready != 1)
      jassertfalse;

    int numread = (type == SocketType::UDP) ? udp.read(readbuf, BUFFER_SIZE, false)
                                            : tcp.read(readbuf, BUFFER_SIZE, false);

    std::string txt{readbuf};
    if (!txt.length())
    {
      continue;
    }

    // PROCESS

    try
    {
      osc::ReceivedMessage msg(osc::ReceivedPacket(readbuf, numread));
      try
      {

        auto command = std::string(msg.AddressPattern());

        // CHECK COMMAND
        if (command != "/reply/cue/selected/number")
          continue;

        // GET JSON STRING
        auto arg = msg.ArgumentsBegin();
        if (!arg->IsString())
          return "";

        // GET PARAMATER
        auto data = juce::JSON::parse(arg->AsString())
                        .getProperty("data", juce::var());
        if (!data.isString())
          return "";

        // return cue number
        return data.toString();
      }
      catch (const osc::Exception &e)
      {
        DBG("OSC PARSE ERROR: " << msg.AddressPattern() << ": " << e.what());
      }
    }
    catch (const osc::Exception &e)
    {
      DBG("OSC ERROR: " << e.what());
    }
  }
}
