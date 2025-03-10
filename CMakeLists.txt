cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ----------------------------------------
# VARIABLES
set(PROJECT_NAME "TESIRATEL")
set(TARGET_NAME "tesiratel")
set(VERSION_NUMBER 0.1.0)

# ----------------------------------------

# PROJECT INIT
project(${PROJECT_NAME} VERSION ${VERSION_NUMBER})

if(APPLE AND CMAKE_BUILD_TYPE STREQUAL "Release")
  set(CMAKE_OSX_ARCHITECTURES "x86_64;arm64")
endif()

# PACKAGE INCLUDE
add_subdirectory(include/JUCE JUCE)

find_package(Boost CONFIG REQUIRED)
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
set(NODE_FILE_DIR telnet)
set(NODE_FILENAME tel)

if(WIN32)
  set(NODE_FULL_FILENAME ${NODE_FILENAME}.exe)
else()
  set(NODE_FULL_FILENAME ${NODE_FILENAME})
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
)

target_include_directories(${TARGET_NAME} PRIVATE ${Boost_INCLUDE_DIRS})

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

  PUBLIC
  juce::juce_recommended_config_flags
  juce::juce_recommended_lto_flags
  juce::juce_recommended_warning_flags
)

# ----------------------------------------

# NODE BUILD AND INSTALL
set(NODE_FULL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${NODE_FILE_DIR})
set(NODE_PATH_SRC "${NODE_FULL_DIR}/${NODE_FULL_FILENAME}")
set(NODE_PATH_DST "$<TARGET_FILE_DIR:${TARGET_NAME}>/${NODE_FULL_FILENAME}")

add_custom_command(TARGET ${TARGET_NAME} PRE_BUILD
  COMMAND deno run build
  WORKING_DIRECTORY ${NODE_FULL_DIR}
)
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
  ${NODE_PATH_SRC} ${NODE_PATH_DST}
)
