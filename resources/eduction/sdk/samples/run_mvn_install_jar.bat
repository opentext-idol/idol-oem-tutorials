set VERSION=26.1.0
set PLATFORM=WINDOWS_X86_64

set EDK_HOME=C:\OpenText\EductionSDK_%VERSION%_%PLATFORM%

set MAVEN_HOME=C:\Program Files\Apache\maven\apache-maven-3.9.11
set JAVA_HOME=C:\Program Files\Microsoft\jdk-21.0.8.9-hotspot

set PATH=%MAVEN_HOME%\bin;%JAVA_HOME%\bin;%PATH%

mvn install:install-file -Dfile=%EDK_HOME%\bin\edk.jar -DgroupId=com.autonomy.eduction -DartifactId=edk -Dversion=%VERSION% -Dpackaging=jar -DgeneratePom=true