set ACI_API_HOME=..\..\..\..\..\..\IDOLCSDK_24.4.0_WINDOWS_X86_64
set PATH=%ACI_API_HOME%;%PATH%

rem Replace the values for the following 3 parameters for your environment
set ACI_HOST=localhost
set ACI_PORT=7010
set IDENTIFIERS_XML_FILE=..\..\..\resources\identifiersXML.xml

set ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY=REPLACE_WITH_MY_LONG_KEY_STRING
rem set ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY=

fetch_update.exe %ACI_HOST% %ACI_PORT% "%IDENTIFIERS_XML_FILE%"
