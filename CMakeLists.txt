cmake_minimum_required(VERSION 3.10)
project(Onion VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(CTest)
enable_testing()

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(OnionConfig.h.in OnionConfig.h)

add_executable(Onion main.cpp)

# add the binary tree to the search path for include files
# so that we will find OnionConfig.h
target_include_directories(Onion PUBLIC
  "${PROJECT_BINARY_DIR}"
  ${EXTRA_INCLUDES}
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
