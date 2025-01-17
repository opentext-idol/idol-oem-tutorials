#!/bin/sh

VERSION=25.1.0
PLATFORM=LINUX_X86_64

EDK_HOME=/opt/OpenText/EductionSDK_${VERSION}_${PLATFORM}
#PYTHON_HOME=

EDKLIBPATH=${EDK_HOME}/bin/libedk.so
export EDKLIBPATH

LICENSEKEY=${EDK_HOME}/combined.dat

CONFIG=test/config/test.cfg
INPUT=test/input/input.txt

ORIG=`pwd`

OUTPUT=${ORIG}/educed.EDK.JSON
rm ${OUTPUT}

cd ${EDK_HOME}/samples/eduction_from_config/resources

python3 -m edk.tool.extract -l ${LICENSEKEY} -i ${INPUT} -c ${CONFIG} > ${OUTPUT}

cd ${ORIG}
