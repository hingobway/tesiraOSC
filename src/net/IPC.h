#pragma once

#include <juce_core/juce_core.h>
#include <gin_network/gin_network.h>

class IPC
{
public:
  IPC();
  ~IPC();

  void sendMessage(const std::string &msg);

private:
  gin::AsyncWebsocket socket;
};
