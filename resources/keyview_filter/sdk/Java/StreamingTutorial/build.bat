@echo off

set JAVA_HOME=C:\Program Files\Microsoft\jdk-21.0.8.9-hotspot
set ANT_HOME=C:\Program Files\Apache\Ant\apache-ant-1.10.15

set PATH=%JAVA_HOME%\bin;%ANT_HOME%\bin

echo "Did you update Config.java per the lesson?"
set /p NO_WHERE="Hit enter to continue"

ant jar