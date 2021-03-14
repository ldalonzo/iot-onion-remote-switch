#ifndef _OMEGA_DEVICE_METHODS_H_
#define _OMEGA_DEVICE_METHODS_H_

using namespace std;

class Command
{
public:
  virtual int Execute(string methodName, const unsigned char *payload, std::size_t size, unsigned char **response, std::size_t *response_size) = 0;
};

class OmegaDeviceMethodCommand : public Command
{
public:
  OmegaDeviceMethodCommand(void);

  int Execute(string methodName, const unsigned char *payload, std::size_t size, unsigned char **response, std::size_t *response_size);
};

#endif