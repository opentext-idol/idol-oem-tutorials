#!/bin/sh

VERSION=25.4.0
PLATFORM=LINUX_X86_64

EDK_HOME=/opt/OpenText/EductionSDK_${VERSION}_${PLATFORM}

JAVA_HOME=/opt/OpenLogic/openlogic-openjdk-11.0.17+8-linux-x64

PATH=${EDK_HOME}/bin:${JAVA_HOME}/bin:${PATH}
export PATH

LD_LIBRARY_PATH=${EDK_HOME}/bin
export LD_LIBRARY_PATH

#DYLIB_LIBRARY_PATH=$EDK_HOME/bin
#export DYLIB_LIBRARY_PATH

configPath=../resources/test/config/basic.cfg
#configPath=../resources/test/config/entity_name.cfg
inputFilePath=../resources/test/input/input.txt

outputFilePath=redacted.EDK.TXT
rm ${outputFilePath}


java -Djava.library.path=${EDK_HOME}/bin -cp ${EDK_HOME}/bin/edk.jar:./target/classes com.autonomy.eduction.samples.Redact ${configPath} ${inputFilePath} ${outputFilePath}