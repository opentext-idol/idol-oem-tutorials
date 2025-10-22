set VERSION=25.4.0

set ACI_API_HOME=..\..\..\..\IDOLJavaSDK_%VERSION%
set MAVEN_HOME=C:\Program Files\Apache\maven\apache-maven-3.8.3
set JAVA_HOME=C:\Program Files\OpenLogic\openlogic-openjdk-17.0.10+7-windows-x64

set PATH=%MAVEN_HOME%\bin;%JAVA_HOME%\bin;%PATH%


set

mvn install:install-file -Dfile=%ACI_API_HOME%\aci-api-release-%VERSION%.jar -DgroupId=com.autonomy.aci -DartifactId=aci-api-release -Dversion=%VERSION% -Dpackaging=jar -DgeneratePom=true