#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "omega_config.h"
#include "gtest/gtest.h"

namespace
{
  TEST(OmegaConfig_GetIoTConnectionString, Success)
  {
    std::string settingsFilename = std::tmpnam(nullptr);
    std::ofstream settingsFile;
    settingsFile.open(settingsFilename);
    settingsFile << "{ \"connectionString\": \"lorem ipsum dolor\" }";
    settingsFile.close();

    EXPECT_EQ("lorem ipsum dolor", OmegaConfig_GetIoTConnectionString(settingsFilename));

    std::remove(settingsFilename.c_str());
  }

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

  TEST(OmegaConfig_GetIoTConnectionString, MissingConnectionString)
  {
    std::string settingsFilename = std::tmpnam(nullptr);
    std::ofstream settingsFile;
    settingsFile.open(settingsFilename);
    settingsFile << "{ }";
    settingsFile.close();

    try
    {
      std::string actual = OmegaConfig_GetIoTConnectionString(settingsFilename);
      FAIL();
    }
    catch (const std::invalid_argument &ex)
    {
      EXPECT_EQ(ex.what(), std::string("Could NOT find \"connectionString\"."));
    }
    catch (std::exception)
    {
      FAIL();
    }

    std::remove(settingsFilename.c_str());
  }
} // namespace
