set ACI_API_HOME=..\..\..\..\..\..\IDOLDOTNETSDK_24.2.0_WINDOWS_X86_64
set PATH=%ACI_API_HOME%;%PATH%

rem Replace the values for the following parameters for your environment
set ACI_HOST=localhost
set ACI_PORT=7010
set TASK_NAME=MyTask

set ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY=REPLACE_WITH_MY_LONG_KEY_STRING
rem set ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY=

fetchSynchronize.exe %ACI_HOST% %ACI_PORT% %TASK_NAME%
