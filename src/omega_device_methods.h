#ifndef _OMEGA_DEVICE_METHODS_H_
#define _OMEGA_DEVICE_METHODS_H_

#include <stdio.h>
#include <string.h>
#include <iostream>

#include <fastgpio.h>

using namespace std;

struct CommandResult
{
  string response;
  int code;
};

class Command
{
public:
  virtual CommandResult Execute(string methodName) = 0;
};

class OmegaDeviceMethodCommand : public Command
{

protected:
  FastGpio *_gpioObj;

public:
  OmegaDeviceMethodCommand(FastGpio *gpioObj)
  {
    _gpioObj = gpioObj;

    gpioObj->SetDirection(15, 1); // set to output
    gpioObj->Set(15, 1);

    gpioObj->SetDirection(16, 1); // set to output
    gpioObj->Set(16, 1);

    gpioObj->SetDirection(17, 1); // set to output
    gpioObj->Set(17, 1);
  }

  CommandResult Execute(string methodName);
};

class IoTHubDeviceClientDeviceMethodCallbackAdapter
{
private:
  Command *adaptee_;

public:
  IoTHubDeviceClientDeviceMethodCallbackAdapter(Command *adaptee)
      : adaptee_(adaptee)
  {
  }

  int Execute(const char *method_name, const unsigned char *payload, size_t size, unsigned char **response, size_t *response_size, void *userContextCallback)
  {
    CommandResult result = this->adaptee_->Execute(std::string(method_name));

    char deviceMethodResponse[result.response.length() + 1];
    strcpy(deviceMethodResponse, result.response.c_str());

    *response_size = sizeof(deviceMethodResponse) - 1;
    *response = new unsigned char[*response_size];
    memcpy(*response, deviceMethodResponse, *response_size);

    return result.code;
  }
};

class InMemoryFastGpio : public FastGpio
{
public:
  int SetDirection(int pinNum, int bOutput);
  int GetDirection(int pinNum, int &bOutput);

  int Set(int pinNum, int value);
  int Read(int pinNum, int &value);
};

#endif