#include <stdio.h>
#include <string.h>
#include <iostream>

#include "omega_device_methods.h"

#include <fastgpio.h>

using namespace std;

class FastGpioCommand
{
public:
  virtual ~FastGpioCommand()
  {
  }
  virtual void Execute() const = 0;
};

class FastGpioSetCommand : public FastGpioCommand
{
private:
  FastGpio *_gpioObj;
  int _pinNumber;
  int _value;

public:
  FastGpioSetCommand(FastGpio *gpioObj, int pinNumber, int value)
  {
    _gpioObj = gpioObj;
    _pinNumber = pinNumber;
    _value = value;
  }

  void Execute() const override
  {
    _gpioObj->SetDirection(this->_pinNumber, 1); // set to output
    _gpioObj->Set(this->_pinNumber, this->_value);
  }
};

CommandResult OmegaDeviceMethodCommand::Execute(string methodName)
{
  CommandResult result;

  if (methodName.compare("turnON") == 0)
  {
    FastGpioCommand *cmd = new FastGpioSetCommand(this->_gpioObj, 15, 0);
    cmd->Execute();

    delete cmd;

    result.code = 200;
    result.response = "{ }";
  }
  else
  {
    result.code = -1;
    result.response = "{ }";
  }

  return result;
}

int InMemoryFastGpio::SetDirection(int pinNum, int bOutput)
{
	return EXIT_SUCCESS;
}

int InMemoryFastGpio::GetDirection(int pinNum, int &bOutput)
{
	return EXIT_SUCCESS;
}

int InMemoryFastGpio::Set(int pinNum, int value)
{
  std::cout << "SET PIN " << pinNum << " = " << value << std::endl;
	return EXIT_SUCCESS;
}

int InMemoryFastGpio::Read(int pinNum, int &value)
{	
	return EXIT_SUCCESS;
}
