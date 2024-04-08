#!/bin/sh

# Set the location of JAVA_HOME and KEYVIEW_BIN_FOLDER for your environment.
JAVA_HOME=/opt/homebrew/opt/openjdk@11
PATH=$JAVA_HOME/bin:$PATH
export PATH

KEYVIEW_BIN_FOLDER=/Users/ec2-user/OpenText/KeyviewFilterSDK_24.2.0_MACOS_M1/MACOS_M1/bin

java -classpath $KEYVIEW_BIN_FOLDER/../../javaapi/KeyView.jar:build/jar/StreamingTutorial.jar -Djava.library.path=$KEYVIEW_BIN_FOLDER tutorial.StreamingTutorial $1 $2
