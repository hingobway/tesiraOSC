#pragma once

#include <juce_core/juce_core.h>

#define THREAD_KILL_TIMEOUT_MS (2000)
#define READ_WAIT_MS (1800)
#define BUFFER_SIZE (1024)

#define OSC_PORT (53534)

#define OSC_COMMAND ("/run")

class OSCWatch : private juce::Thread
{
public:
  OSCWatch();
  ~OSCWatch();

private:
  void run();

  juce::DatagramSocket udp;
  char readBuffer[BUFFER_SIZE];

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OSCWatch)
};
