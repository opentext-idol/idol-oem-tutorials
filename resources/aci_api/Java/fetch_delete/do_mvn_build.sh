#!/bin/sh

MAVEN_HOME=/opt/Apache/maven/apache-maven-3.8.3
JAVA_HOME=/opt/OpenLogic/openlogic-openjdk-11.0.17+8-linux-x64

PATH=$MAVEN_HOME/bin:$JAVA_HOME/bin:$PATH
export JAVA_HOME
export PATH
env

mvn compile package
