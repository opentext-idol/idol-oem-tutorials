@echo off

set VERSION=26.1.0
set PLATFORM=WINDOWS_X86_64

set KEYVIEW_BIN_FOLDER=C:\Opentext\KeyviewFilterSDK_%VERSION%_%PLATFORM%\%PLATFORM%\bin
set IDOL_OEM_TUTORIALS_HOME=C:\OpenText\idol-oem-tutorials

set JAVA_HOME=C:\Program Files\Microsoft\jdk-21.0.8.9-hotspot

set INPUT_FILEPATH=%IDOL_OEM_TUTORIALS_HOME%\resources\keyview_filter\KeyViewFilterSDK_12.12.0_ReleaseNotes_en.rar
set TEXT_OUTPUT_FILEPATH=%INPUT_FILEPATH%.KV_%VERSION%_TEXT.TXT

java -classpath %KEYVIEW_BIN_FOLDER%\..\..\javaapi\KeyView.jar;build\jar\StreamingTutorial.jar -Djava.library.path=%KEYVIEW_BIN_FOLDER% tutorial.StreamingTutorial %INPUT_FILEPATH% %TEXT_OUTPUT_FILEPATH%
