set JAVA_HOME=C:\Program Files\OpenLogic\openlogic-openjdk-11.0.16+8-windows-x64

set PATH=%JAVA_HOME%\bin;%PATH%

set PROGRAM=FetchUpdate
set ACI_HOST=localhost
set ACI_PORT=7010
set IDENTIFIERS_XML_FILE=..\..\resources\identifiersXML.xml

set ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY=REPLACE_WITH_MY_LONG_KEY_STRING
rem set ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY=

java -jar target/%PROGRAM%-1.0-SNAPSHOT-jar-with-dependencies.jar %ACI_HOST% %ACI_PORT% %IDENTIFIERS_XML_FILE%