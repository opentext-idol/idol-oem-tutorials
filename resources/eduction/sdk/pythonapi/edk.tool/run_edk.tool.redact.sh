#!/bin/sh

VERSION=24.3.0
PLATFORM=LINUX_X86_64

EDK_HOME=/opt/OpenText/EductionSDK_${VERSION}_${PLATFORM}
EDK_GRAMMARS_HOME=${EDK_HOME}/../EductionGrammars_${VERSION}_COMMON
#PYTHON_HOME=

EDKLIBPATH=${EDK_HOME}/bin/libedk.so
export EDKLIBPATH

LICENSEKEY=${EDK_HOME}/combined.dat

CONFIG=test/config/basic.cfg
#CONFIG=test/config/entity_name.cfg
INPUT=test/input/input.txt

ORIG=`pwd`

OUTPUT=${ORIG}/redacted.EDK.TXT
rm %{OUTPUT}

cd ${EDK_HOME}/samples/redaction/resources

python3 -m edk.tool.redact -l ${LICENSEKEY} -i ${INPUT} -c ${CONFIG} > ${OUTPUT}

cd ${ORIG}
