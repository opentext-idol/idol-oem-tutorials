#!/bin/sh

VERSION=25.4.0
PLATFORM=LINUX_X86_64

#PYTHON_HOME=
PYTHON_EXE=python3

EDK_HOME=/opt/OpenText/EductionSDK_${VERSION}_${PLATFORM}
EDKLIBPATH=${EDK_HOME}/bin/libedk.so
export EDKLIBPATH
EDK_GRAMMARS_HOME/opt/OpenText/EductionGrammars_%VERSION%_COMMON

LICENSEKEY=${EDK_HOME}/combined.dat

GRAMMAR_FILE=${EDK_GRAMMARS_HOME}/pii/national_id.ecr

${PYTHON_EXE} -m edk.tool.list -l ${LICENSEKEY} -g ${GRAMMAR_FILE}