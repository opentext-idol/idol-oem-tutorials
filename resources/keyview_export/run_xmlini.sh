#!/bin/sh

JAVA_HOME=/usr/lib/jvm/java-11-openjdk-amd64

PATH=$JAVA_HOME/bin:$PATH
export PATH

VERSION=25.4.0
PLATFORM=LINUX_X86_64
#PLATFORM=MACOS_M1

XMLEXPORT_HOME=/opt/OpenText/KeyviewExportSDK_${VERSION}_${PLATFORM}

XMLEXPORT_INI_HOME=${XMLEXPORT_HOME}/xmlexport/programs/ini
XMLEXPORT_INI_FILE=xml1file
#XMLEXPORT_INI_FILE=xml_index

INPUT=${XMLEXPORT_HOME}/testdocs/Annual_Report.docx
#INPUT=${XMLEXPORT_HOME}/testdocs/Investment_Portfolio.xlsx
#INPUT=${XMLEXPORT_HOME}/testdocs/freezer2.ppt

OUTPUT=${INPUT}.${XMLEXPORT_INI_FILE}.XML

echo Input file:  ${INPUT}
echo Output file:  ${OUTPUT}
echo Ini file: ${XMLEXPORT_INI_HOME}/${XMLEXPORT_INI_FILE}.ini
echo

ORIG_DIR=`pwd`
cd ${XMLEXPORT_HOME}/${PLATFORM}/bin
./xmlini ${XMLEXPORT_INI_HOME}/${XMLEXPORT_INI_FILE}.ini ${INPUT} ${OUTPUT}
cd ${ORIG_DIR}