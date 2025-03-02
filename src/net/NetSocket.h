#pragma once

#include <juce_core/juce_core.h>

#include <string>
#include <vector>

class NetSocket
{
public:
  enum SocketType
  {
    TCP,
    UDP
  };

  // MEMBERS

  NetSocket();
  ~NetSocket();

  bool connect(SocketType type);

  bool send(SocketType type, const std::string &cmd);
  bool send(SocketType type, const std::vector<unsigned char> &arr);
  bool sendBytes(SocketType type, const void *bytes, const int size);

  juce::String getSelectedCueNumber(SocketType type);

  bool oscWatch();

private:
  std::string destination_;
  int port_;

  juce::DatagramSocket udp;
  juce::StreamingSocket tcp;
};
