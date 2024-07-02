#!/bin/sh

JAVA_HOME=/opt/OpenLogic/openlogic-openjdk-11.0.17+8-linux-x64
#JAVA_HOME=/opt/homebrew/opt/openjdk@11
ANT_HOME=/opt/homebrew/bin
export JAVA_HOME
export ANT_HOME

PATH=${JAVA_HOME}/bin:${ANT_HOME}:${PATH}
export PATH

echo "Did you update Config.java per the lesson?"
read -p "Hit enter to continue"

ant jar