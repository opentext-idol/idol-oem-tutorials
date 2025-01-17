# Eduction SDK Python API

The Eduction SDK is designed to be embedded into other services.

To facilitate embedding, the Eduction SDK has APIs for C, Java, Python and .NET.  In addition, the Eduction SDK runs natively on the following platforms: Windows (x86_64, x86_32 and ARM_64), Linux (x86_64 and ARM_64), MacOS (x86_64 and Apple M*).

In this lesson, you will:

- use the Eduction SDK Python API to perform extraction using a configuration file
- use the Eduction SDK Python API to compile a grammar XML into an ECR

The [Eduction User and Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/EductionSDK_25.1_Documentation/Guides/html/Content/EductionSDK/APIReference/Python_APIConcepts.htm) has sections on this topic which will be referenced in this lesson.

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
    - [Run `eduction_from_config`](#run-eduction_from_config)
  - [`compile`](#compile)
    - [Run `compile`](#run-compile)
  - [`redaction`](#redaction)
    - [Run `redaction`](#run-redaction)
- [Conclusion](#conclusion)
- [See also](#see-also)
  
---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

Refer to `README.md` in the `C:\OpenText\EductionSDK_25.1.0_WINDOWS_X86_64\samples` folder for API language and platform specific requirements and instructions to build the sample programs.

> NOTE: This lesson assumes you have already completed the [Eduction SDK introduction](../eduction/introduction.md#introduction-to-eduction) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic Eduction concepts.

### License and Version key dat files

Deploy the `licensekey.dat` and `versionkey.dat` files to the EductionSDK home directory (e.g. `C:\OpenText\EductionSDK_25.1.0_WINDOWS_X86_64`).

> NOTE: An improved method to incorporate `versionkey.dat` is implemented as part of the provided resources, where you must ignore the release notes recommendation to pre-concatenate the `licensekey.dat` and `versionkey.dat`, delimited by a `;`.

### Resources

You must download the following resources before you continue:

- source code and build tools
  - [eduction_from_config/python](../../resources/eduction/sdk/samples/eduction_from_config/python/)
  - [compile/python](../../resources/eduction/sdk/samples/compile/python)
  - [redaction/python](../../resources/eduction/sdk/samples/redaction/python)

> NOTE: Deploy these resources to the `%EDK_HOME%\samples` folder, adding to and/or replacing what is provided with EductionSDK.

### Environment and Compilers

- Refer to the `System Requirements` section of the [Getting Started Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/IDOLServer_25.1_Documentation/Guides/html/gettingstarted/Content/Install_Run_IDOL/Install/System_Requirements.htm) for general software dependencies.
- Refer to [Eduction User & Programming Guide - Deploy Eduction SDK - Java API Component](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/EductionSDK_25.1_Documentation/Guides/html/Content/EductionSDK/DeployEductionSDK/Java_API.htm) for API and platform specific software dependencies.
- The `README.md` in `C:\OpenText\EductionSDK_25.1.0_WINDOWS_X86_64\samples` notes more API language and platform specific requirements (*e.g.* compiler information, build tools) and build tips.

A Python interpreter (including pip) are used to install the `edk-version-py3-none-any.whl` and run the sample programs.  The `edk-version-py3-none-any.whl` for version 25.1 must deployed to your Python environment.  Refer to [Eduction User & Programming Guide - API Reference - Python API Concepts](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/EductionSDK_25.1_Documentation/Guides/html/Content/EductionSDK/APIReference/Python_APIConcepts.htm#Installation) for tips on installing `edk-version-py3-none-any.whl`.

## API Documentation

API specific documentation is located in sub-folders of `C:\OpenText\EductionSDK_25.1.0_WINDOWS_X86_64\` as noted below:

- Python - `python_api\help\index.html`

## Example programs

Example programs (with resources) for the Eduction Python API are delivered as [resources](../../resources/eduction/sdk) that are part of this tutorial.  The sample programs cover topics:

- performing different types of extraction / redaction.
- compiling an XML grammar into an ECR file

### `eduction_from_config`

The `eduction_from_config` sample program accepts a configuration file as you've been using in the other Eduction lessons, an UTF-8 text file and a path to the output JSON file.

#### Run `eduction_from_config`

Go ahead and run `eduction_from_config`.  A Windows batch file `run_eduction_from_config.bat` is provided.

> NOTE: Before proceeding make sure the `VERSION`, `PLATFORM` and `PYTHON_HOME` are correct for your environment.

```sh
> cd C:\OpenText\EductionSDK_25.1.0_WINDOWS_x86_64\samples\eduction_from_config\python
> run_eduction_from_config.bat
Creating EDK Factory.
Using Eduction license key: C:\OpenText\EductionSDK_25.1.0_WINDOWS_X86_64\licensekey.dat
Using Eduction version key: C:\OpenText\\EductionSDK_25.1.0_WINDOWS_X86_64\versionkey.dat
Creating EDK Engine from config: test\config\test.cfg
Successfully configured 1 post-processing tasks.
```

Review `educed.EDK.JSON` to see the match information. The program should run and produce an output file containing two matches, as follows:

```json
{
"matches": [
{
  "name": "test/two_words",
  "original": "foo bar",
  "offset": 12,
  "components": [
    {
      "name": "FIRST",
      "text": "foo",
      "offset": 0
    },
    {
      "name": "SECOND",
      "text": "bar",
      "offset": 4
    }
  ]
},
{
  "name": "test/two_words",
  "original": "baz bah",
  "offset": 20,
  "components": [
    {
      "name": "FIRST",
      "text": "baz",
      "offset": 0
    },
    {
      "name": "SECOND",
      "text": "bah",
      "offset": 4
    }
  ]
}
]}
```

For extra credit, try `eduction_from_config` on other Eduction configurations, insuring that configuration file paths are correct.

Review the `eduction_from_config.py` Python source code to gain more insights into how to incorporate the Eduction SDK Python API into your application.

### `compile`

In some use cases for Eduction, custom grammars either for net-new entities and/or extending the entities in the licensed grammar packs.

> NOTE: While the Eduction SDK engine does support XML based resource files, pre-compiling them into ECRs is recommended.

The `compile` sample program accepts a grammar XML and output ECR.

#### Run `compile`

Go ahead and run `compile`.  A Windows batch file `run_compile.bat` is provided.

> NOTE: Before proceeding make sure the `EDK_HOME`, `MAVEN_HOME` and `JAVA_HOME` are correct for your environment.

```sh
> cd C:\OpenText\EductionSDK_25.1.0_WINDOWS_x86_64\samples\compile\Python
> run_compile.bat
Creating EDK Factory.
Using Eduction license key: C:\OpenText\EductionSDK_25.1.0_WINDOWS_X86_64\licensekey\licensekey.dat
Using Eduction version key: C:\OpenText\EductionSDK_25.1.0_WINDOWS_X86_64\versionkey.dat
Creating EDK Engine
Compiling grammar: test\source\test.xml
```

A `test.ecr` from the `src/test.xml` source should be generated.

```sh
> edktool.exe list test.ecr`
```

For extra credit, try `compile` on other Eduction grammar XML.

Review the `compile.py` Python source code to gain more insights into how to incorporate the Eduction SDK Python API into your application.

### `redaction`

In some use cases for Eduction, custom grammars either for net-new entities and/or extending the entities in the licensed grammar packs.

> NOTE: While the Eduction SDK engine does support XML based resource files, pre-compiling them into ECRs is recommended.

The `redaction.py` sample program accepts a configuration file as you've been using in the other Eduction lessons, an UTF-8 text file and a path to the redacted TXT file.

#### Run `redaction`

Go ahead and run `redaction`.  A Windows batch file `run_test.bat` is provided.

> NOTE: Before proceeding make sure the `EDK_HOME`, `MAVEN_HOME` and `JAVA_HOME` are correct for your environment.

```sh
> cd C:\OpenText\EductionSDK_25.1.0_WINDOWS_x86_64\samples\redaction\java
> run_redaction.bat
Creating EDK Factory.
Using Eduction license key: C:\OpenText\EductionSDK_25.1.0_WINDOWS_X86_64\licensekey.dat
Using Eduction version key: C:\OpenText\EductionSDK_25.1.0_WINDOWS_X86_64\versionkey.dat
Creating EDK Engine from config: test\config\basic.cfg
Redacting input: test\input\input.txt
```

A `redacted.EDK.TXT` should be generated and have the same output as in the `..\resources\test\expectations\redaction.txt`.

For extra credit, try `redaction` with the other Eduction configuration file `entity_name.cfg`.

Review the `redaction.py` Python source code to gain more insights into how to incorporate the Eduction SDK Python API into your application.

## Conclusion

You now understand the basics of the Eduction SDK Java API.

As extra credit, build and run the other sample programs in `EductionSDK_<VERSION>_<PLATFORM>\samples` and `EductionGrammars_<VERSION>_COMMON\pii\edk_samples`.  Refer to the changes in these resources and leverage the build tools & tips.

Next, why not try more tutorials to explore some of the other features available in Eduction, linked from [here](../eduction/README.md#capability-showcase).

## See also

- [Eduction SDK User and Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/EductionSDK_25.1_Documentation/Guides/html/)
- [Eduction Server User and Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/EductionServer_25.1_Documentation/Help/Content/_ACI_Welcome.htm)
- [Eduction Grammars User Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/EductionGrammars_25.1_Documentation/Help/)
- [Knowledge Discovery Release Notes - Eduction](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/IDOLReleaseNotes_25.1_Documentation/idol/Content/SDKs/Eduction.htm)
