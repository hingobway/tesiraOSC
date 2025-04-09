#include "NetProcess.h"

NetProcess::NetProcess() : juce::Thread("NetProcess")
{
}

NetProcess::~NetProcess()
{
  if (process != nullptr)
    process->kill();
  stopThread(200);
}

void NetProcess::run()
{
  static std::string buffer{};
  char dbuf[PROC_BUFFER_SIZE]{};

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

    int numread = process->readProcessOutput(dbuf, PROC_BUFFER_SIZE);
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
#else
    juce::ignoreUnused(dbuf);
#endif

    juce::Time::waitForMillisecondCounter(juce::Time::getMillisecondCounter() + 50);
  }
}

void NetProcess::runProcess()
{
  if (NO_NODE_HOST) // allow for separate node in development
    return;

  if (isThreadRunning())
    stopThread(100);

  std::string filename{NODE_APP};
  // univeral binary needs intel node file
#if defined(__APPLE__) && !defined(__aarch64__)
  filename = std::string("intel-") + filename;
#endif

  // init
  process.reset(new juce::ChildProcess());
  auto appPath =
      juce::File::getSpecialLocation(juce::File::currentExecutableFile)
          .getSiblingFile(filename)
          .getFullPathName();

  // start node process
  process->start(appPath + " " + std::to_string(PORT_IPC));

  // listen for output
  startThread();
}

void NetProcess::restartProcess() // MAIN THREAD ONLY
{
  DBG("[NET] RESTARTING NODE PROCESS");
  runProcess();
}
