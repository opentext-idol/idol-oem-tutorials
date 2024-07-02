#!/bin/sh

VERSION=24.3.0
PLATFORM=LINUX_X86_64

EDK_HOME=/opt/OpenText/EductionSDK_${VERSION}_${PLATFORM}
JAVA_HOME=/opt/OpenLogic/openlogic-openjdk-11.0.17+8-linux-x64

PATH=${JAVA_HOME}/bin:${PATH}
export PATH

VERSION=24.3.0

mvn install:install-file -Dfile=${EDK_HOME}/bin/edk.jar -DgroupId=com.autonomy.eduction -DartifactId=edk -Dversion=${VERSION} -Dpackaging=jar -DgeneratePom=true
