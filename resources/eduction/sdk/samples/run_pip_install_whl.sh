#!/bin/sh

VERSION=25.4.0
PLATFORM=LINUX_X86_64

EDK_HOME=/opt/OpenText/EductionSDK_${VERSION}_${PLATFORM}

EDKLIBPATH=%EDK_HOME%\bin\edk.dll
export EDKLIBPATH

PIP_EXE=pip3

cd ${EDK_HOME}
${PIP_EXE} install bin/edk-${VERSION}-py3-none-any.whl