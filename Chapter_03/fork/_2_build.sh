#!/bin/bash

# Capture current directory into 'myDir'
myDir=${PWD##*/}

# Run the commands needed to build and push the program
echo
echo "setup build environment (needed each time you start a new terminal session)"
. /usr/local/oecore-x86_64/environment-setup-cortexa7-neon-vfpv4-oe-linux-gnueabi
echo
echo "running 'autogen.sh' ..."
source autogen.sh
echo
echo "running 'configure' ..."
source configure ${CONFIGURE_FLAGS}
echo
echo "running 'make' ..."
make
echo
echo "running 'adb push' ..."
adb push src/$myDir /CUSTAPP
