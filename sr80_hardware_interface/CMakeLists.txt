cmake_minimum_required(VERSION 3.8)
project(sr80_hardware_interface)

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(Threads REQUIRED)
find_package(yaml-cpp REQUIRED)

set(THIS_PACKAGE_INCLUDE_DEPENDS
  rclcpp
  rclcpp_lifecycle
  hardware_interface
  pluginlib
)

set(ec_interface /usr/local/lib/libethercat_interface.so)
set(ec_interface_INCLUDE_DIRS /home/$ENV{USER}/ethercat_interface/include/)
set(ec_master /usr/local/lib/libethercat.so)

foreach(DEPENDENCY IN ITEMS ${THIS_PACKAGE_INCLUDE_DEPENDS})
    find_package(${DEPENDENCY} REQUIRED)
endforeach()

add_library(
  sr80_hardware
  SHARED
  src/sr80_hardware.cpp
  src/ethercat_controller.cpp
)
target_link_libraries(
  sr80_hardware
  ${ec_interface}
  ${ec_master}
  ${YAML_CPP_LIBRARIES}
)
target_include_directories(
  sr80_hardware
  PUBLIC
  include/
  ${ec_interface_INCLUDE_DIRS}
  ${YAML_CPP_INCLUDE_DIRS}
)
ament_target_dependencies(
  sr80_hardware
  ${THIS_PACKAGE_INCLUDE_DEPENDS}
)

pluginlib_export_plugin_description_file(hardware_interface sr80_hardware.xml)

install(
  TARGETS sr80_hardware
  DESTINATION lib
)
install(
  DIRECTORY include/
  DESTINATION include
)

ament_export_include_directories(
  include
)
ament_export_libraries(
  sr80_hardware
)
ament_export_dependencies(
  ${THIS_PACKAGE_INCLUDE_DEPENDS}
)

ament_package()
