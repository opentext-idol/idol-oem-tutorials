#!/bin/sh

VERSION=24.4.0
PLATFORM=LINUX_X86_64

EDK_HOME=/opt/OpenText/EductionSDK_${VERSION}_${PLATFORM}
EDK_GRAMMARS_HOME=${EDK_HOME}/../EductionGrammars_${VERSION}_COMMON
#PYTHON_HOME=

EDKLIBPATH=${EDK_HOME}/bin/libedk.so
export EDKLIBPATH

LICENSEKEY=${EDK_HOME}/combined.dat
GRAMMAR_FILE=${EDK_GRAMMARS_HOME}/pii/national_id.ecr

python3 -m edk.tool.list -l ${LICENSEKEY} -g ${GRAMMAR_FILE}