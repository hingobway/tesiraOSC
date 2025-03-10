#include "Routing.h"

Routing::Routing(MainComponent *ui_)
    : ui{ui_},
      routes{
          {{"tesira_connect_status"}, [this](auto p)
           { return route_tesira_connect_status(p); }}
          // ,{{""}, [this](auto p){return route(p);}}
      }
{
  // REGISTER LISTENERS

  // osc
  osc.onListening = [this]() { //
    ui->netStatus.updateStatus(NetStatus::OSC, NetStatus::CONNECTED);
  };
  osc.onListenFailed = [this]() { //
    ui->netStatus.updateStatus(NetStatus::OSC, NetStatus::DISCONNECTED);
  };
  osc.onRunCommand = [this](std::string msg) { //
    command_tesira_run(juce::String(msg));
  };

  // ipc
  ipc.onMessage = [this](std::string msg) { //
    handleMessage(msg);
  };
  ipc.onConnect = [this]() { //
    ui->netStatus.updateStatus(NetStatus::IPC, NetStatus::CONNECTED);
  };
  ipc.onDisconnect = [this]() { //
    ui->netStatus.updateStatus(NetStatus::IPC, NetStatus::DISCONNECTED);
  };
}

// ROUTES

void Routing::route_tesira_connect_status(juce::var p)
{
  auto c = p.getProperty("connected", JSNIL);
  if (!c.isBool())
    return;

  ui->netStatus.updateStatus(
      NetStatus::TESIRA,
      (!!c) ? NetStatus::CONNECTED : NetStatus::DISCONNECTED);
}

// COMMANDS

void Routing::command_tesira_run(juce::String cmd)
{
  JSON_OBJ(msg)
  {
    msg->setProperty("message", cmd);
  }
  ipc.sendMessage("tesira_run", juce::var(msg));
}

// METHODS -----------------------------------------------------

Routing::~Routing()
{
}

void Routing::handleMessage(juce::String msg)
{
  auto obj = juce::JSON::parse(msg);
  auto type_v = obj.getProperty("type", JSNIL);
  if (!type_v.isString())
    return;
  auto type = type_v.toString().toStdString();
  auto data = obj.getProperty("data", JSNIL);

  if (routes.find(type) != routes.end())
  {
    routes[type](data);
  }
}
