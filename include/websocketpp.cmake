add_library(websocketpp INTERFACE)

target_include_directories(websocketpp SYSTEM INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/asio/asio/include
  ${CMAKE_CURRENT_LIST_DIR}/websocketpp
)

target_compile_definitions(websocketpp INTERFACE
  ASIO_STANDALONE=1
)
