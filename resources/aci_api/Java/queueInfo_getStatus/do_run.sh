#!/bin/sh

VERSION=25.4.0

JAVA_HOME=/opt/OpenLogic/openlogic-openjdk-17.0.10+7-linux-x64
ACI_API_HOME=../../../../../IDOLJavaSDK_$VERSION

PATH=$MAVEN_HOME/bin:$JAVA_HOME/bin:$PATH
export JAVA_HOME
export PATH

PROGRAM=QueueinfoGetstatus
ACI_HOST=localhost
ACI_PORT=7010
QUEUE_NAME=ingest
TOKEN=MTI3LjAuMS4xOjcwMDA6SU5HRVNUOjE2NTIyNzkzNTUwMDY3OC0wNjM2OTE2ODA3
#TOKEN=

ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY=REPLACE_WITH_MY_LONG_KEY_STRING
export ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY

LIBS=../lib
CLASSPATH=$ACI_API_HOME/aci-api-release-$VERSION.jar:$LIBS/httpclient5-5.3.1.jar:$LIBS/httpclient-4.5.14.jar:$LIBS/commons-lang3-3.13.0.jar:$LIBS/slf4j-api-2.0.12.jar:$LIBS/jcl-over-slf4j-2.0.12.jar:$LIBS/commons-logging-1.2.jar:$LIBS/httpmime-4.5.14.jar:$LIBS/httpcore5-5.2.4.jar:$LIBS/httpcore-4.4.16.jar:$LIBS/commons-codec-1.16.1.jar:$LIBS/httpcore5-h2-5.2.4.jar:./target/$PROGRAM-1.0-SNAPSHOT.jar
java -cp $CLASSPATH com.autonomy.aci.samples.$PROGRAM $ACI_HOST $ACI_PORT $QUEUE_NAME $TOKEN

#java -jar target/$PROGRAM-1.0-SNAPSHOT-jar-with-dependencies.jar $ACI_HOST $ACI_PORT $QUEUE_NAME $TOKEN

#mvn exec:java "-Dexec.args=$MODE $ACI_HOST $ACI_PORT $QUEUE_NAME $TOKEN"