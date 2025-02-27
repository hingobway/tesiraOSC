set(BASE include/oscpack)

# separate versions of NetworkingUtils.cpp and UdpSocket.cpp are provided for Win32 and POSIX
# the IpSystemTypePath selects the correct ones based on the current platform
IF(WIN32)
  set(IpSystemTypePath ip/win32)
  set(LIBS ${LIBS} Ws2_32 winmm)
ELSE(WIN32)
  set(IpSystemTypePath ip/posix)
ENDIF(WIN32)

ADD_LIBRARY(oscpack

  ${BASE}/ip/IpEndpointName.h
  ${BASE}/ip/IpEndpointName.cpp

  ${BASE}/ip/NetworkingUtils.h
  ${BASE}/${IpSystemTypePath}/NetworkingUtils.cpp

  ${BASE}/ip/UdpSocket.h
  ${BASE}/${IpSystemTypePath}/UdpSocket.cpp

  ${BASE}/ip/PacketListener.h
  ${BASE}/ip/TimerListener.h

  ${BASE}/osc/OscTypes.h
  ${BASE}/osc/OscTypes.cpp
  ${BASE}/osc/OscHostEndianness.h
  ${BASE}/osc/OscException.h
  ${BASE}/osc/OscPacketListener.h
  ${BASE}/osc/MessageMappingOscPacketListener.h
  ${BASE}/osc/OscReceivedElements.h
  ${BASE}/osc/OscReceivedElements.cpp
  ${BASE}/osc/OscPrintReceivedElements.h
  ${BASE}/osc/OscPrintReceivedElements.cpp
  ${BASE}/osc/OscOutboundPacketStream.h
  ${BASE}/osc/OscOutboundPacketStream.cpp
)

target_compile_options(oscpack PRIVATE "-w")

target_include_directories(oscpack PRIVATE ${BASE})

target_include_directories(oscpack INTERFACE ${BASE})
