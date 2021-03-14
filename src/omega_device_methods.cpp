#include <stdio.h>
#include <string.h>
#include <iostream>

#include "omega_device_methods.h"

using namespace std;

OmegaDeviceMethodCommand::OmegaDeviceMethodCommand(void){
}

int OmegaDeviceMethodCommand::Execute(string methodName, const unsigned char *payload, std::size_t size, unsigned char **response, std::size_t *response_size)
{
  if (methodName.compare("turnON") == 0)
  {
    const char deviceMethodResponse[] = "{ }";
    *response_size = sizeof(deviceMethodResponse) - 1;
    *response = new unsigned char[*response_size];
    memcpy(*response, deviceMethodResponse, *response_size);

    return 200;
  }

  const char deviceMethodResponse[] = "{ }";
  *response_size = sizeof(deviceMethodResponse) - 1;
  *response = new unsigned char[*response_size];
  memcpy(*response, deviceMethodResponse, *response_size);
  return -1;
}
