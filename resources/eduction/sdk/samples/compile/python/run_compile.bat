set VERSION=25.1.0
set PLATFORM=WINDOWS_X86_64

set EDK_HOME=C:\OpenText\EductionSDK_%VERSION%_%PLATFORM%
set PYTHON_HOME=%USERPROFILE%\AppData\Local\Programs\Python\Python310

set PATH=%EDK_HOME%\bin;%PYTHON_HOME%;%PYTHON_HOME%\scripts
set EDKLIBPATH=%EDK_HOME%\bin\edk.dll

set EDK_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH=%EDK_HOME%\licensekey.dat
set EDK_SAMPLE_PROGRAM_VERSIONKEY_FROM_FILEPATH=%EDK_HOME%\versionkey.dat

set INPUT=test\source\test.xml

set ORIG=%cd%

set OUTPUT=%ORIG%\test.ecr
del %OUTPUT%

cd ..\resources

python "%ORIG%\compile.py" "%INPUT%" "%OUTPUT%"

cd %ORIG%
