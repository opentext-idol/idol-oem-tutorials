#!/bin/sh

VERSION=24.3.0

JAVA_HOME=/opt/OpenLogic/openlogic-openjdk-11.0.17+8-linux-x64
ACI_API_HOME=../../../../../IDOLJavaSDK_$VERSION

PATH=$MAVEN_HOME/bin:$JAVA_HOME/bin:$PATH
export JAVA_HOME
export PATH

PROGRAM=EduceRedact
ACI_HOST=localhost
ACI_PORT=13000
MODE=e
ENTITIES_CSV=REPLACE_WITH_ENTITIES
#ENTITIES_CSV=number/cc
TEXT="REPLACE WITH TEXT"
#TEXT=378282246310005

ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY=REPLACE_WITH_MY_LONG_KEY_STRING
export ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY

LIBS=../lib
CLASSPATH=$ACI_API_HOME/aci-api-release-$VERSION.jar:$LIBS/httpclient-4.5.13.jar:$LIBS/commons-lang-2.6.jar:$LIBS/slf4j-api-1.7.9.jar:$LIBS/jcl-over-slf4j-1.7.9.jar:$LIBS/commons-logging-1.2.jar:$LIBS/httpmime-4.5.13.jar:$LIBS/httpcore-4.4.13.jar:./target/$PROGRAM-1.0-SNAPSHOT.jar
java -cp $CLASSPATH com.autonomy.aci.samples.$PROGRAM $MODE $ACI_HOST $ACI_PORT "$ENTITIES_CSV" "$TEXT"

#java -jar target/$PROGRAM-1.0-SNAPSHOT-jar-with-dependencies.jar $MODE $ACI_HOST $ACI_PORT "$ENTITIES_CSV" "$TEXT"

#mvn exec:java "-Dexec.args=$MODE $ACI_HOST $ACI_PORT '$ENTITIES_CSV' '$TEXT'"