add_library(omega_config
  omega_config.cpp
)

add_library(omega_device_methods
  omega_device_methods.cpp
)

target_link_libraries(omega_config
  parson
)
