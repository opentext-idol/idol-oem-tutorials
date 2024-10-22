#!/bin/sh

set VERSION=24.4.0
set PLATFORM=LINUX_X86_64

KEYVIEW_BIN_FOLDER=/opt/OpenText/KeyviewFilterSDK_${VERSION}_${PLATFORM}/${PLATFORM}/bin
IDOL_OEM_TUTORIALS_HOME=/opt/OpenText/idol-oem-tutorials

JAVA_HOME=/opt/OpenLogic/openlogic-openjdk-11.0.17+8-linux-x64
#JAVA_HOME=/opt/homebrew/opt/openjdk@11
PATH=$JAVA_HOME/bin:$PATH
export PATH

INPUT_FILEPATH=${IDOL_OEM_TUTORIALS_HOME}/resources/keyview_filter/KeyViewFilterSDK_12.12.0_ReleaseNotes_en.rar
TEXT_OUTPUT_FILEPATH=${INPUT_FILEPATH}.KV_${VERSION}_TEXT.TXT

java -classpath ${KEYVIEW_BIN_FOLDER}/../../javaapi/KeyView.jar:build/jar/StreamingTutorial.jar -Djava.library.path=${KEYVIEW_BIN_FOLDER} tutorial.StreamingTutorial ${INPUT_FILEPATH} ${TEXT_OUTPUT_FILEPATH}
