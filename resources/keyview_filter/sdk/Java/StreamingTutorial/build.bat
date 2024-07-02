@echo off

set JAVA_HOME=C:\Program Files\OpenLogic\openlogic-openjdk-11.0.16%+8-windows-x64
set ANT_HOME=C:\Program Files\Apache\Ant\apache-ant-1.9.16

set PATH=%JAVA_HOME%\bin;%ANT_HOME%\bin

echo "Did you update Config.java per the lesson?"
set /p NO_WHERE="Hit enter to continue"

ant jar