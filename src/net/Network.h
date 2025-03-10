#pragma once

#include <juce_core/juce_core.h>

#include "../util/json.h"

#include "../MainComponent.h"
#include "IPC.h"
#include "OSCWatch.h"
#include "NetProcess.h"

class Network
{
public:
  Network(MainComponent *);
  ~Network();

  void handleMessage(juce::String msg);

  void commandSendTesira(juce::String cmd);

private:
  MainComponent *ui;
  NetProcess netProcess;
  IPC ipc;
  OSCWatch osc;

  // ROUTES

  std::unordered_map<std::string, std::function<void(juce::var)>> routes;

  void routeSendTesiraCommand(juce::var p);

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Network)
};
