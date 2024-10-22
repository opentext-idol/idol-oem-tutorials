set VERSION=24.4.0
set PLATFORM=WINDOWS_X86_64

set EDK_HOME=C:\OpenText\EductionSDK_%VERSION%_%PLATFORM%

set JAVA_HOME=C:\Program Files\OpenLogic\openlogic-openjdk-11.0.16+8-windows-x64

set PATH=%EDK_HOME%\bin;%MAVEN_HOME%\bin;%JAVA_HOME%\bin

set configPath=..\resources\test\config\test.cfg
set inputFilePath=..\resources\test\input\input.txt

set outputFilePath=educed.EDK.JSON
del %outputFilePath%

set sessionConfigPath=..\resources\test\config\test_session.cfg
set EntityMatchLimit=

java -cp %EDK_HOME%\bin\edk.jar;.\target\classes com.autonomy.eduction.samples.FromConfig "%configPath%" "%inputFilePath%" "%outputFilePath%" "%sessionConfigPath%" %EntityMatchLimit%