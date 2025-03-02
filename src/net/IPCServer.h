#pragma once

#include <juce_events/juce_events.h>

#include "IPCConnection.h"

#define IPC_PORT (53533)

class IPCServer : private juce::InterprocessConnectionServer
{
public:
  IPCServer();
  ~IPCServer();

private:
  juce::InterprocessConnection *createConnectionObject() override;

  juce::OwnedArray<IPCConnection> connections;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(IPCServer)
};
