#include <stdio.h>
#include <string.h>
#include <iostream>

#include "omega_device_methods.h"

int deviceMethodCallback(const char *method_name, const unsigned char* payload, std::size_t size, unsigned char** response, std::size_t* response_size, void* userContextCallback)
{
  if (strcmp("turnON", method_name) == 0)
  {
    const char deviceMethodResponse[] = "{ }";
    *response_size = sizeof(deviceMethodResponse) - 1;
    *response = new unsigned char[*response_size];
    memcpy(*response, deviceMethodResponse, *response_size);

    return 200;
  }

  return -1;
}
