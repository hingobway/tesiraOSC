#pragma once

#include <juce_events/juce_events.h>

class IPCConnection : public juce::InterprocessConnection
{
public:
  IPCConnection();
  ~IPCConnection();

private:
  void connectionMade() override;
  void connectionLost() override;
  void messageReceived(const juce::MemoryBlock &message) override;
};
