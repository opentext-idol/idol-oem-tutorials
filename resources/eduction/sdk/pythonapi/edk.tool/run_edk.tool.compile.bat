set VERSION=25.4.0
set PLATFORM=WINDOWS_x86_64

rem set PYTHON_HOME=
rem set PATH=%PYTHON_HOME%
set PYTHON_EXE=python

set EDK_HOME=C:\OpenText\EductionSDK_%VERSION%_%PLATFORM%
set EDKLIBPATH=%EDK_HOME%\bin\edk.dll

set LICENSEKEY=%EDK_HOME%\combined.dat

set INPUT=%EDK_HOME%\samples\compile\resources\test\source\test.xml
set OUTPUT=test.ecr
del %OUTPUT%

%PYTHON_EXE% -m edk.tool.compile -l "%LICENSEKEY%" -i "%INPUT%" -o "%OUTPUT%"
