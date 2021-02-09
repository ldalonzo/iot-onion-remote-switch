#include <iostream>
#include <string>

#include "OnionConfig.h"

int main(int argc, char *argv[])
{
  std::cout << argv[0] << " Version " << Onion_VERSION_MAJOR << "." << Onion_VERSION_MINOR << std::endl;

  return 0;
}
