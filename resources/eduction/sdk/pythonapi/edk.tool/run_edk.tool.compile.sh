#!/bin/sh

VERSION=24.3.0
PLATFORM=LINUX_X86_64

EDK_HOME=/opt/OpenText/EductionSDK_${VERSION}_${PLATFORM}
EDK_GRAMMARS_HOME=${EDK_HOME}/../EductionGrammars_${VERSION}_COMMON
#PYTHON_HOME=

EDKLIBPATH=${EDK_HOME}/bin/libedk.so
export EDKLIBPATH

LICENSEKEY=${EDK_HOME}/combined.dat

INPUT=${EDK_HOME}/samples/compile/resources/test/source/test.xml

OUTPUT=test.ecr
rm %{OUTPUT}

python3 -m edk.tool.compile -l ${LICENSEKEY} -i ${INPUT} -o ${OUTPUT}
