set VERSION=25.1.0
set PLATFORM=WINDOWS_X86_64

set EDK_HOME=C:\OpenText\EductionSDK_%VERSION%_%PLATFORM%
set MAVEN_HOME=C:\Program Files\Apache\maven\apache-maven-3.8.3
set JAVA_HOME=C:\Program Files\OpenLogic\openlogic-openjdk-11.0.16+8-windows-x64

set PATH=%MAVEN_HOME%\bin;%JAVA_HOME%\bin;%PATH%

mvn install:install-file -Dfile=%EDK_HOME%\bin\edk.jar -DgroupId=com.autonomy.eduction -DartifactId=edk -Dversion=%VERSION% -Dpackaging=jar -DgeneratePom=true