#pragma once

#include <juce_events/juce_events.h>

#define BUFFER_SIZE (1024)

class NetProcess : private juce::Thread
{
public:
  NetProcess();
  ~NetProcess();

  void run();

private:
  static juce::String getAppPath();

  juce::ChildProcess process;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NetProcess)
};
