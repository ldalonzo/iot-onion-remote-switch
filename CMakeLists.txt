cmake_minimum_required(VERSION 3.10)
project(Onion VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(
  ${PROJECT_SOURCE_DIR}/submodules/azure-iot-sdk-c/deps/parson/
)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/src)

# Set up the include and library paths
include_directories($ENV{TOOLCHAIN_PREFIX}/include/)
include_directories($ENV{TOOLCHAIN_PREFIX}/include/azureiot)
link_directories($ENV{TOOLCHAIN_PREFIX}/lib)

configure_file(appsettings.json appsettings.json COPYONLY)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(OnionConfig.h.in OnionConfig.h)

add_executable(onion-switch
  ${PROJECT_SOURCE_DIR}/main.cpp
)

# add the binary tree to the search path for include files
# so that we will find OnionConfig.h
target_include_directories(onion-switch PUBLIC
  "${PROJECT_BINARY_DIR}"
)

target_link_libraries(onion-switch
  omega_config
  omega_device_methods

  iothub_client_mqtt_transport
  iothub_client
  umqtt
  aziotsharedutil
  parson
  pthread
  curl
  ssl
  crypto
  m 
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

option(PACKAGE_TESTS "Build the tests")

if(PACKAGE_TESTS)
  include(CTest)
  enable_testing()
  add_subdirectory(test)
endif()
