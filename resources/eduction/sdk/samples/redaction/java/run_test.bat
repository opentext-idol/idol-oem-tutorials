echo off
set EDK_HOME=C:\OpenText\EductionSDK_24.2.0_WINDOWS_X86_64
set MAVEN_HOME=C:\Program Files\Apache\maven\apache-maven-3.8.3
set JAVA_HOME=C:\Program Files\Java\jdk1.8.0_321

set PATH=%EDK_HOME%\bin;%MAVEN_HOME%\bin;%JAVA_HOME%\bin

set configPath=..\resources\test\config\basic.cfg
rem set configPath=..\resources\test\config\entity_name.cfg
set inputFilePath=..\resources\test\input\input.txt
set outputFilePath=test_redact_java.txt

del %outputFilePath%
java -cp %EDK_HOME%\bin\edk.jar;.\target\classes com.autonomy.eduction.samples.Redact "%configPath%" "%inputFilePath%" "%outputFilePath%"