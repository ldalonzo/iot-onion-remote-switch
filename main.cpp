#include <iostream>
#include <string>

#include "OnionConfig.h"

#include "omega_config.h"

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

  IoTHub_Deinit();
  return 0;
}
