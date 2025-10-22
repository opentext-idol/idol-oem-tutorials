#!/bin/sh

VERSION=25.4.0
PLATFORM=LINUX_X86_64

#PYTHON_HOME=
PYTHON_EXE=python3

EDK_HOME=/opt/OpenText/EductionSDK_${VERSION}_${PLATFORM}
EDKLIBPATH=${EDK_HOME}/bin/libedk.so
export EDKLIBPATH

LICENSEKEY=${EDK_HOME}/combined.dat

CONFIG=test/config/test.cfg
INPUT=test/input/input.txt

ORIG=`pwd`

OUTPUT=${ORIG}/educed.EDK.JSON
rm ${OUTPUT}

cd ${EDK_HOME}/samples/eduction_from_config/resources

${PYTHON_EXE} -m edk.tool.extract -l ${LICENSEKEY} -i ${INPUT} -c ${CONFIG} > ${OUTPUT}

cd ${ORIG}
