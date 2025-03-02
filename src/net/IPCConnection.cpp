#include "IPCConnection.h"

IPCConnection::IPCConnection()
{
}

IPCConnection::~IPCConnection()
{
  disconnect();
}

void IPCConnection::connectionMade()
{
}

void IPCConnection::connectionLost()
{
}

void IPCConnection::messageReceived(const juce::MemoryBlock &message)
{
}
