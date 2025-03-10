#include "Network.h"

Network::Network(MainComponent *ui_)
    : ui{ui_},
      routes{
          {{"tesira_run"}, [this](auto p)
           { return routeSendTesiraCommand(p); }}
          // ,{{""}, [this](auto p){return route(p);}}
      }
{
  // REGISTER LISTENERS

  osc.onRunCommand = [this](std::string msg) { //
    routeSendTesiraCommand(juce::String(msg));
  };

  ipc.onConnect = [this]() { //
    ui->ipcStatus.updateStatus(IPCStatus::CONNECTED);
  };
  ipc.onDisconnect = [this]() { //
    ui->ipcStatus.updateStatus(IPCStatus::DISCONNECTED);
  };
  ipc.onMessage = [this](std::string msg) { //
    handleMessage(msg);
  };
}

Network::~Network()
{
}

void Network::handleMessage(juce::String msg)
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

void Network::commandSendTesira(juce::String cmd)
{
  JSON_OBJ(msg)
  {
    msg->setProperty("message", cmd);
  }
  routeSendTesiraCommand(juce::var(msg));
}

void Network::routeSendTesiraCommand(juce::var v)
{
  if (!v.getProperty("message", JSNIL).isString())
    return;

  ipc.sendMessage("tesira_run", v);
}
