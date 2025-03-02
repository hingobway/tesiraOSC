#include "IPCws.h"

IPCws::IPCws()
{
  try
  {
    // net init
    server.init_asio();

    // handlers
    server.set_message_handler(std::bind(&onMessage, this, std::placeholders::_1, std::placeholders::_2));

    // start listening
    server.listen(IPC_PORT);
    server.start_accept();
    server.run();
  }
  catch (const std::exception &e)
  {
    DBG("ERROR (websocketpp): " << e.what());
  }
}

IPCws::~IPCws()
{
}

void IPCws::sendMessage(const std::string &msg)
{
  for (auto &c : connections)
  {
    websocketpp::endpoint<websocketpp::connection<websocketpp::config::asio>, websocketpp::config::asio>::connection_ptr a;

    server.send(c, msg, websocketpp::frame::opcode::text);
  }
}

void IPCws::onMessage(websocketpp::connection_hdl hdl, WSServer::message_ptr msg)
{
  if (std::find(connections.begin(), connections.end(), hdl) == connections.end())
  {
    DBG("new connection found.");
    connections.push_back(hdl);
  }

  DBG("MESSAGE: " << msg->get_payload());
}
