#!/bin/sh

#MAVEN_HOME=
JAVA_HOME=/opt/OpenLogic/openlogic-openjdk-11.0.17+8-linux-x64

PATH=${JAVA_HOME}/bin:${PATH}
export PATH

mvn test > mvn_test.log
#mvn -e test > mvn_e_test.log
#mvn clean -X test > mvn_X_test.log