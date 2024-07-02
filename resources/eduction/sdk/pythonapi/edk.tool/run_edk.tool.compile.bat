set VERSION=24.3.0
set PLATFORM=WINDOWS_x86_64

set EDK_HOME=C:\Opentext\EductionSDK_%VERSION%_%PLATFORM%
set PYTHON_HOME=%USERPROFILE%\AppData\Local\Programs\Python\Python310

set PATH=%PYTHON_HOME%
set EDKLIBPATH=%EDK_HOME%\bin\edk.dll

set LICENSEKEY=%EDK_HOME%\combined.dat

set INPUT=%EDK_HOME%\samples\compile\resources\test\source\test.xml

set OUTPUT=test.ecr
del %OUTPUT%

python -m edk.tool.compile -l "%LICENSEKEY%" -i "%INPUT%" -o "%OUTPUT%"
