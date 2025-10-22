set VERSION=25.4.0
set PLATFORM=WINDOWS_X86_64

set EDK_HOME=C:\OpenText\EductionSDK_%VERSION%_%PLATFORM%
set PYTHON_HOME=%USERPROFILE%\AppData\Local\Programs\Python\Python310

set PATH=%PYTHON_HOME%;%PYTHON_HOME%\scripts
set EDKLIBPATH=%EDK_HOME%\bin\edk.dll

set EDK_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH=%EDK_HOME%\licensekey.dat
set EDK_SAMPLE_PROGRAM_VERSIONKEY_FROM_FILEPATH=%EDK_HOME%\versionkey.dat

set CONFIG=test\config\basic.cfg
rem set CONFIG=test\config\entity_name.cfg
set INPUT=test\input\input.txt

set ORIG=%cd%

set OUTPUT=%ORIG%\redacted.EDK.TXT
del /s %OUTPUT%

cd ..\resources

python "%ORIG%\redaction.py" %CONFIG% "%INPUT%" "%OUTPUT%"

cd %ORIG%
