set VERSION=24.4.0
set PLATFORM=WINDOWS_x86_64

set EDK_HOME=C:\OpenText\EductionSDK_%VERSION%_%PLATFORM%
set PYTHON_HOME=%USERPROFILE%\AppData\Local\Programs\Python\Python310

set PATH=%PYTHON_HOME%
set EDKLIBPATH=%EDK_HOME%\bin\edk.dll

set LICENSEKEY=%EDK_HOME%\licensekey.dat

python -m edk.tool.licenseinfo -l "%LICENSEKEY%"
