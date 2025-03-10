set(BASE include/oscpack)

ADD_LIBRARY(oscpack
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

target_compile_options(oscpack PUBLIC "-w")

target_include_directories(oscpack PRIVATE ${BASE})

target_include_directories(oscpack INTERFACE ${BASE})
