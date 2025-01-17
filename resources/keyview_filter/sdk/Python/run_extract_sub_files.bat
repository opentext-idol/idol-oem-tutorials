set VERSION=25.1.0
set PLATFORM=WINDOWS_X86_64

set KEYVIEW_FILTERSDK_HOME=C:\OpenText\KeyViewFilterSDK_%VERSION%_%PLATFORM%
set KEYVIEW_EXPORTSDK_HOME=C:\OpenText\KeyViewExportSDK_%VERSION%_%PLATFORM%
set IDOL_OEM_TUTORIALS_HOME=C:\OpenText\idol-oem-tutorials

set KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH=%KEYVIEW_FILTERSDK_HOME%\licensekey.dat

set INPUT_FILEPATH=%KEYVIEW_FILTERSDK_HOME%\javaapi\KeyView.jar
rem set INPUT_FILEPATH=%IDOL_OEM_TUTORIALS_HOME%\resources\keyview_filter\demo_EMBEDDED_DOCS+HIDDEN_TEXT.pptx
rem set INPUT_FILEPATH=%KEYVIEW_EXPORTSDK_HOME%\testdocs\Annual_Report.docx
rem set INPUT_FILEPATH=%KEYVIEW_EXPORTSDK_HOME%\testdocs\freezer2.ppt
rem set INPUT_FILEPATH=%KEYVIEW_EXPORTSDK_HOME%\testdocs\FreshDinner.doc
rem set INPUT_FILEPATH=%KEYVIEW_EXPORTSDK_HOME%\testdocs\frshfrozen.xls
rem set INPUT_FILEPATH=%KEYVIEW_EXPORTSDK_HOME%\testdocs\Investment_Portfolio.xlsx
rem set INPUT_FILEPATH=%KEYVIEW_EXPORTSDK_HOME%\testdocs\Report_Template.pdf
rem set INPUT_FILEPATH=%KEYVIEW_EXPORTSDK_HOME%\testdocs\Onboarding.msg
rem set INPUT_FILEPATH=%KEYVIEW_EXPORTSDK_HOME%\testdocs\SquaresTemplate.zip

set OUTPUT_ROOT_PATH=%IDOL_OEM_TUTORIALS_HOME%\_WORK\output
mkdir %OUTPUT_ROOT_PATH%

set LOG=extract_sub_files.LOG

set RECURSE=--recurse
rem set RECURSE=

python extract_sub_files.py "%KEYVIEW_FILTERSDK_HOME%\%PLATFORM%\bin" "%INPUT_FILEPATH%" "%OUTPUT_ROOT_PATH%" %RECURSE% > %LOG%
