#pragma once

#include <juce_core/juce_core.h>

#include "util/json.h"

#include "MainComponent.h"
#include "net/IPC.h"
#include "net/OSCWatch.h"
#include "net/NetProcess.h"

class Routing
{
public:
  Routing(MainComponent *);
  ~Routing();

  void handleMessage(juce::String msg);

  void command_tesira_run(juce::String cmd);
  void command_tesira_run2(juce::String cmd);

private:
  MainComponent *ui;
  NetProcess netProcess;
  IPC ipc;
  OSCWatch osc;

  // ROUTES

  void route_tesira_connect_status(juce::var);

  std::unordered_map<std::string, std::function<void(juce::var)>> routes;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Routing)
};
