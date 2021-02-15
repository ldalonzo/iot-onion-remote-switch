#include <stdexcept>
#include <string>

#include "omega_config.h"

#include "parson.h"

std::string OmegaConfig_GetIoTConnectionString(std::string filename)
{
  if (filename.empty())
  {
    throw std::invalid_argument("No filename provided.");
  }

  JSON_Value *root_value = json_parse_file(filename.c_str());
  if (root_value == NULL)
  {
    throw std::invalid_argument("Could NOT parse " + filename + " as a JSON file.");
  }

  JSON_Object *root_object = json_value_get_object(root_value);

  JSON_Value *connectionString_value = json_object_dotget_value(root_object, "connectionString");
  if (connectionString_value == NULL)
  {
    throw std::invalid_argument("Could NOT find \"connectionString\".");
  }

  const char *connectionString_data = json_value_get_string(connectionString_value);

  return std::string(connectionString_data);
}
