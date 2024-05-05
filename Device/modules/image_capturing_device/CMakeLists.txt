# © 2023 Intel Corporation

simics_add_module(image_capturing_device
  CLASSES image_capturing_device
  SOURCES image_capturing_device.dml module_load.py
  SIMICS_API 6
)
add_subdirectory(test)
