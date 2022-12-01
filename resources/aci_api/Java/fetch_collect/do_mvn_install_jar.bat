set ACI_API_HOME=..\..\..\..\..\..\IDOLJavaSDK_12.10.0
set MAVEN_HOME=C:\Program Files\Apache\maven\apache-maven-3.8.3

set PATH=%MAVEN_HOME%\bin;%PATH%

set VERSION=12.10.0

set

mvn install:install-file -Dfile=%ACI_API_HOME%\idol-aci-client-12.10.0-bin\aci-api-release-12.10.0.jar -DgroupId=com.autonomy.aci -DartifactId=aci -Dversion=%VERSION% -Dpackaging=jar -DgeneratePom=true