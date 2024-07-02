set VERSION=24.3.0
set PLATFORM=WINDOWS_X86_64

set KEYVIEW_FILTERSDK_HOME=C:\OpenText\KeyViewFilterSDK_%VERSION%_%PLATFORM%
set KEYVIEW_EXPORTSDK_HOME=C:\OpenText\KeyViewExportSDK_%VERSION%_%PLATFORM%
set IDOL_OEM_TUTORIALS_HOME=C:\OpenText\idol-oem-tutorials\

set EDK_HOME=C:\Opentext\EductionSDK_%VERSION%_%PLATFORM%
set PYTHON_HOME=%USERPROFILE%\AppData\Local\Programs\Python\Python310

set PATH=%PYTHON_HOME%;%PYTHON_HOME%\scripts
set EDKLIBPATH=%EDK_HOME%\bin\edk.dll

set KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH=%KEYVIEW_FILTERSDK_HOME%\licensekey.dat

set EDK_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH=%EDK_HOME%\licensekey.dat
set EDK_SAMPLE_PROGRAM_VERSIONKEY_FROM_FILEPATH=%EDK_HOME%\versionkey.dat

set CONFIG=test\config\test.cfg
set INPUT_FILEPATH=test\input\input.pdf
rem set INPUT_FILEPATH=%IDOL_OEM_TUTORIALS_HOME%\resources\keyview_filter\2022_calendar_HIDDEN_TEXT.docx
rem set INPUT_FILEPATH=%KEYVIEW_EXPORTSDK_HOME%\testdocs\Annual_Report.docx
rem set INPUT_FILEPATH=%KEYVIEW_EXPORTSDK_HOME%\testdocs\freezer2.ppt
rem set INPUT_FILEPATH=%KEYVIEW_EXPORTSDK_HOME%\testdocs\FreshDinner.doc
rem set INPUT_FILEPATH=%KEYVIEW_EXPORTSDK_HOME%\testdocs\frshfrozen.xls
rem set INPUT_FILEPATH=%KEYVIEW_EXPORTSDK_HOME%\testdocs\Investment_Portfolio.xlsx
rem set INPUT_FILEPATH=%KEYVIEW_EXPORTSDK_HOME%\testdocs\Report_Template.pdf
rem set INPUT_FILEPATH=%KEYVIEW_EXPORTSDK_HOME%\testdocs\SquaresLetterHead.tiff

set ORIG=%cd%

set OUTPUT=%ORIG%\educed.EDK.JSON
del /s %OUTPUT%

cd ..\resources

python %ORIG%\kvfilter_eduction_stream.py "%KEYVIEW_FILTERSDK_HOME%\%PLATFORM%\bin" "%CONFIG%" "%INPUT_FILEPATH%" "%OUTPUT%"

cd %ORIG%
