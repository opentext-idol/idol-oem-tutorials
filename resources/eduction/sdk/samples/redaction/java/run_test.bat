set VERSION=25.1.0
set PLATFORM=WINDOWS_X86_64

set EDK_HOME=C:\OpenText\EductionSDK_%VERSION%_%PLATFORM%

set JAVA_HOME=C:\Program Files\OpenLogic\openlogic-openjdk-11.0.16+8-windows-x64

set PATH=%EDK_HOME%\bin;%MAVEN_HOME%\bin;%JAVA_HOME%\bin

set configPath=..\resources\test\config\basic.cfg
rem set configPath=..\resources\test\config\entity_name.cfg
set inputFilePath=..\resources\test\input\input.txt

set outputFilePath=redacted.EDK.TXT
del %outputFilePath%

java -cp %EDK_HOME%\bin\edk.jar;.\target\classes com.autonomy.eduction.samples.Redact "%configPath%" "%inputFilePath%" "%outputFilePath%"