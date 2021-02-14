#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "omega_config.h"
#include "gtest/gtest.h"

namespace
{
  TEST(OmegaConfig_GetIoTConnectionString, MissingFile)
  {
    try
    {
      std::string actual = OmegaConfig_GetIoTConnectionString("");
      FAIL();
    }
    catch (const std::invalid_argument &ex)
    {
      EXPECT_EQ(ex.what(), std::string("No filename provided."));
    }
    catch (std::exception)
    {
      FAIL();
    }
  }
} // namespace
