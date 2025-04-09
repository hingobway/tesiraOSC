#pragma once

#include <juce_events/juce_events.h>

#include <functional>

#include "../OPTIONS.h"

#define THREAD_KILL_TIMEOUT_MS (220)
#define READ_WAIT_MS (200)
#define OSC_BUFFER_SIZE (4096)

class OSCWatch : private juce::Thread
{
public:
  OSCWatch();
  OSCWatch(int port);
  ~OSCWatch() override;

  void listenOnPort(int port);
  void listenOnPort() { listenOnPort(port); }
  int getPort() { return port; }

  // EVENT CALLBACKS
  std::function<void(std::string cmd)> onRunCommand;
  std::function<void()> onListening;
  std::function<void()> onListenFailed;

private:
  int port;

  void run() override;

  std::unique_ptr<juce::DatagramSocket> udp;
  char readBuffer[OSC_BUFFER_SIZE];

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OSCWatch)
};
