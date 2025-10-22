set VERSION=25.4.0
set PLATFORM=WINDOWS_X86_64

set EDK_HOME=C:\OpenText\EductionSDK_%VERSION%_%PLATFORM%

set EDKLIBPATH=%EDK_HOME%\bin\edk.dll

set PIP_EXE=pip3

cd %EDK_HOME%
%PIP_EXE% install bin\edk-%VERSION%-py3-none-any.whl