@echo off

set VERSION=25.4.0
set PLATFORM=WINDOWS_X86_64

set XMLEXPORT_HOME=C:\OpenText\KeyviewExportSDK_%VERSION%_%PLATFORM%

set XMLEXPORT_INI_HOME=%XMLEXPORT_HOME%\xmlexport\programs\ini
set XMLEXPORT_INI_FILE=xml1file
rem set XMLEXPORT_INI_FILE=xml_index

set INPUT=%XMLEXPORT_HOME%\testdocs\Annual_Report.docx
rem set INPUT=%XMLEXPORT_HOME%\testdocs\Investment_Portfolio.xlsx
rem set INPUT=%XMLEXPORT_HOME%\testdocs\freezer2.ppt

set OUTPUT=%INPUT%.%XMLEXPORT_INI_FILE%.XML

echo Input file:  %INPUT%
echo Output file:  %OUTPUT%
echo Ini file: %XMLEXPORT_INI_HOME%\%XMLEXPORT_INI_FILE%.ini
echo.

set ORIG_DIR=%CD%
cd %XMLEXPORT_HOME%\%PLATFORM%\bin
xmlini %XMLEXPORT_INI_HOME%\%XMLEXPORT_INI_FILE%.ini %INPUT% %OUTPUT%
cd %ORIG_DIR%