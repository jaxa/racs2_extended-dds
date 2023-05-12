# RACS2 (ROS and cFS System 2) Extended-DDS

## Overview

This repository is a collection of software and examples that message communication between Robot Operating System 2 (ROS2) nodes and core flight executives (cFE).  cFE is a core component of NASA-supplied spacecraft software, Core Flight System (CFS).

This project provides ROS2/cFE examples with rclc-implemented cFS apps

**If you would like to report a bug or have a request for an update, please contact us. We will respond on demand.**

## License

This project is under the Apache 2.0 license. See LICENSE text file.

## Release Notes

- RACS2 (ROS2/cFE) project suite 1.0.0 is released.

## Directory List

- ROS2 :
  - [TBU] RACS2 Extended-DDS software for ROS2.
- cFS :
  - [TBU] RACS2 Extended-DDS software for cFS.
- Document :
  - [TBU] Documents of RACS2.
- Example :
  - Example software of RACS2.
- Misc :
  - Other Information of RACS2.

## Dependency

- Base OS :
  - Ubuntu 20.04 LTS
- ROS2 :
  - "ros-foxy" package.
  - [rclc](https://github.com/ros2/rclc)
- [cFS Aquila](https://github.com/nasa/cFS/releases/tag/v6.7.0a): 
  - cFE 6.7.0a
  - OSAL v5.0.0


## Setup

### Premise

- ROS2 and cFS shall be installed on the OS.
  - See below.
    - [ROS2 Installation](https://docs.ros.org/en/foxy/Installation/Ubuntu-Install-Debians.html)
    - [cFS Installation](https://github.com/nasa/cFS)

### Procedure

- Preparing for Protocol Buffers.
  - C/C++ :
    ```
    sudo apt install -y libwebsockets-dev protobuf-c-compiler libprotobuf-c-dev
    ```
  - Python :
    ```
    pip install protobuf
    ```

- git clone the [RACS2 Extended-DDS](https://github.com/jaxa/racs2_extended-dds.git) source code.  

- Preparation of execution environment on the cFS side.  
  - Go to the top of the cFS project directory and execute the following build command
    ```
    git clone --recursive https://github.com/nasa/cFS.git
    git checkout v6.7.0a
    git submodule update --init
    ```

  - Go to the top of the cFS project directory and execute the following build command
    ```
    cp cfe/cmake/Makefile.sample Makefile
    cp -r cfe/cmake/sample_defs sample_defs
    ```

  - Go to the top of the cFS project directory and execute the following build command
    ```
    make prep
    make
    make install
    ```

- Preparation of execution environment on the ROS2 side.   
  - Go to the top of the ROS2 project directory and execute the following build command
    ```
    colcon build --symlink-install
    ```

- Start the cFS application.
  ```
  cd [cFS project path]/build/exe/cpu1
  ./core-cpu1
  ```

- Start the ROS2 publishers and subscribers.

- Start the cFS publishers and subscribers.


## About Example

- See `Example/README.md`.

## How to exchange messages

- [TBU]

## Reference 

* [Hiroki Kato, et al. "RACS2: the ROS2 and cFS System, launched" Flight Software Workshop 2023.](https://drive.google.com/file/d/1VBsiUEW6Z8pG8LvbM7lEyZMRMz9w-sjX/view?usp=share_link)
