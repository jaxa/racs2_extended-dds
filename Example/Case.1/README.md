# RACS2 (ROS and cFS System 2) Example - Case.1 

## Overview

## Directory List

- ROS2/
  - sample_sub
    - The Example Subscriber for ROS2.
  - racs2_msg
    - The definition of custom message.
- cFS/
  - apps/sample_pub
    - The Example Publisher for cFS.
  - sample_defs 
    - The Example build settings for cFS.

## Setup

### Premise

- Not required.

### Procedure

- Preparation of execution environment on the ROS2 side.
  - Place directories in the ROS2 execution environment.
    ```
    cp -pr  racs2_extended-dds/Example/Case.1/ROS2/sample_sub [ROS2 project path]/src/
    cp -pr  racs2_extended-dds/Example/Case.1/ROS2/racs2_msg [ROS2 project path]/src/
    ```
  - Go to the top of the ROS2 project directory and execute the following build command
    ```
    colcon build --symlink-install
    ```

- Preparation of execution environment on the cFS side.
  - Place  directories in the cFS execution environment.
    ```
    cp -pr  racs2_extended-dds/Example/Case.1/cFS/apps/sample_pub [cFS project path]/apps/
    cp -pr  racs2_extended-dds/Example/Case.1/cFS/sample_defs/* [cFS project path]/sample_defs/
    ```
  
  - Edit L.205 of "[cFS project path]/sample_defs/default_osconfig.h" as follows,

    ```
    #define OSAL_DEBUG_PERMISSIVE_MODE
    ```
    
  - Go to the top of the cFS project directory and execute the following build command.
    ```
    make prep
    make
    make install
    ```

- Start the ROS2 nodes.
  ```
  cd [ROS2 project path]
  source install/setup.bash
  ros2 run  sample_sub  sample_sub
  ```

- Start the cFS applications, talker.
  ```
  cd [cFS project path]/build/exe/cpu1
  ./core-cpu1
  ```

- Check the messages that have been published and subscribed.

## How to exchange messages

- See `Document/HowToExchangeMessages.md`.

