set VERSION=25.4.0
set PLATFORM=WINDOWS_x86_64

rem set PYTHON_HOME=
rem set PATH=%PYTHON_HOME%
set PYTHON_EXE=python

set EDK_HOME=C:\OpenText\EductionSDK_%VERSION%_%PLATFORM%
set EDKLIBPATH=%EDK_HOME%\bin\edk.dll
set EDK_GRAMMARS_HOME=C:\OpenText\EductionGrammars_%VERSION%_COMMON

set LICENSEKEY=%EDK_HOME%\combined.dat

set GRAMMAR_FILE=%EDK_GRAMMARS_HOME%\pii\national_id.ecr

%PYTHON_EXE% -m edk.tool.list -l "%LICENSEKEY%" -g "%GRAMMAR_FILE%"
