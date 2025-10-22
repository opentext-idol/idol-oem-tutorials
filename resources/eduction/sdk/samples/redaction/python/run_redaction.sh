#/bin/sh

VERSION=25.4.0
PLATFORM=LINUX_X86_64

EDK_HOME=/opt/OpenText/EductionSDK_${VERSION}_${PLATFORM}
#PYTHON_HOME=

EDKLIBPATH=${EDK_HOME}/bin/libedk.so
export EDKLIBPATH

EDK_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH=${EDK_HOME}/licensekey.dat
EDK_SAMPLE_PROGRAM_VERSIONKEY_FROM_FILEPATH=${EDK_HOME}/versionkey.dat
export EDK_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH
export EDK_SAMPLE_PROGRAM_VERSIONKEY_FROM_FILEPATH

CONFIG=test/config/basic.cfg
#CONFIG=test/config/entity_name.cfg
INPUT=test/input/input.txt

ORIG=`pwd`

OUTPUT=${ORIG}/redacted.EDK.TXT
rm ${OUTPUT}

cd ../resources

python3 ${ORIG}/redaction.py ${CONFIG} ${INPUT} ${OUTPUT}

cd ${ORIG}
