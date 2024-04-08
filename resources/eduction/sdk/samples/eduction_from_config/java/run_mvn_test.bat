set EDK_HOME=C:\Opentext\EductionSDK_24.2.0_WINDOWS_X86_64
set MAVEN_HOME=C:\Program Files\Apache\maven\apache-maven-3.8.3
set JAVA_HOME=C:\Program Files\Java\jdk1.8.0_321

set PATH=%EDK_HOME%\bin;%MAVEN_HOME%\bin;%JAVA_HOME%\bin;%SYSTEMRoot%\system32

mvn test > mvn_test.log
rem mvn -e test > mvn_e_test.log
rem mvn clean -X test > mvn_X_test.log

