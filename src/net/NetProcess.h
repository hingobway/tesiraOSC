#pragma once

#include <juce_events/juce_events.h>

#include "../OPTIONS.h"

#define BUFFER_SIZE (1024)

class NetProcess : private juce::Thread
{
public:
  NetProcess();
  ~NetProcess();

  void run();

private:
  void runProcess();
  void restartProcess();

  std::unique_ptr<juce::ChildProcess> process;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NetProcess)
};
