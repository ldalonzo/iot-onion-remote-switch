include(GoogleTest)

add_subdirectory("${PROJECT_SOURCE_DIR}/submodules/googletest" "submodules/googletest")
include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(onion_test
  omega_config_unittest.cpp
  omega_device_methods_unittest.cpp
)

target_link_libraries(onion_test
  gtest
  gtest_main
  omega_config
  omega_device_methods
)

gtest_discover_tests(onion_test)
