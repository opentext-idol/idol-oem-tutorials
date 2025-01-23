# Eduction SDK Java API

The Eduction SDK is designed to be embedded into other services. To facilitate embedding, the Eduction SDK has APIs for C, Java and .NET.  In addition, the Eduction SDK runs natively on the following platforms: Windows (x86_64, x86_32 and ARM_64), Linux (x86_64 and ARM_64) and MacOS (x86_64 and Apple M*).

In this lesson, you will:

- use the Eduction SDK Java API to perform extraction using a configuration file
- use the Eduction SDK Java API to compile a grammar XML into an ECR

The [Eduction User and Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/EductionSDK_25.1_Documentation/Guides/html/Content/EductionSDK/APIReference/Java_APIConcepts.htm) has sections on this topic which will be referenced in this lesson.

> NOTE: This lesson only covers the Eduction SDK APIs and does not cover Eduction Server. See [here](./README.md#use-eduction-server) for a lesson on Eduction Server.

> NOTE: This guide assumes you have already completed the introductory Eduction [tutorial](../eduction/introduction.md#introduction-to-eduction).

---

- [Setup](#setup)
  - [License and Version key dat files](#license-and-version-key-dat-files)
  - [Resources](#resources)
  - [Environment and Compilers](#environment-and-compilers)
- [API Documentation](#api-documentation)
- [Example programs](#example-programs)
  - [`eduction_from_config`](#eduction_from_config)
    - [Sample `eduction_from_config` code](#sample-eduction_from_config-code)
    - [Build `eduction_from_config`](#build-eduction_from_config)
    - [Run `eduction_from_config`](#run-eduction_from_config)
  - [`compile`](#compile)
    - [Sample `compile` code](#sample-compile-code)
    - [Build `compile`](#build-compile)
    - [Run `compile`](#run-compile)
  - [`redaction`](#redaction)
    - [Build `redaction`](#build-redaction)
    - [Run `redaction`](#run-redaction)
- [Conclusion](#conclusion)
- [See also](#see-also)
  
---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

Refer to `README.md` in the `C:\OpenText\EductionSDK_25.1.0_WINDOWS_X86_64\samples` folder for API language and platform specific requirements and instructions to build the sample programs.

> NOTE: This lesson assumes you have already completed the [Eduction SDK introduction](../eduction/introduction.md#introduction-to-eduction) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic Eduction concepts.

### License and Version key dat files

Deploy the `licensekey.dat` and `versionkey.dat` files to the EductionSDK home directory (*e.g.* `C:\OpenText\EductionSDK_25.1.0_WINDOWS_X86_64`).

### Resources

You must download the following resources before you continue:

- source code and build tools
  - [eduction_from_config/java](../../resources/eduction/sdk/samples/eduction_from_config/java/)
  - [eduction_from_config/resources](../../resources/eduction/sdk/samples/eduction_from_config/resources/)
  - [compile/java](../../resources/eduction/sdk/samples/compile/java)
  - [redaction/java](../../resources/eduction/sdk/samples/redaction/java)
  - [run_mvn_install_jar.bat](../../resources/eduction/sdk/samples)

> NOTE: Deploy these resources to the `%EDK_HOME%\samples` folder, adding to and/or replacing what is provided with EductionSDK.

### Environment and Compilers

- Refer to the `System Requirements` section of the [Getting Started Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/IDOLServer_25.1_Documentation/Guides/html/gettingstarted/Content/Install_Run_IDOL/Install/System_Requirements.htm) for general software dependencies.
- Refer to [Eduction User & Programming Guide - Deploy Eduction SDK - Java API Component](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/EductionSDK_25.1_Documentation/Guides/html/Content/EductionSDK/DeployEductionSDK/Java_API.htm) for API and platform specific software dependencies.
- The `README.md` in `C:\OpenText\EductionSDK_25.1.0_WINDOWS_X86_64\samples` notes more API language and platform specific requirements (*e.g.* compiler information, build tools) and build tips.

> NOTE: For the Java code, the `pom.xml` may need to be modified as the following:
>
> ```diff
> ...
> <dependencies>
>    ...
>    <dependency>
>      <groupId>com.autonomy.eduction</groupId>
>      <artifactId>edk</artifactId>
> -    <version>12.11.0</version>
> +    <version>25.1.0</version>
>    </dependency>
> </dependencies> 
> ```

Apache Maven and a Java JDK (*e.g.* OpenJDK) are used to build and run the sample programs.  The `edk.jar` for version 25.1 must deployed to your local Maven cache.  A Windows batch file `run_mvn_install_jar.bat` and Bourne shell script `run_mvn_install_jar` are provided in the `C:\OpenText\idol-oem-tutorials\resources\eduction\sdk\samples`.

> NOTE: Before proceeding make sure the `EDK_HOME`, `MAVEN_HOME` and `JAVA_HOME` are correct for your environment.

```sh
> cd C:\OpenText\EductionSDK_25.1.0_WINDOWS_x86_64\samples
> run_mvn_install_jar.bat
C:\OpenText\EductionSDK_25.1.0_WINDOWS_x86_6\samples>mvn install:install-file -Dfile=C:\OpenText\EductionSDK_25.1.0_WINDOWS_x86_6\bin\edk.jar -DgroupId=com.autonomy.eduction -DartifactId=edk -Dversion=25.1.0 -Dpackaging=jar -DgeneratePom=true
[INFO] Scanning for projects...
[INFO]
[INFO] ------------------< org.apache.maven:standalone-pom >-------------------
[INFO] Building Maven Stub Project (No POM) 1
[INFO] --------------------------------[ pom ]---------------------------------
[INFO]
[INFO] --- maven-install-plugin:2.4:install-file (default-cli) @ standalone-pom ---
[INFO] Installing C:\OpenText\EductionSDK_25.1.0_WINDOWS_x86_6\bin\edk.jar to C:%HOMEPATH%\.m2\repository\com\autonomy\eduction\edk\25.1.0\edk-25.1.0.jar
[INFO] Installing C:%HOMEPATH%\AppData\Local\Temp\mvninstall6990321632397672369.pom to C:%HOMEPATH%\.m2\repository\com\autonomy\eduction\edk\25.1.0\edk-25.1.0.pom
[INFO] ------------------------------------------------------------------------
[INFO] BUILD SUCCESS
[INFO] ------------------------------------------------------------------------
[INFO] Total time:  0.589 s
[INFO] Finished at: 2024-02-26T13:51:05-07:00
[INFO] ------------------------------------------------------------------------
```

## API Documentation

API specific documentation is located in sub-folders of `C:\OpenText\EductionSDK_25.1.0_WINDOWS_X86_64\` as noted below:

- Java - `java_api\help\index.html`

## Example programs

Example programs (with resources) ship with the `EductionSDK_<VERSION>_<PLATFORM>.zip` and `EductionGrammars_<VERSION>_COMMON.zip`.  The sample programs cover topics:

- performing different types of extraction / redaction.
- compiling an XML grammar into an ECR file

### `eduction_from_config`

The `eduction_from_config` sample program accepts a configuration file as you've been using in the other Eduction lessons, an UTF-8 text file, a path to the output JSON file and some optional arguments to override the configuration.

#### Sample `eduction_from_config` code

The Java sample `eduction_from_config` application code lives in: `C:\OpenText\EductionSDK_25.1.0_WINDOWS_X86_64\samples\eduction_from_config\java`.

#### Build `eduction_from_config`

Go ahead and build `eduction_from_config`.  A Windows batch file `run_mvn_test.bat` is provided.

> NOTE: Before proceeding make sure the `EDK_HOME`, `MAVEN_HOME` and `JAVA_HOME` are correct for your environment.

```sh
> cd C:\OpenText\EductionSDK_25.1.0_WINDOWS_x86_64\samples\eduction_from_config\java
> run_mvn_test.bat 
```

Check the `mvn_test.log` for any errors and `BUILD SUCCESS`.

#### Run `eduction_from_config`

Go ahead and run `eduction_from_config`.  A Windows batch file `run_test.bat` is provided.

> NOTE: Before proceeding make sure the `EDK_HOME`, `MAVEN_HOME` and `JAVA_HOME` are correct for your environment.

> NOTE: `eduction_from_config` expects the `idol-oem-tutorials\resources\eduction\sdk\samples\eduction_from_config\resources\test\config\test_session.cfg` to be deployed.

```sh
> cd C:\OpenText\EductionSDK_25.1.0_WINDOWS_x86_64\samples\eduction_from_config\java
> run_test.bat
Feb 26, 2025.1:04:52 PM com.autonomy.eduction.samples.FromConfig$Args <init>
INFO: Parameters valid.
Successfully configured 1 post-processing tasks.
Feb 26, 2025.1:04:52 PM com.autonomy.eduction.samples.FromConfig extract
INFO: Input data file opened.
Feb 26, 2025.1:04:52 PM com.autonomy.eduction.samples.FromConfig extract
INFO: Printing results to output.json...
Feb 26, 2025.1:04:52 PM com.autonomy.eduction.samples.FromConfig getJsonLines
INFO: Got 2 matches
```

Review `educed.EDK.JSON` to see the match information. The program should run and produce an output file containing two matches, as follows:

```json
{
  "matches": [
    {
      "matched_text": "foo bar",
      "entity_name": "test/two_words",
      "offset": 12,
      "offset_length": 12,
      "matched_text_length": 7,
      "matched_text_size": 7,
      "normalized_text": "foo bar",
      "normalized_text_length": 7,
      "normalized_text_size": 7,
      "score": 1.00,
      "components": [
        {
          "name": "FIRST",
          "normalized_text": "foo",
          "normalized_text_length": 3,
          "normalized_text_size": 3,
          "normalized_text_offset": 0,
          "normalized_text_offset_length": 0
        },
        {
          "name": "SECOND",
          "normalized_text": "bar",
          "normalized_text_length": 3,
          "normalized_text_size": 3,
          "normalized_text_offset": 4,
          "normalized_text_offset_length": 4
        }
      ]
    },
    {
      "matched_text": "baz bah",
      "entity_name": "test/two_words",
      "offset": 20,
      "offset_length": 20,
      "matched_text_length": 7,
      "matched_text_size": 7,
      "normalized_text": "baz bah",
      "normalized_text_length": 7,
      "normalized_text_size": 7,
      "score": 1.00,
      "components": [
        {
          "name": "FIRST",
          "normalized_text": "baz",
          "normalized_text_length": 3,
          "normalized_text_size": 3,
          "normalized_text_offset": 0,
          "normalized_text_offset_length": 0
        },
        {
          "name": "SECOND",
          "normalized_text": "bah",
          "normalized_text_length": 3,
          "normalized_text_size": 3,
          "normalized_text_offset": 4,
          "normalized_text_offset_length": 4
        }
      ]
    }
  ]
}
```

For extra credit, try `eduction_from_config` on other Eduction configurations, insuring that configuration file paths are correct.

Review the `eduction_from_config` Java source code to gain more insights into how to incorporate the Eduction SDK Java API into your application.

### `compile`

In some use cases for Eduction, custom grammars either for net-new entities and/or extending the entities in the licensed grammar packs.

> NOTE: While the Eduction SDK engine does support XML based resource files, pre-compiling them into ECRs is recommended.

#### Sample `compile` code

The C sample `compile` application code lives in: `C:\OpenText\EductionSDK_25.1.0_WINDOWS_X86_64\samples\compile\java`.

#### Build `compile`

Go ahead and build `compile`.  A Windows batch file `run_mvn_test.bat` is provided.

> NOTE: Before proceeding make sure the `EDK_HOME`, `MAVEN_HOME` and `JAVA_HOME` are correct for your environment.

```sh
> cd C:\OpenText\EductionSDK_25.1.0_WINDOWS_x86_64\samples\compile\java
> run_mvn_test.bat 
```

Check the `mvn_test.log` for any errors and `BUILD SUCCESS`.

#### Run `compile`

Go ahead and run `compile`.  A Windows batch file `run_test.bat` is provided.

> NOTE: Before proceeding make sure the `EDK_HOME`, `MAVEN_HOME` and `JAVA_HOME` are correct for your environment.

```sh
> cd C:\OpenText\EductionSDK_25.1.0_WINDOWS_x86_64\samples\compile\java
> run_test.bat
Feb 26, 2025.1:09:53 PM com.autonomy.eduction.samples.Compile save
INFO: Parameters valid.
Feb 26, 2025.1:09:53 PM com.autonomy.eduction.samples.Compile save
INFO: License read.
Feb 26, 2025.1:09:53 PM com.autonomy.eduction.samples.Compile save
INFO: Version key read.
Feb 26, 2025.1:09:53 PM com.autonomy.eduction.samples.Compile save
INFO: Engine created.
Feb 26, 2025.1:09:53 PM com.autonomy.eduction.samples.Compile save
INFO: Grammar source file loaded and compiled
Feb 26, 2025.1:09:53 PM com.autonomy.eduction.samples.Compile save
INFO: Compiled grammar file saved
```

A `test.ecr` from the `src/test.xml` source should be generated. To verify the compilation and check which entities are declared as public, let's list the ECRs contents.

```sh
> edktool.exe list -a test.ecr

Eduction EDKTool Utility v25.1.0
Loading resource file:
test.ecr


Grammar version:        4.0

Compiled using Edktool: 25.1.0

Listing entities:
test/two_words
    components: "FIRST" "SECOND"

Listing all necessary requirements for license:
    (none)

0.018 seconds elapsed
```

For extra credit, try `compile` on other Eduction grammar XML.

Review the `compile` Java source code to gain more insights into how to incorporate the Eduction SDK Java API into your application.

### `redaction`

In some use cases for Eduction, custom grammars either for net-new entities and/or extending the entities in the licensed grammar packs.

> NOTE: While the Eduction SDK engine does support XML based resource files, pre-compiling them into ECRs is recommended.

The `redaction` sample program accepts a configuration file as you've been using in the other Eduction lessons, an UTF-8 text file and a path to the redacted TXT file.

#### Build `redaction`

Go ahead and build `redaction`.  A Windows batch file `run_mvn_test.bat` is provided.

> NOTE: Before proceeding make sure the `EDK_HOME`, `MAVEN_HOME` and `JAVA_HOME` are correct for your environment.

```sh
> cd C:\OpenText\EductionSDK_25.1.0_WINDOWS_x86_64\samples\redaction\java
> run_mvn_test.bat 
```

Check the `mvn_test.log` for any errors and `BUILD SUCCESS`.

#### Run `redaction`

Go ahead and run `redaction`.  A Windows batch file `run_test.bat` is provided.

> NOTE: Before proceeding make sure the `EDK_HOME`, `MAVEN_HOME` and `JAVA_HOME` are correct for your environment.

```sh
> cd C:\OpenText\EductionSDK_25.1.0_WINDOWS_x86_64\samples\redaction\java
> run_test.bat
Apr 08, 2024 4:06:48 PM com.autonomy.eduction.samples.Redact redact
INFO: Parameters valid.
Apr 08, 2024 4:06:48 PM com.autonomy.eduction.samples.Redact redact
INFO: Read license.
Apr 08, 2024 4:06:48 PM com.autonomy.eduction.samples.Redact redact
INFO: Engine created.
Apr 08, 2024 4:06:48 PM com.autonomy.eduction.samples.Redact redact
INFO: Printing result to test_redact_java.txt ...
Apr 08, 2024 4:06:48 PM com.autonomy.eduction.samples.Redact redact
INFO: Program completed without error
```

A `redacted.EDK.TXT` should be generated and have the same output as in the `..\resources\test\expectations\redaction.txt`.

For extra credit, try `redaction` with the other Eduction configuration file `entity_name.cfg`.

Review the `redaction` Java source code to gain more insights into how to incorporate the Eduction SDK Java API into your application.

## Conclusion

You now understand the basics of the Eduction SDK Java API.

As extra credit, build and run the other sample programs in `EductionSDK_<VERSION>_<PLATFORM>\samples` and `EductionGrammars_<VERSION>_COMMON\pii\edk_samples`.  Refer to the changes in these resources and leverage the build tools & tips.

Next, why not try more tutorials to explore some of the other features available in Eduction, linked from [here](../eduction/README.md#capability-showcase).

## See also

- [Eduction SDK User and Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/EductionSDK_25.1_Documentation/Guides/html/)
- [Eduction Server User and Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/EductionServer_25.1_Documentation/Help/Content/_ACI_Welcome.htm)
- [Eduction Grammars User Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/EductionGrammars_25.1_Documentation/Help/)
- [Knowledge Discovery Release Notes - Eduction](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/IDOLReleaseNotes_25.1_Documentation/idol/Content/SDKs/Eduction.htm)
