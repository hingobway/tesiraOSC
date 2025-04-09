#pragma once

#include <juce_core/juce_core.h>
#include "../util/json.h"

#include "../MainComponent.h"
#include "IPC.h"
#include "OSCWatch.h"
#include "NetProcess.h"
#include "../Params.h"

class RoutingWrapper
{

  using RouteMap = std::unordered_map<std::string, std::function<void(juce::var)>>;

public:
  RoutingWrapper(MainComponent &, RouteMap routes);

protected:
  void handleMessage(juce::String msg);

  MainComponent &ui;
  NetProcess netProcess;
  IPC ipc;
  OSCWatch osc;

  RouteMap routes;
};
