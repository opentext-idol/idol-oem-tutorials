#!/bin/sh

VERSION=25.4.0
PLATFORM=LINUX_X86_64

EDK_HOME=/opt/OpenText/EductionSDK_${VERSION}_${PLATFORM}
#MAVEN_HOME=
JAVA_HOME=/opt/OpenLogic/openlogic-openjdk-11.0.17+8-linux-x64

PATH=${EDK_HOME}/bin:${JAVA_HOME}/bin:${PATH}
export PATH

mvn test > mvn_test.log
#mvn -e test > mvn_e_test.log
#mvn clean -X test > mvn_X_test.log