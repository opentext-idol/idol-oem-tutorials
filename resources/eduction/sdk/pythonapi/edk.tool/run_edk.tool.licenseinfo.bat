set VERSION=25.4.0
set PLATFORM=WINDOWS_x86_64

rem set PYTHON_HOME=
rem set PATH=%PYTHON_HOME%
set PYTHON_EXE=python

set EDK_HOME=C:\OpenText\EductionSDK_%VERSION%_%PLATFORM%
set EDKLIBPATH=%EDK_HOME%\bin\edk.dll

set LICENSEKEY=%EDK_HOME%\licensekey.dat

%PYTHON_EXE% -m edk.tool.licenseinfo -l "%LICENSEKEY%"
