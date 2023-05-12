# cmake_minimum_required(VERSION 2.6.4)
cmake_minimum_required(VERSION 3.5)
project(CFE_SAMPLE_SUB C)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Find requirements
if(NOT fastcdr_FOUND)
    find_package(fastcdr REQUIRED)
endif()
message("fastcdr_INCLUDE_DIR: ${fastcdr_INCLUDE_DIR}")

if(NOT fastrtps_FOUND)
    find_package(fastrtps REQUIRED)
endif()
message("fastrtps_INCLUDE_DIR: ${fastrtps_INCLUDE_DIR}")

include_directories(fsw/mission_inc)
include_directories(fsw/platform_inc)

aux_source_directory(fsw/src APP_SRC_FILES)

######################################################
# rclc
find_package(rcl REQUIRED)
find_package(rcutils REQUIRED)
find_package(rosidl_generator_c REQUIRED)
find_package(std_msgs REQUIRED)

if("${rcl_VERSION}" VERSION_LESS "1.0.0")
  message(STATUS "Found rcl version ${rcl_VERSION}, which belongs to Dashing or Eloquent")
  # Later, with CMake 3.12+ use:
  # add_compile_definitions(USE_RCL_WAIT_SET_IS_VALID_BACKPORT)
  add_definitions(-DUSE_RCL_WAIT_SET_IS_VALID_BACKPORT)
else()
  message(STATUS "Found rcl version ${rcl_VERSION}, which belongs to Foxy or later")
  find_package(rosidl_runtime_c REQUIRED)
endif()

add_library(rclc_lib
  fsw/src/rclc/init.c
  fsw/src/rclc/publisher.c
  fsw/src/rclc/subscription.c
  fsw/src/rclc/client.c
  fsw/src/rclc/service.c
  fsw/src/rclc/timer.c
  fsw/src/rclc/node.c
  fsw/src/rclc/executor_handle.c
  fsw/src/rclc/executor.c
  fsw/src/rclc/sleep.c
)
target_link_libraries(rclc_lib 
  ${rcl_LIBRARIES} 
  ${rcutils_LIBRARIES} 
  ${rosidl_generator_c_LIBRARIES}
  ${std_msgs_LIBRARIES}
)
include_directories(
  fsw/src/include 
  ${rcl_INCLUDE_DIRS} 
  ${rcutils_INCLUDE_DIRS}
  ${rosidl_generator_c_INCLUDE_DIRS}
  ${std_msgs_INCLUDE_DIRS}
)
######################################################

# Create the app module
add_cfe_app(sample_sub ${APP_SRC_FILES})

target_link_libraries(sample_sub
  ${PROTOBUF_LIBRARY}
  protobuf-c
  rclc_lib
)