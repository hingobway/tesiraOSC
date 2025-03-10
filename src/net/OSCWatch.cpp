#include "OSCWatch.h"

#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>

#include <osc/OscOutboundPacketStream.h>
#include <osc/OscReceivedElements.h>

OSCWatch::OSCWatch() : juce::Thread("OSCWatch")
{

  bool success = udp.bindToPort(PORT_OSC);
  if (!success)
  {
    DBG("[OSC] PORT BIND FAILED");
    return;
  }

  startThread();
}

OSCWatch::~OSCWatch()
{
  bool cleanExit = stopThread(THREAD_KILL_TIMEOUT_MS);
  if (!cleanExit)
    DBG("[OSC] WARNING: OSC was killed prematurely.");
}

void OSCWatch::run()
{
  juce::MessageManager::callAsync([]() { //
    DBG("[OSC] LISTENING on port " << PORT_OSC);
  });

  while (!threadShouldExit())
  {
    // wait for input
    int ready = udp.waitUntilReady(true, READ_WAIT_MS);
    if (ready == -1)
      DBG("[OSC] UDP ERROR");
    if (ready != 1)
      continue;

    // read message
    int bytesRead = udp.read(readBuffer, BUFFER_SIZE, false);
    std::string text{readBuffer};
    if (!text.length())
      continue;

    // PROCESS MESSAGE

    try
    {
      osc::ReceivedMessage msg(osc::ReceivedPacket(readBuffer, bytesRead));
      try
      {

        DBG("[OSC] COMMAND RECEIVED");

        auto command = std::string(msg.AddressPattern());

        // CHECK COMMAND
        if (command != OSC_COMMAND)
          continue;

        auto argb = msg.ArgumentsBegin();
        auto arge = msg.ArgumentsEnd();

        std::stringstream s{};
        for (auto it = argb; it != arge; ++it)
        {
          if (it->IsString())
            s << it->AsString() << " ";
          else if (it->IsInt32())
            s << it->AsInt32() << " ";
          else if (it->IsInt64())
            s << it->AsInt64() << " ";
          else if (it->IsFloat())
            s << it->AsFloat() << " ";
          else if (it->IsDouble())
            s << it->AsDouble() << " ";
        }
        auto output = s.str().substr(0, s.str().size() - 1);

        {
          if (onRunCommand)
            onRunCommand(output);
        }
      }
      catch (const osc::Exception &e)
      {
        juce::MessageManagerLock mml;
        DBG("[OSC] OSC PARSE ERROR: " << msg.AddressPattern() << ": " << e.what());
      }
    }
    catch (const osc::Exception &e)
    {
      juce::MessageManagerLock mml;
      DBG("[OSC] OSC ERROR: " << e.what());
    }
  }
}
