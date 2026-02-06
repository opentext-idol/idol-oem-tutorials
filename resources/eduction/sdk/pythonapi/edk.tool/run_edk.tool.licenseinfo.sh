#!/bin/sh

VERSION=26.1.0
PLATFORM=LINUX_X86_64

#PYTHON_HOME=
PYTHON_EXE=python3

EDK_HOME=/opt/OpenText/EductionSDK_${VERSION}_${PLATFORM}
EDKLIBPATH=${EDK_HOME}/bin/libedk.so
export EDKLIBPATH

LICENSEKEY=${EDK_HOME}/licensekey.dat

${PYTHON_EXE} -m edk.tool.licenseinfo -l ${LICENSEKEY}
