set VERSION=23.2.0

set JAVA_HOME=C:\Program Files\OpenLogic\openlogic-openjdk-11.0.16+8-windows-x64
set ACI_API_HOME=..\..\..\..\..\IDOLJavaSDK_%VERSION%
set PATH=%JAVA_HOME%\bin;%PATH%

set PROGRAM=EduceRedact
set ACI_HOST=localhost
set ACI_PORT=13000
set MODE=e
set ENTITIES_CSV=REPLACE_WITH_ENTITIES
rem set ENTITIES_CSV=number/cc
set TEXT=REPLACE WITH TEXT
rem set TEXT=378282246310005

set ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY=REPLACE_WITH_MY_LONG_KEY_STRING
rem set ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY=

set LIBS=..\lib
set CLASSPATH=%ACI_API_HOME%\aci-api-release-%VERSION%.jar;%LIBS%\httpclient-4.5.13.jar;%LIBS%\commons-lang-2.6.jar;%LIBS%\slf4j-api-1.7.9.jar;%LIBS%\jcl-over-slf4j-1.7.9.jar;%LIBS%\commons-logging-1.2.jar;%LIBS%\httpmime-4.5.13.jar;%LIBS%\httpcore-4.4.13.jar;%LIBS%\commons-codec-1.11.jar;.\target\%PROGRAM%-1.0-SNAPSHOT.jar
java -cp %CLASSPATH% com.autonomy.aci.samples.%PROGRAM% %MODE% %ACI_HOST% %ACI_PORT% "%ENTITIES_CSV%" "%TEXT%"

rem java -jar target/%PROGRAM%-1.0-SNAPSHOT-jar-with-dependencies.jar %MODE% %ACI_HOST% %ACI_PORT% "%ENTITIES_CSV%" "%TEXT%"

rem mvn exec:java -Dexec.args="%MODE% %ACI_HOST% %ACI_PORT% '%ENTITIES_CSV%' '%TEXT%'"