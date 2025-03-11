cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ----------------------------------------
# VARIABLES
set(PROJECT_NAME "TESIRATEL")
set(TARGET_NAME "tesiratel")
set(VERSION_NUMBER 0.1.0)

# while debugging, disable the hosted node instance to use your own. node will always be hosted in production.
set(DISABLE_HOSTED_NODE 1)

# ----------------------------------------

# PROJECT INIT
project(${PROJECT_NAME} VERSION ${VERSION_NUMBER})

# PACKAGE INCLUDE
add_subdirectory(include/JUCE JUCE)
add_subdirectory(include/melatonin_inspector)

include(include/oscpack.cmake)
include(include/websocketpp.cmake)

# JUCE CONFIG
juce_add_gui_app(${TARGET_NAME}
  PRODUCT_NAME "TESIRATEL"

  # manufacturer
  COMPANY_NAME "foster"
  BUNDLE_ID "audio.foster.tesiratel"
)

# NODE DIR SETUP
set(NODE_FILE_DIR "telnet")
set(NODE_FILENAME "node_telnet")
set(NODE_BINDIR "bin")
set(NODE_ENTRYPOINT "main.ts")

if(WIN32)
  set(NODE_FULL_FILENAME "${NODE_FILENAME}.exe")
else()
  set(NODE_FULL_FILENAME "${NODE_FILENAME}")
endif()

if(NOT CMAKE_BUILD_TYPE STREQUAL "Release" AND DISABLE_HOSTED_NODE)
  set(NO_NODE_HOST_FINAL 1)
else()
  set(NO_NODE_HOST_FINAL 0)
endif()

# FINISH TARGET CONFIG
target_compile_definitions(${TARGET_NAME}
  PUBLIC
  JUCE_WEB_BROWSER=0
  JUCE_USE_CURL=0
  DONT_SET_USING_JUCE_NAMESPACE=1

  CMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE}"
  VERSION="${CURRENT_VERSION}"

  PRODUCT_NAME_WITHOUT_VERSION="${TARGET_NAME}"

  JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:${TARGET_NAME},JUCE_PRODUCT_NAME>"
  JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:${TARGET_NAME},JUCE_VERSION>"

  PRIVATE
  NODE_APP="${NODE_FULL_FILENAME}"
  NO_NODE_HOST=${NO_NODE_HOST_FINAL}
)

# ADD FILES
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)
target_sources(${TARGET_NAME} PRIVATE ${SOURCE_FILES})

# BINARY DATA
file(GLOB_RECURSE BINARY_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/assets/*")
list(FILTER BINARY_FILES EXCLUDE REGEX "/\\.DS_Store$")
juce_add_binary_data(BinaryData SOURCES ${BINARY_FILES})

# ADD LIBRARIES
target_link_libraries(${TARGET_NAME}
  PRIVATE
  BinaryData

  # EXTERNAL DEPS
  oscpack
  websocketpp

  # JUCE MODULES
  juce::juce_gui_basics
  juce::juce_gui_extra

  melatonin_inspector

  PUBLIC
  juce::juce_recommended_config_flags
  juce::juce_recommended_lto_flags
  juce::juce_recommended_warning_flags
)

# ----------------------------------------

# NODE BUILD AND INSTALL
if(NOT NO_NODE_HOST_FINAL)
  set(NODE_FULL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${NODE_FILE_DIR}")
  set(NODE_FULL_BINDIR "${NODE_FULL_DIR}/${NODE_BINDIR}")
  set(NODE_PATH_SRC "${NODE_FULL_BINDIR}/${NODE_FULL_FILENAME}")
  set(NODE_PATH_DST "$<TARGET_FILE_DIR:${TARGET_NAME}>/${NODE_FULL_FILENAME}")

  # build binary for all platforms except intel mac
  if(NOT APPLE OR "arm64" IN_LIST CMAKE_OSX_ARCHITECTURES)
    add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD
      COMMAND deno compile "-A" "-o" ${NODE_PATH_SRC} ${NODE_ENTRYPOINT}
      WORKING_DIRECTORY ${NODE_FULL_DIR}
    )
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
      ${NODE_PATH_SRC} ${NODE_PATH_DST}
    )
  endif()

  # build mac intel binary (separate for universal)
  if(APPLE AND "x86_64" IN_LIST CMAKE_OSX_ARCHITECTURES)
    set(NODE_PATH_SRC "${NODE_FULL_BINDIR}/intel-${NODE_FULL_FILENAME}")
    set(NODE_PATH_DST "$<TARGET_FILE_DIR:${TARGET_NAME}>/intel-${NODE_FULL_FILENAME}")

    add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD
      COMMAND deno compile "--target" "x86_64-apple-darwin" "-A" "-o" ${NODE_PATH_SRC} ${NODE_ENTRYPOINT}
      WORKING_DIRECTORY ${NODE_FULL_DIR}
    )
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy
      ${NODE_PATH_SRC} ${NODE_PATH_DST}
    )
  endif()
endif()
