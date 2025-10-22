set VERSION=25.4.0

set JAVA_HOME=C:\Program Files\OpenLogic\openlogic-openjdk-17.0.10+7-windows-x64
set ACI_API_HOME=..\..\..\..\..\IDOLJavaSDK_%VERSION%

set PATH=%JAVA_HOME%\bin;%PATH%

set PROGRAM=FetchSynchronize
set ACI_HOST=localhost
set ACI_PORT=7020
set TASK_NAME=MyTask

set ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY=REPLACE_WITH_MY_LONG_KEY_STRING
rem set ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY=

set LIBS=..\lib
set CLASSPATH=%ACI_API_HOME%\aci-api-release-%VERSION%.jar;%LIBS%\httpclient5-5.3.1.jar;%LIBS%\httpclient-4.5.14.jar;%LIBS%\commons-lang3-3.13.0.jar;%LIBS%\slf4j-api-2.0.12.jar;%LIBS%\jcl-over-slf4j-2.0.12;%LIBS%\commons-logging-1.2.jar;%LIBS%\httpmime-4.5.14.jar;%LIBS%\httpcore5-5.2.4.jar;%LIBS%\httpcore-4.4.16.jar;%LIBS%\commons-codec-1.16.1.jar;%LIBS%\httpcore5-h2-5.2.4.jar;.\target\%PROGRAM%-1.0-SNAPSHOT.jar
java -cp %CLASSPATH% com.autonomy.aci.samples.%PROGRAM% %ACI_HOST% %ACI_PORT% %TASK_NAME%

rem java -jar target/%PROGRAM%-1.0-SNAPSHOT-jar-with-dependencies.jar %ACI_HOST% %ACI_PORT% %TASK_NAME%

rem mvn exec:java -Dexec.args="%ACI_HOST% %ACI_PORT% %TASK_NAME%"