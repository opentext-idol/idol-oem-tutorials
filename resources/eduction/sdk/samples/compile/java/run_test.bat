echo off
set EDK_HOME=C:\OpenText\EductionSDK_24.2.0_WINDOWS_X86_64
set MAVEN_HOME=C:\Program Files\Apache\maven\apache-maven-3.8.3
set JAVA_HOME=C:\Program Files\Java\jdk1.8.0_321

set PATH=%EDK_HOME%\bin;%MAVEN_HOME%\bin;%JAVA_HOME%\bin

set grammar=test
set grammarIn=..\resources\test\source\%grammar%.xml
set grammarOut=..\resources\test\%grammar%.ecr

del %grammarOut%
java -cp %EDK_HOME%\bin\edk.jar;%EDK_HOME%\samples\compile\java\target\classes com.autonomy.eduction.samples.Compile "%grammarIn%" "%grammarOut%"