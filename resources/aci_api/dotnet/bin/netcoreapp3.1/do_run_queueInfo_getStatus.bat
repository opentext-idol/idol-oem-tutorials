set ACI_API_HOME=..\..\..\..\..\..\IDOLDOTNETSDK_24.3.0_WINDOWS_X86_64
set PATH=%ACI_API_HOME%;%PATH%

rem Replace the values for the following parameters for your environment
# The TOKEN value will be returned from a=fetch or similar
set ACI_HOST=localhost
set ACI_PORT=7010
set QUEUE_NAME=fetch
rem set TOKEN=MTkyLjE2OC4xODIuMTo3MDAwOklOR0VTVDoxNjU2NjE5ODYxMDY3MjAxMzY3MDM0Mzgw
set TOKEN=

set ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY=REPLACE_WITH_MY_LONG_KEY_STRING
rem set ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY=

queueInfo_getStatus.exe %ACI_HOST% %ACI_PORT% %QUEUE_NAME% %TOKEN%
