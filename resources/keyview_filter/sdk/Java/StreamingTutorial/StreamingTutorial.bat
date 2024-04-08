@echo off

REM Set the location of JAVA_HOME and KEYVIEW_BIN_FOLDER for your environment.
set JAVA_HOME=C:\Program Files\OpenLogic\openlogic-openjdk-11.0.16%+8-windows-x64
set KEYVIEW_BIN_FOLDER=C:\Opentext\KeyViewFilterSDK_24.2.0\WINDOWS_X86_64\bin

java -classpath %KEYVIEW_BIN_FOLDER%\..\..\javaapi\KeyView.jar;build\jar\StreamingTutorial.jar -Djava.library.path=%KEYVIEW_BIN_FOLDER% tutorial.StreamingTutorial %*
