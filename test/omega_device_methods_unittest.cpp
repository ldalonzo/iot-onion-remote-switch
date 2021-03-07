#include <iostream>
#include <fstream>

#include "omega_device_methods.h"
#include "gtest/gtest.h"

namespace
{
  TEST(deviceMethodCallback, Unrecognized)
  {
    const char *method_name = "blah";
    const unsigned char *payload = new unsigned char;
    size_t size;
    unsigned char **response = new unsigned char *;
    size_t *response_size = new size_t;
    int actual_result = deviceMethodCallback(method_name, payload, size, response, response_size, NULL);

    EXPECT_EQ(-1, actual_result);
  }

  TEST(deviceMethodCallback, TurnON)
  {
    const char *method_name = "turnON";
    const unsigned char *payload = new unsigned char;
    size_t size;
    unsigned char **response = new unsigned char *;
    size_t *response_size = new size_t;
    int actual_result = deviceMethodCallback(method_name, payload, size, response, response_size, NULL);
    std::string actual_response(reinterpret_cast<char const *>(*response), *response_size);

    EXPECT_EQ(200, actual_result);
    EXPECT_EQ("{ }", actual_response);
  }
} // namespace
