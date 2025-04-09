#pragma once

#include <juce_core/juce_core.h>

#include "net/RoutingWrapper.h"

class Routing : private RoutingWrapper
{
public:
  Routing(MainComponent &ui_)
      : RoutingWrapper(
            ui_,
            // REGISTER ROUTES
            {
                {{"tesira_connect_status"}, [this](auto p)
                 { return route_tesira_connect_status(p); }}
                // ,{{""}, [this](auto p){return route(p);}}
            })
  {
    // REGISTER LISTENERS

    // osc
    osc.onListening = [this]() { //
      ui.netStatus.updateStatus(NetStatus::OSC, NetStatus::CONNECTED);
    };
    osc.onListenFailed = [this]() { //
      ui.netStatus.updateStatus(NetStatus::OSC, NetStatus::DISCONNECTED);
    };
    osc.onRunCommand = [this](std::string msg) { //
      tesira_run(juce::String(msg));
    };

    // ipc
    ipc.onMessage = [this](std::string msg) { //
      handleMessage(msg);
    };
    ipc.onConnect = [this]() { //
      ui.netStatus.updateStatus(NetStatus::IPC, NetStatus::CONNECTED);

      // run relock to trigger tesira connection
      if (ui.params.get().isLocked)
      {
        system_lock(true);
      }

    };
    ipc.onDisconnect = [this]() { //
      ui.netStatus.updateStatus(NetStatus::IPC, NetStatus::DISCONNECTED);
      ui.netStatus.updateStatus(NetStatus::TESIRA, NetStatus::DISCONNECTED);
    };

    // auto-start if ready
    if (ui.params.get().isLocked)
      system_lock(true);
  }

  // COMMANDS

  void tesira_run(juce::String message)
  {
    JSON_OBJ(cmd)
    {
      cmd->setProperty("message", message);
    }
    ipc.sendCommand("tesira_run", juce::var(cmd));
  }

  void tesira_connect(juce::String remoteAddress, juce::String localAddress, int port)
  {
    JSON_OBJ(cmd)
    {
      cmd->setProperty("remoteAddress", remoteAddress);
      cmd->setProperty("localAddress", localAddress);
      cmd->setProperty("port", port);
    }
    ipc.sendCommand("tesira_connect", juce::var(cmd));
  }

  void system_lock(bool isLocked)
  {
    if (isLocked)
    {
      auto &p = ui.params.get();

      // restart OSC connection
      if (p.osc.port > 0 && osc.getPort() != p.osc.port)
        osc.listenOnPort(p.osc.port);

      // START/RESTART NODE if needed
      if (ui.netStatus.getStatus(NetStatus::TESIRA) == NetStatus::CONNECTED || ui.netStatus.getStatus(NetStatus::IPC) == NetStatus::DISCONNECTED)
      {
        netProcess.runProcess();
      }
      else
      {
        // otherwise request tesira connect
        tesira_connect(p.tesira.remoteAddress, p.tesira.localAddress, p.tesira.port);
      }
    }
    else
    {
      // TODO anything to do immediately on unlock?
    }
  }

private:
  // ROUTES

  void route_tesira_connect_status(juce::var p)
  {
    auto c = p.getProperty("connected", JSNIL);
    if (!c.isBool())
      return;

    ui.netStatus.updateStatus(
        NetStatus::TESIRA,
        (!!c) ? NetStatus::CONNECTED : NetStatus::DISCONNECTED);
  }

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Routing)
};
