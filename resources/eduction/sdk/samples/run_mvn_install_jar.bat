set EDK_HOME=C:\Opentext\EductionSDK_24.2.0_WINDOWS_X86_64
set MAVEN_HOME=C:\Program Files\Apache\maven\apache-maven-3.8.3
set JAVA_HOME=C:\Program Files\Java\jdk1.8.0_321

set PATH=%MAVEN_HOME%\bin;%JAVA_HOME%\bin;%PATH%

set VERSION=24.2.0

rem set

mvn install:install-file -Dfile=%EDK_HOME%\bin\edk.jar -DgroupId=com.autonomy.eduction -DartifactId=edk -Dversion=%VERSION% -Dpackaging=jar -DgeneratePom=true