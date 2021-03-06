#!/bin/bash

export WORKSPACE_ROOT=/home/leo/Workspace2/iot-onion-remote-switch
export TOOLCHAIN_ROOT=${WORKSPACE_ROOT}/build/toolchain

# Set up environment variables in preparation for the build to follow
source ${WORKSPACE_ROOT}/build/set-toolchain-mips-openwrt-linux.sh

# Build the application
mkdir ${WORKSPACE_ROOT}/cmake
cd ${WORKSPACE_ROOT}/cmake
cmake -DCMAKE_TOOLCHAIN_FILE=${WORKSPACE_ROOT}/submodules/azure-iot-sdk-c/cmake/toolchain.cmake ..
make
