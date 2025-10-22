set VERSION=25.4.0
set PLATFORM=WINDOWS_x86_64

rem set PYTHON_HOME=
rem set PATH=%PYTHON_HOME%
set PYTHON_EXE=python

set EDK_HOME=C:\OpenText\EductionSDK_%VERSION%_%PLATFORM%
set EDKLIBPATH=%EDK_HOME%\bin\edk.dll

set LICENSEKEY=%EDK_HOME%\combined.dat

set CONFIG=test\config\test.cfg
set INPUT=test\input\input.txt

set ORIG=%cd%

set OUTPUT=%ORIG%\educed.EDK.JSON
del %OUTPUT%

cd %EDK_HOME%\samples\eduction_from_config\resources

%PYTHON_EXE% -m edk.tool.extract -l "%LICENSEKEY%" -i "%INPUT%" -c "%CONFIG%" > "%OUTPUT%"

cd %ORIG%
