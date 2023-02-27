#!/bin/sh

JAVA_HOME=/opt/OpenLogic/openlogic-openjdk-11.0.17+8-linux-x64

PATH=$MAVEN_HOME/bin:$JAVA_HOME/bin:$PATH
export JAVA_HOME
export PATH

PROGRAM=FetchIdentifiers
ACI_HOST=localhost
ACI_PORT=7010
TASK_NAME=MyTask

ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY=REPLACE_WITH_MY_LONG_KEY_STRING
export ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY

java -jar target/$PROGRAM-1.0-SNAPSHOT-jar-with-dependencies.jar $ACI_HOST $ACI_PORT $TASK_NAME