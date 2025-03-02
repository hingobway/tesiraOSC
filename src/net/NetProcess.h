#pragma once

#include <juce_core/juce_core.h>

#define BUFFER_SIZE (1024)

class NetProcess : private juce::Thread
{
public:
  NetProcess();
  ~NetProcess();

  void run();

private:
  juce::ChildProcess process;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NetProcess)
};
