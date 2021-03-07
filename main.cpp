#include <iostream>
#include <string>

#include "OnionConfig.h"

#include "omega_config.h"
#include "omega_device_methods.h"

#include "iothub_client_options.h"
#include "iothub_device_client.h"
#include "iothub.h"
#include "iothubtransportmqtt.h"

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

  // Turn on automatic URL encoding
  bool urlEncodeOn = true;
  IoTHubDeviceClient_SetOption(iotHubClientHandle, OPTION_AUTO_URL_ENCODE_DECODE, &urlEncodeOn);

  bool traceOn = true;
  IoTHubDeviceClient_SetOption(iotHubClientHandle, OPTION_LOG_TRACE, &traceOn);

  IoTHubDeviceClient_SetDeviceMethodCallback(iotHubClientHandle, deviceMethodCallback, NULL);
  getchar();

  IoTHubDeviceClient_Destroy(iotHubClientHandle);
  IoTHub_Deinit();
  return 0;
}
