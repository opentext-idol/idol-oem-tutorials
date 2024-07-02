set MAVEN_HOME=C:\Program Files\Apache\maven\apache-maven-3.8.3
set JAVA_HOME=C:\Program Files\OpenLogic\openlogic-openjdk-11.0.16+8-windows-x64

set PATH=%MAVEN_HOME%\bin;%JAVA_HOME%\bin;%SYSTEMRoot%\system32

mvn test > mvn_test.log
rem mvn -e test > mvn_e_test.log
rem mvn clean -X test > mvn_X_test.log

