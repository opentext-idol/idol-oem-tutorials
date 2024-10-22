set VERSION=24.4.0
set PLATFORM=WINDOWS_x86_64

set EDK_HOME=C:\OpenText\EductionSDK_%VERSION%_%PLATFORM%
set EDK_GRAMMARS_HOME=%EDK_HOME%\..\EductionGrammars_%VERSION%_COMMON

set PYTHON_HOME=%USERPROFILE%\AppData\Local\Programs\Python\Python310

set PATH=%PYTHON_HOME%
set EDKLIBPATH=%EDK_HOME%\bin\edk.dll

set LICENSEKEY=%EDK_HOME%\combined.dat
set GRAMMAR_FILE=%EDK_GRAMMARS_HOME%\pii\national_id.ecr

python -m edk.tool.list -l "%LICENSEKEY%" -g "%GRAMMAR_FILE%"
