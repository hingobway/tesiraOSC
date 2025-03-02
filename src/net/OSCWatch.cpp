#include "OSCWatch.h"

#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>

#include <osc/OscOutboundPacketStream.h>
#include <osc/OscReceivedElements.h>

OSCWatch::OSCWatch() : juce::Thread("OSCWatch")
{

  bool success = udp.bindToPort(OSC_PORT);
  if (!success)
  {
    DBG("PORT BIND FAILED");
    return;
  }

  this->startThread();
}

OSCWatch::~OSCWatch()
{
  bool cleanExit = stopThread(THREAD_KILL_TIMEOUT_MS);
  if (!cleanExit)
    DBG("WARNING: OSC was killed prematurely.");
}

void OSCWatch::run()
{

  while (!threadShouldExit())
  {
    // wait for input
    int ready = udp.waitUntilReady(true, READ_WAIT_MS);
    if (ready == -1)
      DBG("UDP ERROR");
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

        DBG("COMMAND RECEIVED");

        auto command = std::string(msg.AddressPattern());

        // CHECK COMMAND
        if (command != OSC_COMMAND)
          continue;

        auto argb = msg.ArgumentsBegin();
        auto arge = msg.ArgumentsEnd();

        std::stringstream s{};
        for (auto it = argb; it != arge; ++it)
        {
          if (!it->IsString())
            continue;
          s << it->AsString() << " ";
        }
        auto output = s.str().substr(0, s.str().size() - 1);

        {
          juce::MessageManagerLock mml;
          if (!mml.lockWasGained())
            return;

          DBG("running OSC callback");
          this->onMessage(output);
        }
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
