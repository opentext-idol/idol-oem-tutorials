set VERSION=25.4.0
set PLATFORM=WINDOWS_x86_64

rem set PYTHON_HOME=
rem set PATH=%PYTHON_HOME%
set PYTHON_EXE=python

set EDK_HOME=C:\OpenText\EductionSDK_%VERSION%_%PLATFORM%
set EDKLIBPATH=%EDK_HOME%\bin\edk.dll

set LICENSEKEY=%EDK_HOME%\combined.dat

set CONFIG=test\config\basic.cfg
rem set CONFIG=test\config\entity_name.cfg
set INPUT=test\input\input.txt

set ORIG=%cd%

set OUTPUT=%ORIG%\redacted.EDK.TXT
del %OUTPUT%

cd %EDK_HOME%\samples\redaction\resources

%PYTHON_EXE% -m edk.tool.redact -l "%LICENSEKEY%" -i "%INPUT%" -c "%CONFIG%" > "%OUTPUT%"

cd %ORIG%
