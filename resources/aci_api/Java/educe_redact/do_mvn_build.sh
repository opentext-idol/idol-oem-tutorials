#!/bin/sh

MAVEN_HOME=/opt/Apache/maven/apache-maven-3.8.3
#JAVA_HOME=/opt/Java/jdk1.8.0_321

#PATH=$MAVEN_HOME/bin:$JAVA_HOME/bin:$PATH
PATH=$MAVEN_HOME/bin:$PATH

env

mvn compile package
