#pragma once

#include <juce_core/juce_core.h>

#define IPC_THREAD_KILL_TIMEOUT_MS (2000)
#define IPC_READ_WAIT_MS (1800)
#define IPC_BUFFER_SIZE (1024)

#define IPC_PORT (53533)

class IPC : private juce::Thread
{
public:
  IPC();
  ~IPC();

  void sendMessage(const std::string &msg);

private:
  void run();

  juce::StreamingSocket server;
  juce::OwnedArray<juce::StreamingSocket> connections;
};
