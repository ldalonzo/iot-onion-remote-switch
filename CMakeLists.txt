cmake_minimum_required(VERSION 3.10)
project(Onion VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)
list(APPEND EXTRA_LIBS omega_device_methods)
list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/src")

add_subdirectory(${PROJECT_SOURCE_DIR}/submodules/azure-iot-sdk-c)

set(AZUREIOT_INC_FOLDER "${PROJECT_SOURCE_DIR}/submodules/azure-iot-sdk-c/iothub_client/inc")
include_directories(${AZUREIOT_INC_FOLDER})

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
  ${EXTRA_INCLUDES}
)

target_link_libraries(onion-switch
  iothub_client
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

option(PACKAGE_TESTS "Build the tests" ON)

if(PACKAGE_TESTS)
  include(CTest)
  enable_testing()
  add_subdirectory(test)
endif()
