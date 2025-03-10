#pragma once

#include <juce_events/juce_events.h>

#include <functional>

#include "../OPTIONS.h"

#define THREAD_KILL_TIMEOUT_MS (220)
#define READ_WAIT_MS (200)
#define BUFFER_SIZE (1024)

class OSCWatch : private juce::Thread
{
public:
  OSCWatch();
  ~OSCWatch();

  std::function<void(std::string)> onRunCommand;

private:
  void run() override;

  juce::DatagramSocket udp;
  char readBuffer[BUFFER_SIZE];

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OSCWatch)
};
