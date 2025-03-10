#include "NetProcess.h"

NetProcess::NetProcess() : juce::Thread("NetProcess")
{

  process.start(getAppPath());

  startThread();
}

NetProcess::~NetProcess()
{
  stopThread(1000);
  process.kill();
}

void NetProcess::run()
{
  static std::string buffer{};

  char dbuf[BUFFER_SIZE]{};
  while (!threadShouldExit())
  {
    process.readProcessOutput(dbuf, BUFFER_SIZE);

    if (!strlen(dbuf))
      continue;

    buffer += std::string(dbuf);

    // print buffered lines
    {
      juce::MessageManagerLock mml;
      if (!mml.lockWasGained())
        return;

      // print complete lines
      size_t pos = 0;
      while ((pos = buffer.find('\n')) != std::string::npos)
      {
        std::string line = buffer.substr(0, pos);
        DBG("[NET] " << line);
        buffer.erase(0, pos + 1);
      }
    }

    std::memset(dbuf, 0, BUFFER_SIZE);

    juce::Time::waitForMillisecondCounter(juce::Time::getMillisecondCounter() + 50);
  }
}

juce::String NetProcess::getAppPath()
{
  return juce::File::getSpecialLocation(juce::File::currentExecutableFile)
      .getSiblingFile(NODE_APP)
      .getFullPathName();
}
