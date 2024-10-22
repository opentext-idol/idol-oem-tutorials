#!/bin/sh

VERSION=24.4.0
PLATFORM=LINUX_X86_64

EDK_HOME=/opt/OpenText/EductionSDK_${VERSION}_${PLATFORM}

JAVA_HOME=/opt/OpenLogic/openlogic-openjdk-11.0.17+8-linux-x64

PATH=${EDK_HOME}/bin:${JAVA_HOME}/bin:${PATH}
export PATH

LD_LIBRARY_PATH=${EDK_HOME}/bin
export LD_LIBRARY_PATH

#DYLIB_LIBRARY_PATH=$EDK_HOME/bin
#export DYLIB_LIBRARY_PATH

grammar=test
grammarIn=../resources/test/source/${grammar}.xml

grammarOut=${grammar}.ecr
rm ${grammarOut}

java -cp ${EDK_HOME}/bin/edk.jar:./target/classes com.autonomy.eduction.samples.Compile $grammarIn ${grammarOut} 