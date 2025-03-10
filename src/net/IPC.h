#pragma once

#include <juce_events/juce_events.h>

#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>

#include "../util/json.h"
#include "../OPTIONS.h"

namespace WS
{
  using namespace websocketpp;

  using client = websocketpp::client<websocketpp::config::asio_client>;
  using hdl = websocketpp::connection_hdl;
  using msg = websocketpp::config::asio_client::message_type::ptr;
  using err = websocketpp::lib::error_code;
}

class IPC : private juce::Thread
{
public:
  IPC();
  ~IPC();

  void sendMessage(std::string type, juce::var data);
  void sendMessageString(const std::string &msg);

  // EVENT CALLBACKS
  std::function<void(std::string)> onMessage;
  std::function<void()> onConnect;
  std::function<void()> onDisconnect;

private:
  void initWS();
  void run() override;

  void handleMessage(WS::hdl hdl, WS::msg msg);
  void handleConnect(WS::hdl hdl);
  void handleFailOrClose(WS::hdl hdl);

  void restartThread();

  std::unique_ptr<WS::client> ws;
  WS::hdl hdl;

  int port = PORT_IPC;
};

namespace ARG
{
  using namespace std::placeholders;
}
