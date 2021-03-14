#include <iostream>
#include <string>

#include "OnionConfig.h"

#include "omega_config.h"
#include "omega_device_methods.h"

#include "iothub_client_options.h"
#include "iothub_device_client.h"
#include "iothub.h"
#include "iothubtransportmqtt.h"

static Command *command;

static int deviceMethodCallback(const char *method_name, const unsigned char *payload, size_t size, unsigned char **response, size_t *response_size, void *userContextCallback)
{
  return command->Execute(std::string(method_name), payload, size, response, response_size);
}

int main(int argc, char *argv[])
{
  std::cout << argv[0] << " Version " << Onion_VERSION_MAJOR << "." << Onion_VERSION_MINOR << std::endl;

  if (IoTHub_Init() != 0)
  {
    std::cout << "Failed to initialize the platform." << std::endl;
    return -1;
  }

  IOTHUB_CLIENT_TRANSPORT_PROVIDER protocol = MQTT_Protocol;
  IOTHUB_DEVICE_CLIENT_HANDLE iotHubClientHandle;
  std::string connectionString = OmegaConfig_GetIoTConnectionString("appsettings.json");
  if ((iotHubClientHandle = IoTHubDeviceClient_CreateFromConnectionString(connectionString.c_str(), protocol)) == NULL)
  {
    std::cout << "ERROR: iotHubClientHandle is NULL!" << std::endl;
    return -2;
  }

  command = new OmegaDeviceMethodCommand();

  // Turn on automatic URL encoding
  bool urlEncodeOn = true;
  IoTHubDeviceClient_SetOption(iotHubClientHandle, OPTION_AUTO_URL_ENCODE_DECODE, &urlEncodeOn);

  bool traceOn = true;
  IoTHubDeviceClient_SetOption(iotHubClientHandle, OPTION_LOG_TRACE, &traceOn);

  IoTHubDeviceClient_SetDeviceMethodCallback(iotHubClientHandle, deviceMethodCallback, NULL);
  getchar();

  IoTHubDeviceClient_Destroy(iotHubClientHandle);
  IoTHub_Deinit();

  delete command;
  return 0;
}
