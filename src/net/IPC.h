#pragma once

#include <juce_events/juce_events.h>

#include <websocketpp/client.hpp>
#include <websocketpp/config/asio_no_tls_client.hpp>

#include "../OPTIONS.h"

namespace WS
{
  using namespace websocketpp;

  using client = websocketpp::client<websocketpp::config::asio_client>;
  using hdl = websocketpp::connection_hdl;
  using msg = websocketpp::config::asio_client::message_type::ptr;
  using err = websocketpp::lib::error_code;
}

namespace ARG
{
  using namespace std::placeholders;
}

class IPC : private juce::Thread
{
public:
  IPC();
  ~IPC();

  void sendMessage(const std::string &msg);

private:
  void initWS();
  void run() override;

  void onMessage(WS::hdl hdl, WS::msg msg);
  void onConnect(WS::hdl hdl);
  void onFail(WS::hdl hdl);

  void restartThread();

  std::unique_ptr<WS::client> ws;
  WS::hdl hdl;

  int port = PORT_IPC;
};
