#include "IPCServer.h"

IPCServer::IPCServer()
{
  beginWaitingForSocket(IPC_PORT, "127.0.0.1");
}

IPCServer::~IPCServer()
{
  stop();
}

juce::InterprocessConnection *IPCServer::createConnectionObject()
{
  auto conn = new IPCConnection();
  connections.add(conn);
  return conn;
}
