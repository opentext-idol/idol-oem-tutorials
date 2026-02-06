set MAVEN_HOME=C:\Program Files\Apache\maven\apache-maven-3.9.11
set JAVA_HOME=C:\Program Files\Microsoft\jdk-21.0.8.9-hotspot

set PATH=%MAVEN_HOME%\bin;%JAVA_HOME%\bin;%SYSTEMRoot%\system32

mvn test > mvn_test.log
rem mvn -e test > mvn_e_test.log
rem mvn clean -X test > mvn_X_test.log

