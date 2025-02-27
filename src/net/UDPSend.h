#pragma once

#include <juce_core/juce_core.h>

#include <string>
#include <vector>

class UDPSend
{
public:
  UDPSend();
  ~UDPSend();

  bool send(const std::string &);
  bool send(const std::vector<unsigned char> &);
  bool sendBytes(const void *bytes, const int size);

private:
  std::string destination_;
  int port_;

  juce::DatagramSocket socket;
};
