#!/bin/sh

VERSION=25.1.0
PLATFORM=LINUX_X86_64

EDK_HOME=/opt/OpenText/EductionSDK_${VERSION}_${PLATFORM}

JAVA_HOME=/opt/OpenLogic/openlogic-openjdk-11.0.17+8-linux-x64

PATH=${EDK_HOME}/bin:${JAVA_HOME}/bin:${PATH}
export PATH

LD_LIBRARY_PATH=${EDK_HOME}/bin
export LD_LIBRARY_PATH

#DYLIB_LIBRARY_PATH=$EDK_HOME/bin
#export DYLIB_LIBRARY_PATH

configPath=../resources/test/config/test.cfg
inputFilePath=../resources/test/input/input.txt

outputFilePath=educed.EDK.JSON
rm ${outputFilePath}

sessionConfigPath=../resources/test/config/test_session.cfg
EntityMatchLimit=''

java -cp ${EDK_HOME}/bin/edk.jar:./target/classes com.autonomy.eduction.samples.FromConfig $configPath ${inputFilePath} ${outputFilePath} ${sessionConfigPath} ${EntityMatchLimit}
