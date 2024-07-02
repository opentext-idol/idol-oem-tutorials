#!/bin/sh

VERSION=24.3.0

JAVA_HOME=/opt/OpenLogic/openlogic-openjdk-11.0.17+8-linux-x64
ACI_API_HOME=../../../../../IDOLJavaSDK_$VERSION

PATH=$MAVEN_HOME/bin:$JAVA_HOME/bin:$PATH
export JAVA_HOME
export PATH

PROGRAM=MSProcess
ACI_HOST=localhost
ACI_PORT=14000
CONFIG_NAME=REPLACE_WITH_CONFIG_NAME
SOURCE_FILE_PATH=REPLACE_WITH_SOURCE_FILE_PATH

ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY=REPLACE_WITH_MY_LONG_KEY_STRING
export ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY

LIBS=../lib
CLASSPATH=$ACI_API_HOME/aci-api-release-$VERSION.jar:$LIBS/httpclient-4.5.13.jar:$LIBS/commons-lang-2.6.jar:$LIBS/slf4j-api-1.7.9.jar:$LIBS/jcl-over-slf4j-1.7.9.jar:$LIBS/commons-logging-1.2.jar:$LIBS/httpmime-4.5.13.jar:$LIBS/httpcore-4.4.13.jar:./target/$PROGRAM-1.0-SNAPSHOT.jar
java -cp $CLASSPATH com.autonomy.aci.samples.$PROGRAM $ACI_HOST $ACI_PORT $CONFIG_NAME "$SOURCE_FILE_PATH"

#java -jar target/$PROGRAM-1.0-SNAPSHOT-jar-with-dependencies.jar $ACI_HOST $ACI_PORT $CONFIG_NAME "$SOURCE_FILE_PATH"

#mvn exec:java "-Dexec.args=$MODE $ACI_HOST $ACI_PORT $CONFIG_NAME '$SOURCE_FILE_PATH'"