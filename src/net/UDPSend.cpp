#include "UDPSend.h"

#include <string>
#include <sstream>

#include <osc/OscOutboundPacketStream.h>
#include <osc/OscReceivedElements.h>

#define BUFFER_SIZE (1024)

UDPSend::UDPSend() : socket()
{
  // SETTINGS
  destination_ = "127.0.0.1";
  port_ = 53000;

  // prepare socket
  socket.bindToPort(0);
  int ready = socket.waitUntilReady(false, -1);
  if (ready != 1)
    jassertfalse;

  // send OSC packet
  char buf[BUFFER_SIZE];
  osc::OutboundPacketStream p(buf, BUFFER_SIZE);
  p << osc::BeginBundleImmediate
    << osc::BeginMessage("/udpReplyPort")
    << socket.getBoundPort()
    << osc::EndMessage

    << osc::BeginMessage("/cue/selected/number")
    << osc::EndMessage
    << osc::EndBundle;

  this->sendBytes(p.Data(), (int)p.Size());

  // READ

  char readbuf[BUFFER_SIZE];

  ready = socket.waitUntilReady(true, -1);
  if (ready != 1)
    jassertfalse;
  int numread = socket.read(readbuf, BUFFER_SIZE, false);
  std::string txt{readbuf};
  if (!txt.length())
  {
    DBG("nothing");
    return;
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
        return;

      // GET JSON STRING
      auto arg = msg.ArgumentsBegin();
      if (!arg->IsString())
        return;

      // GET PARAMATER
      auto data = juce::JSON::parse(arg->AsString())
                      .getProperty("data", juce::var());
      if (!data.isString())
        return;

      // print cue number!
      DBG("GOT CUE NUMBER: " << data.toString());
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

UDPSend::~UDPSend()
{
  socket.shutdown();
}

bool UDPSend::send(const std::string &cmd)
{
  std::string msg{cmd + "\n"};
  return this->sendBytes(msg.c_str(), (int)msg.size());
}

bool UDPSend::send(const std::vector<unsigned char> &arr)
{
  return this->sendBytes(arr.data(), (int)arr.size());
}

bool UDPSend::sendBytes(const void *bytes, const int size)
{
  int written = socket.write(
      destination_, port_,
      bytes, size);

  return written != -1;
}
