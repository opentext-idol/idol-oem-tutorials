# Named Entity Recognition SDK Python API

The Named Entity Recognition SDK is designed to be embedded into other services.

To facilitate embedding, the Named Entity Recognition SDK has APIs for C, Java, Python and .NET.  In addition, the Named Entity Recognition SDK runs natively on the following platforms: Windows (x86_64, x86_32 and ARM_64), Linux (x86_64 and ARM_64), MacOS (x86_64 and Apple M*).

In this lesson, you will:

- use the Named Entity Recognition SDK Python API to perform extraction using a configuration file
- use the Named Entity Recognition SDK Python API to compile a grammar XML into an ECR

The [Named Entity Recognition User and Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/EductionSDK_25.4_Documentation/Guides/html/Content/EductionSDK/APIReference/Python_APIConcepts.htm) has sections on this topic which will be referenced in this lesson.

> NOTE: This lesson only covers the Named Entity Recognition SDK APIs and does not cover Named Entity Recognition Server. See [here](./README.md#use-named-entity-recognition-server) for a lesson on Named Entity Recognition Server.

> NOTE: This guide assumes you have already completed the introductory Named Entity Recognition [tutorial](../eduction/introduction.md).

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

Refer to `README.md` in the `C:\OpenText\EductionSDK_25.4.0_WINDOWS_X86_64\samples` folder for API language and platform specific requirements and instructions to build the sample programs.

> NOTE: This lesson assumes you have already completed the [Named Entity Recognition SDK introduction](../eduction/introduction.md) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic Named Entity Recognition concepts.

### License and Version key dat files

Deploy the `licensekey.dat` and `versionkey.dat` files to the EductionSDK home directory (e.g. `C:\OpenText\EductionSDK_25.4.0_WINDOWS_X86_64`).

> NOTE: An improved method to incorporate `versionkey.dat` is implemented as part of the provided resources, where you must ignore the release notes recommendation to pre-concatenate the `licensekey.dat` and `versionkey.dat`, delimited by a `;`.

### Resources

You must download the following resources before you continue:

- source code and build tools
  - [eduction_from_config/python](../../resources/eduction/sdk/samples/eduction_from_config/python/)
  - [compile/python](../../resources/eduction/sdk/samples/compile/python)
  - [redaction/python](../../resources/eduction/sdk/samples/redaction/python)
  - [run_pip_install_whl.bat](../../resources/eduction/sdk/samples)


> NOTE: Deploy these resources to the `%EDK_HOME%\samples` folder, adding to and/or replacing what is provided with EductionSDK.

### Environment and Compilers

- Refer to the `System Requirements` section of the [Getting Started Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/IDOLServer_25.4_Documentation/Guides/html/gettingstarted/Content/Install_Run_IDOL/Install/System_Requirements.htm) for general software dependencies.
- Refer to [Named Entity Recognition User & Programming Guide - Deploy Named Entity Recognition SDK - Java API Component](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/EductionSDK_25.4_Documentation/Guides/html/Content/EductionSDK/DeployEductionSDK/Java_API.htm) for API and platform specific software dependencies.
- The `README.md` in `C:\OpenText\EductionSDK_25.4.0_WINDOWS_X86_64\samples` notes more API language and platform specific requirements (*e.g.* compiler information, build tools) and build tips.

A Python interpreter (including pip) are used to install the `edk-version-py3-none-any.whl` and run the sample programs.  The `edk-version-py3-none-any.whl` for version 25.4 must deployed to your Python environment.  Refer to [Named Entity Recognition User & Programming Guide - API Reference - Python API Concepts](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/EductionSDK_25.4_Documentation/Guides/html/Content/EductionSDK/APIReference/Python_APIConcepts.htm#Installation) for tips on installing `edk-version-py3-none-any.whl`.

A Windows batch file `run_pip_install_whl.bat` and Bourne shell script `run_pip_install_whl.sh` are provided in the `C:\OpenText\idol-oem-tutorials\resources\eduction\sdk\samples`.

> NOTE: Before proceeding make sure the `EDK_HOME` and other environment variables are correct for your environment.

```sh
> cd C:\OpenText\EductionSDK_25.4.0_WINDOWS_x86_64\samples
> run_pip_install_whl.bat
Defaulting to user installation because normal site-packages is not writeable
Processing c:\_opentext\idolserver-25.4\eductionsdk_25.4.0\bin\edk-25.4.0-py3-none-any.whl
Installing collected packages: edk
  WARNING: The script edk-tool.exe is installed in 'C:\Users\<USERNAME>\AppData\Roaming\Python\Python313\Scripts' which is not on PATH.
  Consider adding this directory to PATH or, if you prefer to suppress this warning, use --no-warn-script-location.
Successfully installed edk-25.4.0
```

## API Documentation

API specific documentation is located in sub-folders of `C:\OpenText\EductionSDK_25.4.0_WINDOWS_X86_64\` as noted below:

- Python - `python_api\help\index.html`

## Example programs

Example programs (with resources) for the Named Entity Recognition Python API are delivered as [resources](../../resources/eduction/sdk) that are part of this tutorial.  The sample programs cover topics:

- performing different types of extraction / redaction.
- compiling an XML grammar into an ECR file

### `eduction_from_config`

The `eduction_from_config` sample program accepts a configuration file as you've been using in the other Named Entity Recognition lessons, an UTF-8 text file and a path to the output JSON file.

#### Run `eduction_from_config`

Go ahead and run `eduction_from_config`.  A Windows batch file `run_eduction_from_config.bat` is provided.

> NOTE: Before proceeding make sure the `VERSION`, `PLATFORM` and other environment variables are correct for your environment.

```sh
> cd C:\OpenText\EductionSDK_25.4.0_WINDOWS_x86_64\samples\eduction_from_config\python
> run_eduction_from_config.bat
Creating EDK Factory.
Using Eduction license key: C:\OpenText\EductionSDK_25.4.0_WINDOWS_X86_64\licensekey.dat
Using Eduction version key: C:\OpenText\EductionSDK_25.4.0_WINDOWS_X86_64\versionkey.dat
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

For extra credit, try `eduction_from_config` on other Named Entity Recognition configurations, insuring that configuration file paths are correct.

Review the `eduction_from_config.py` Python source code to gain more insights into how to incorporate the Named Entity Recognition SDK Python API into your application.

### `compile`

In some use cases for Named Entity Recognition, custom grammars either for net-new entities and/or extending the entities in the licensed grammar packs.

> NOTE: While the Named Entity Recognition SDK engine does support XML based resource files, pre-compiling them into ECRs is recommended.

The `compile` sample program accepts a grammar XML and output ECR.

#### Run `compile`

Go ahead and run `compile`.  A Windows batch file `run_compile.bat` is provided.

> NOTE: Before proceeding make sure the `EDK_HOME`, `MAVEN_HOME` and `JAVA_HOME` are correct for your environment.

```sh
> cd C:\OpenText\EductionSDK_25.4.0_WINDOWS_x86_64\samples\compile\Python
> run_compile.bat
Creating EDK Factory.
Using Eduction license key: C:\OpenText\EductionSDK_25.4.0_WINDOWS_X86_64\licensekey\licensekey.dat
Using Eduction version key: C:\OpenText\EductionSDK_25.4.0_WINDOWS_X86_64\versionkey.dat
Creating EDK Engine
Compiling grammar: test\source\test.xml
```

A `test.ecr` from the `src/test.xml` source should be generated.

```sh
> edktool.exe list test.ecr`
```

For extra credit, try `compile` on other Named Entity Recognition grammar XML.

Review the `compile.py` Python source code to gain more insights into how to incorporate the Named Entity Recognition SDK Python API into your application.

### `redaction`

In some use cases for Named Entity Recognition, custom grammars either for net-new entities and/or extending the entities in the licensed grammar packs.

> NOTE: While the Named Entity Recognition SDK engine does support XML based resource files, pre-compiling them into ECRs is recommended.

The `redaction.py` sample program accepts a configuration file as you've been using in the other Named Entity Recognition lessons, an UTF-8 text file and a path to the redacted TXT file.

#### Run `redaction`

Go ahead and run `redaction`.  A Windows batch file `run_test.bat` is provided.

> NOTE: Before proceeding make sure the `EDK_HOME`, `MAVEN_HOME` and `JAVA_HOME` are correct for your environment.

```sh
> cd C:\OpenText\EductionSDK_25.4.0_WINDOWS_x86_64\samples\redaction\java
> run_redaction.bat
Creating EDK Factory.
Using Eduction license key: C:\OpenText\EductionSDK_25.4.0_WINDOWS_X86_64\licensekey.dat
Using Eduction version key: C:\OpenText\EductionSDK_25.4.0_WINDOWS_X86_64\versionkey.dat
Creating EDK Engine from config: test\config\basic.cfg
Redacting input: test\input\input.txt
```

A `redacted.EDK.TXT` should be generated and have the same output as in the `..\resources\test\expectations\redaction.txt`.

For extra credit, try `redaction` with the other Named Entity Recognition configuration file `entity_name.cfg`.

Review the `redaction.py` Python source code to gain more insights into how to incorporate the Named Entity Recognition SDK Python API into your application.

## Conclusion

You now understand the basics of the Named Entity Recognition SDK Java API.

As extra credit, build and run the other sample programs in `EductionSDK_<VERSION>_<PLATFORM>\samples` and `EductionGrammars_<VERSION>_COMMON\pii\edk_samples`.  Refer to the changes in these resources and leverage the build tools & tips.

Next, why not try more tutorials to explore some of the other features available in Named Entity Recognition, linked from [here](../eduction/README.md#capability-showcase).

## See also

- [Named Entity Recognition SDK User and Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/EductionSDK_25.4_Documentation/Guides/html/)
- [Named Entity Recognition Server User and Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/EductionServer_25.4_Documentation/Help/Content/_ACI_Welcome.htm)
- [Named Entity Recognition Grammars User Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/EductionGrammars_25.4_Documentation/Help/)
- [Knowledge Discovery Release Notes - Named Entity Recognition](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/IDOLReleaseNotes_25.4_Documentation/idol/Content/SDKs/Eduction.htm)
