#include "IPC.h"

IPC::IPC() : socket(juce::URL("ws://127.0.0.1:53533"))
{

  socket.onConnect = [this]()
  {
    DBG("connected!");
  };

  socket.onText = [this](const juce::String &msg)
  {
    DBG("WS: " << msg);
  };

  socket.onDisconnect = [this]()
  {
    DBG("DISCONNECTED");
  };

  while (!socket.isConnected())
  {
    DBG("attempting IPC connection...");
    socket.connect();

    juce::Time::waitForMillisecondCounter(juce::Time::getMillisecondCounter() + 500);
  }

  DBG("IPC connected!");
}

IPC::~IPC()
{
  socket.disconnect();
}

void IPC::sendMessage(const std::string &msg)
{
  DBG("sending IPC...");
  socket.send(juce::String(msg));
}
