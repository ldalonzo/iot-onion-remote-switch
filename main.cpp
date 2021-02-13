#include <iostream>
#include <string>

#include "OnionConfig.h"

#include "iothub.h"

int main(int argc, char *argv[])
{
  std::cout << argv[0] << " Version " << Onion_VERSION_MAJOR << "." << Onion_VERSION_MINOR << std::endl;

  if (IoTHub_Init() != 0)
  {
    std::cout << "Failed to initialize the platform." << std::endl;
    return -1;
  }

  return 0;
}
