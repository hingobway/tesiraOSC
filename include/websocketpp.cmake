add_library(websocketpp INTERFACE)

target_include_directories(websocketpp SYSTEM INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/websocketpp
)
