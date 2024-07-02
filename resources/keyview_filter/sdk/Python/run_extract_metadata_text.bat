set VERSION=24.3.0
set PLATFORM=WINDOWS_X86_64

set KEYVIEW_FILTERSDK_HOME=C:\OpenText\KeyViewFilterSDK_%VERSION%_%PLATFORM%
set KEYVIEW_EXPORTSDK_HOME=C:\OpenText\KeyViewExportSDK_%VERSION%_%PLATFORM%
set IDOL_OEM_TUTORIALS_HOME=C:\OpenText\idol-oem-tutorials\

set KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH=%KEYVIEW_FILTERSDK_HOME%\licensekey.dat

set INPUT_FILEPATH=%IDOL_OEM_TUTORIALS_HOME%\resources\keyview_filter\2022_calendar_HIDDEN_TEXT.docx
rem set INPUT_FILEPATH=%KEYVIEW_EXPORTSDK_HOME%\testdocs\Annual_Report.docx
rem set INPUT_FILEPATH=%KEYVIEW_EXPORTSDK_HOME%\testdocs\freezer2.ppt
rem set INPUT_FILEPATH=%KEYVIEW_EXPORTSDK_HOME%\testdocs\FreshDinner.doc
rem set INPUT_FILEPATH=%KEYVIEW_EXPORTSDK_HOME%\testdocs\frshfrozen.xls
rem set INPUT_FILEPATH=%KEYVIEW_EXPORTSDK_HOME%\testdocs\Investment_Portfolio.xlsx
rem set INPUT_FILEPATH=%KEYVIEW_EXPORTSDK_HOME%\testdocs\Report_Template.pdf
rem set INPUT_FILEPATH=%KEYVIEW_EXPORTSDK_HOME%\testdocs\SquaresLetterHead.tiff

set METADATA_OUTPUT_FILEPATH=%INPUT_FILEPATH%.KV_%VERSION%_METADATA.TXT
set TEXT_OUTPUT_FILEPATH=%INPUT_FILEPATH%.KV_%VERSION%_TEXT.TXT

python3 extract_metadata_text.py "%KEYVIEW_FILTERSDK_HOME%\%PLATFORM%\bin" "%INPUT_FILEPATH%" "%METADATA_OUTPUT_FILEPATH%" "%TEXT_OUTPUT_FILEPATH%"