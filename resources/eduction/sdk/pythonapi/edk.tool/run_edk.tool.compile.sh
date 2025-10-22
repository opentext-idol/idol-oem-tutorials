#!/bin/sh

VERSION=25.4.0
PLATFORM=LINUX_X86_64

#PYTHON_HOME=
PYTHON_EXE=python3

EDK_HOME=/opt/OpenText/EductionSDK_${VERSION}_${PLATFORM}
EDKLIBPATH=${EDK_HOME}/bin/libedk.so
export EDKLIBPATH

LICENSEKEY=${EDK_HOME}/combined.dat

INPUT=${EDK_HOME}/samples/compile/resources/test/source/test.xml

OUTPUT=test.ecr
rm %{OUTPUT}

${PYTHON_EXE} -m edk.tool.compile -l ${LICENSEKEY} -i ${INPUT} -o ${OUTPUT}
