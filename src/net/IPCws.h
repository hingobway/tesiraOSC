#pragma once

#include <juce_core/juce_core.h>

#include <functional>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

using WSServer = websocketpp::server<websocketpp::config::asio>;

#define IPC_PORT (53533)

class IPCws
{
public:
  IPCws();
  ~IPCws();

  void sendMessage(const std::string &msg);

private:
  void onMessage(websocketpp::connection_hdl hdl, WSServer::message_ptr msg);

  WSServer server;
  std::vector<websocketpp::connection_hdl> connections;
};
