#!/bin/bash

export WORKSPACE_ROOT=/home/leo/Workspace2/iot-onion-remote-switch

rm -r -f ${WORKSPACE_ROOT}/build/toolchain
mkdir ${WORKSPACE_ROOT}/build/toolchain
cd ${WORKSPACE_ROOT}/build/toolchain

# Set up environment variables in preparation for the builds to follow
#
export TOOLCHAIN_ROOT=${WORKSPACE_ROOT}/build/toolchain
source ${WORKSPACE_ROOT}/build/set-toolchain-mips-openwrt-linux.sh

# Download the OpenWRT cross-compile toolchain for Onion Omega (Atheros AR7xxx/AR9xxx)
# Instructions on how to build it can be found here: http://onioniot.github.io/wiki/Tutorials/Cross-Compile
#
wget https://dalonzo.blob.core.windows.net/public/toolchain-mips_34kc_gcc-4.8-linaro_uClibc-0.9.33.2.tar.gz
tar -xvf toolchain-mips_34kc_gcc-4.8-linaro_uClibc-0.9.33.2.tar.gz

# Download OpenSSL source and expand it
wget https://www.openssl.org/source/openssl-1.0.2o.tar.gz
tar -xvf openssl-1.0.2o.tar.gz

# Download cURL source and expand it
wget http://curl.haxx.se/download/curl-7.60.0.tar.gz
tar -xvf curl-7.60.0.tar.gz

# Download the Linux utilities for libuuid and expand it
wget https://mirrors.edge.kernel.org/pub/linux/utils/util-linux/v2.32/util-linux-2.32-rc2.tar.gz
tar -xvf util-linux-2.32-rc2.tar.gz

# Build OpenSSL
cd openssl-1.0.2o
./Configure linux-generic32 shared --prefix=${TOOLCHAIN_PREFIX} --openssldir=${TOOLCHAIN_PREFIX}
make
make install
cd ..

# Build cURL
cd curl-7.60.0
./configure --with-sysroot=${TOOLCHAIN_SYSROOT} --prefix=${TOOLCHAIN_PREFIX} --target=${TOOLCHAIN_NAME} --with-ssl --with-zlib --host=${TOOLCHAIN_NAME} --build=x86_64-pc-linux-uclibc
make
make install
cd ..

# Build uuid
cd util-linux-2.32-rc2
./configure --prefix=${TOOLCHAIN_PREFIX} --with-sysroot=${TOOLCHAIN_SYSROOT} --target=${TOOLCHAIN_NAME} --host=${TOOLCHAIN_NAME} --disable-all-programs  --disable-bash-completion --enable-libuuid
make
make install
cd ..

# To build the Azure IoT SDK we need to create a cmake toolchain file. This tells cmake to use the tools in the
# toolchain rather than those on the host
#
# Create a working directory for the cmake operations
rm -r -f ${WORKSPACE_ROOT}/submodules/azure-iot-sdk-c/cmake
mkdir ${WORKSPACE_ROOT}/submodules/azure-iot-sdk-c/cmake
cd ${WORKSPACE_ROOT}/submodules/azure-iot-sdk-c/cmake

# Create a cmake toolchain file on the fly
echo "SET(CMAKE_SYSTEM_NAME Linux)     # this one is important" > toolchain.cmake
echo "SET(CMAKE_SYSTEM_VERSION 1)      # this one not so much" >> toolchain.cmake
echo "SET(CMAKE_SYSROOT ${TOOLCHAIN_SYSROOT})" >> toolchain.cmake
echo "SET(CMAKE_C_COMPILER ${TOOLCHAIN_EXES}/${TOOLCHAIN_NAME}-gcc)" >> toolchain.cmake
echo "SET(CMAKE_CXX_COMPILER ${TOOLCHAIN_EXES}/${TOOLCHAIN_NAME}-g++)" >> toolchain.cmake
echo "SET(CMAKE_FIND_ROOT_PATH $ENV{TOOLCHAIN_SYSROOT})" >> toolchain.cmake
echo "SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)" >> toolchain.cmake
echo "SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)" >> toolchain.cmake
echo "SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)" >> toolchain.cmake
echo "SET(set_trusted_cert_in_samples true CACHE BOOL \"Force use of TrustedCerts option\" FORCE)" >> toolchain.cmake

# Build the Azure IoT SDK. This will use the OpenSSL, cURL and uuid binaries that we built before
cmake -DCMAKE_TOOLCHAIN_FILE=toolchain.cmake -DCMAKE_INSTALL_PREFIX=${TOOLCHAIN_PREFIX} ..
make
make install
