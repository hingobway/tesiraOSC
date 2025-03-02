#include "IPC.h"

IPC::IPC() : juce::Thread("IPC")
{
  bool success = server.createListener(IPC_PORT, "127.0.0.1");
  if (!success)
    jassertfalse;

  startThread();
}

IPC::~IPC()
{
  stopThread(IPC_THREAD_KILL_TIMEOUT_MS);
  server.close();
}

void IPC::sendMessage(const std::string &msg)
{
  for (auto it = connections.begin(); it != connections.end();)
  {
    auto &c = *it;

    // make sure connection is valid
    if (!c->isConnected())
    {
      it++;
      c->close();
      connections.removeObject(c);
      DBG("removed inactive connection.");
      continue;
    }

    // write to connection
    c->write(msg.c_str(), msg.size());
    ++it;
  }
}

// run thread
void IPC::run()
{
  while (!threadShouldExit())
  {
    auto c = server.waitForNextConnection();
    connections.add(c);

    DBG("new connection!");

    juce::Thread::launch(
        [this, c]()
        {
          char buffer[IPC_BUFFER_SIZE];

          while (true)
          {
            std::memset(buffer, 0, IPC_BUFFER_SIZE);
            int ready = c->waitUntilReady(true, IPC_READ_WAIT_MS);
            if (ready != 1)
              continue;

            c->read(buffer, IPC_BUFFER_SIZE, true);
            std::string message{buffer};
            if (!message.length())
              continue;

            DBG("MESSAGE RECEIVED: " << message);
          }
        });
  }
}
