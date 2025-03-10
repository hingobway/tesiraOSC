#include "IPC.h"

#define WS_LOCAL_ADDRESS (std::string("ws://127.0.0.1"))

IPC::IPC() : juce::Thread("IPC")
{
  // init and run websocket
  initWS();
}

IPC::~IPC()
{
  ws->close(hdl, websocketpp::close::status::going_away, "QUIT");
  stopThread(1000);
}

// PUBLIC

void IPC::sendMessage(const std::string &msg)
{
  juce::MessageManagerLock mml;
  if (!mml.lockWasGained())
    return;
  DBG("[IPC] sending message...");

  WS::err err;
  ws->send(hdl, msg, websocketpp::frame::opcode::text, err);
  if (err)
    DBG("[IPC] [ERROR] " << err.message());
  else
    DBG("[IPC] message sent.");
}

// PRIVATE

void IPC::initWS() // MESSAGE THREAD ONLY
{

  // create client
  ws.reset(new WS::client());

  // websocket config
  ws->init_asio();
  ws->set_access_channels(WS::log::alevel::none);
  ws->set_error_channels(WS::log::elevel::none);

  // event handlers

  ws->set_message_handler(std::bind(&IPC::onMessage, this, ARG::_1, ARG::_2));
  ws->set_open_handler(std::bind(&IPC::onConnect, this, ARG::_1));
  ws->set_fail_handler(std::bind(&IPC::onFail, this, ARG::_1));

  // config connection
  WS::err err;
  auto c = ws->get_connection(WS_LOCAL_ADDRESS + std::to_string(port), err);
  if (err)
  {
    juce::MessageManagerLock mml;
    DBG("CREATE CONNECTION FAILED: " << err.message());
    jassertfalse;
  }
  ws->connect(c);

  // run network loop
  startThread();
}

// THREAD RUN
void IPC::run()
{
  // run connection loop
  ws->run();
}

// HANDLERS

void IPC::onMessage(WS::hdl hdl, WS::msg msg)
{
  DBG("[IPC] [MSG] " << msg->get_payload());
}

void IPC::onConnect(WS::hdl hdl_)
{
  juce::MessageManagerLock mml;
  DBG("[IPC] CONNECTION SUCCESS");
  this->hdl = hdl_;
}

void IPC::onFail(WS::hdl hdl)
{
  // restart thread (from main thread)
  juce::MessageManager::callAsync([this]() { //
    restartThread();
  });
}

void IPC::restartThread() // MESSAGE THREAD ONLY
{
  // DBG("[IPC] attempting reconnect...");

  stopThread(50);
  initWS();
}
