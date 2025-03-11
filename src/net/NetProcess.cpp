#include "NetProcess.h"

NetProcess::NetProcess() : juce::Thread("NetProcess")
{
  runProcess();
}

NetProcess::~NetProcess()
{
  stopThread(100);
  process->kill();
}

void NetProcess::run()
{
  static std::string buffer{};
  char dbuf[BUFFER_SIZE]{};

  // event loop
  while (!threadShouldExit())
  {
    // if process stopped running, restart it.
    if (!process->isRunning())
    {
      juce::MessageManager::callAsync([this]() { //
        restartProcess();
      });
      return;
    }

    // show console outputs if debugging

#ifdef JUCE_DEBUG

    int numread = process->readProcessOutput(dbuf, BUFFER_SIZE);
    if (!numread)
      continue;

    buffer += std::string(dbuf, (size_t)numread);

    // print buffered lines
    {
      juce::MessageManagerLock mml;
      if (!mml.lockWasGained())
        return;

      DBG("[NET] READ SOMETHING");

      // print complete lines
      size_t pos = 0;
      while ((pos = buffer.find('\n')) != std::string::npos)
      {
        std::string line = buffer.substr(0, pos);
        DBG("[NET] " << line);
        buffer.erase(0, pos + 1);
      }
    }

#endif

    juce::Time::waitForMillisecondCounter(juce::Time::getMillisecondCounter() + 50);
  }
}

void NetProcess::runProcess()
{
  // init
  process.reset(new juce::ChildProcess());
  auto appPath =
      juce::File::getSpecialLocation(juce::File::currentExecutableFile)
          .getSiblingFile(NODE_APP)
          .getFullPathName();

  if (NO_NODE_HOST) // allow for separate node in development
    return;

  // start node process
  process->start(appPath + " " + std::to_string(PORT_IPC));

  // listen for output
  startThread();
}

void NetProcess::restartProcess() // MAIN THREAD ONLY
{
  DBG("[NET] RESTARTING NODE PROCESS");
  stopThread(100);
  runProcess();
}
