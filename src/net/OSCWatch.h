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
  ~OSCWatch() override;

  // EVENT CALLBACKS
  std::function<void(std::string cmd)> onRunCommand;
  std::function<void()> onListening;
  std::function<void()> onListenFailed;

private:
  void run() override;

  juce::DatagramSocket udp;
  char readBuffer[OSC_BUFFER_SIZE];

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OSCWatch)
};
