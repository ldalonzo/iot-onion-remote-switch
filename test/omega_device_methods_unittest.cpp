#include <iostream>
#include <fstream>

#include "omega_device_methods.h"
#include "gtest/gtest.h"

namespace
{
  TEST(deviceMethodCallback, Unrecognized)
  {
    const char *method_name = "blah";
    int actual_result = deviceMethodCallback(method_name);

    EXPECT_EQ(-1, actual_result);
  }
} // namespace
