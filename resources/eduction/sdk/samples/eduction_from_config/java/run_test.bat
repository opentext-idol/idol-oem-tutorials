echo off
set EDK_HOME=C:\Opentext\EductionSDK_24.2.0_WINDOWS_X86_64
set MAVEN_HOME=C:\Program Files\Apache\maven\apache-maven-3.8.3
set JAVA_HOME=C:\Program Files\Java\jdk1.8.0_321

set PATH=%EDK_HOME%\bin;%MAVEN_HOME%\bin;%JAVA_HOME%\bin

set configPath=..\resources\test\config\test.cfg
set inputFilePath=..\resources\test\input\input.txt
set outputFilePath=test_output_java.json

set MaxMatchesPerDoc=10000
set MinScore=0.4
set PostProcessThreshold=0.4
set EntityMatchLimit=

java -cp %EDK_HOME%\bin\edk.jar;.\target\classes com.autonomy.eduction.samples.FromConfig "%configPath%" "%inputFilePath%" "%outputFilePath%" %MaxMatchesPerDoc% %MinScore% %PostProcessThreshold% %EntityMatchLimit%