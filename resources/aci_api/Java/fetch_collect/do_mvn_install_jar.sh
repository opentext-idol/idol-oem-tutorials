#!/bin/sh

ACI_API_HOME=../../../../../../IDOLJavaSDK_12.10.0
MAVEN_HOME=/opt/Apache/maven/apache-maven-3.8.3

PATH=$MAVEN_HOME/bin:$PATH

VERSION=12.10.0

env

mvn install:install-file -Dfile=$ACI_API_HOME/idol-aci-client-12.10.0-bin/aci-api-release-12.10.0.jar -DgroupId=com.autonomy.aci -DartifactId=aci -Dversion=$VERSION -Dpackaging=jar -DgeneratePom=true
