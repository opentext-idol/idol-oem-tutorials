set VERSION=24.4.0
set PLATFORM=WINDOWS_x86_64

set EDK_HOME=C:\OpenText\EductionSDK_%VERSION%_%PLATFORM%
set PYTHON_HOME=%USERPROFILE%\AppData\Local\Programs\Python\Python310

set PATH=%PYTHON_HOME%
set EDKLIBPATH=%EDK_HOME%\bin\edk.dll

set LICENSEKEY=%EDK_HOME%\combined.dat

set CONFIG=test\config\test.cfg
set INPUT=test\input\input.txt

set ORIG=%cd%

set OUTPUT=%ORIG%\educed.EDK.JSON
del %OUTPUT%

cd %EDK_HOME%\samples\eduction_from_config\resources

python -m edk.tool.extract -l "%LICENSEKEY%" -i "%INPUT%" -c "%CONFIG%" > "%OUTPUT%"

cd %ORIG%
