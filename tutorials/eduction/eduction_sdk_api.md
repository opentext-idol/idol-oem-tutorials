# Named Entity Recognition SDK APIs

The Named Entity Recognition SDK is designed to be embedded into other services.   To facilitate embedding, the Named Entity Recognition SDK has APIs for C, Java, Python and .NET.  In addition, the Named Entity Recognition SDK runs natively on the following platforms: Windows (x86_64, x86_32 and ARM_64), Linux (x86_64 and ARM_64) and MacOS (x86_64 and Apple M*).

In this lesson, you will:

- learn the locations of documentation to setup and use the Named Entity Recognition SDK APIs
- use the Named Entity Recognition SDK APIs to perform extraction using a configuration file
- use the Named Entity Recognition SDK APIs to compile a grammar XML into an ECR

The [Named Entity Recognition User and Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/EductionSDK_25.4_Documentation/Guides/html/Content/EductionSDK/APIReference/apiReference.htm) has excellent sections on this topic which will be heavily relied upon in this lesson.

> NOTE: This lesson only covers the Named Entity Recognition SDK APIs and does not cover Named Entity Recognition Server. See [here](./README.md#use-named-entity-recognition-server) for a lesson on Named Entity Recognition Server.

> NOTE: This guide assumes you have already completed the introductory Named Entity Recognition [tutorial](../eduction/introduction.md).

---

- [Setup](#setup)
  - [Required third-party tools](#required-third-party-tools)
- [API Documentation](#api-documentation)
- [Example programs](#example-programs)
- [Conclusion](#conclusion)
- [See also](#see-also)
  
---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

Refer to `README.md` in the `C:\OpenText\EductionSDK_25.4.0_WINDOWS_X86_64\samples` folder for API language and platform specific requirements and instructions to build the sample programs.

> NOTE: This lesson assumes you have already completed the [Named Entity Recognition SDK introduction](../eduction/introduction.md) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic Named Entity Recognition concepts.

### Required third-party tools

- Refer to the `System Requirements` section of the [Getting Started Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/IDOLServer_25.4_Documentation/Guides/html/gettingstarted/Content/Install_Run_IDOL/Install/System_Requirements.htm) for general [software dependencies](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/IDOLServer_25.4_Documentation/Guides/html/gettingstarted/Content/Install_Run_IDOL/Install/System_Requirements.htm#Software-Depende) and notes about [C and C++ Runtime Libraries](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/IDOLServer_25.4_Documentation/Guides/html/gettingstarted/Content/Install_Run_IDOL/Install/System_Requirements.htm#C-and-C---Runtim).
- Refer to [Named Entity Recognition User & Programming Guide - Deploy Named Entity Recognition SDK](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/EductionSDK_25.4_Documentation/Guides/html/Content/EductionSDK/DeployEductionSDK/deploySDK.htm) for API and platform specific software dependencies.
- And again the `README.md` in `C:\OpenText\EductionSDK_25.4.0_WINDOWS_X86_64\samples` notes more API language and platform specific requirements (*e.g.* compiler information, build tools) and build tips.
- The programming language specific sections include more details on this topic building upon the information in the `README.md`.

## API Documentation

API specific documentation is located in sub-folders of `C:\OpenText\EductionSDK_25.4.0_WINDOWS_X86_64\` as noted below:

- C - `c_api\help\index.html`
- Java - `java_api\help\index.html`
- Python - `python_api\help\index.html`
- .NET - `dotnet_api\help\index.html`

## Example programs

Example programs (with resources) ship with the `EductionSDK_<VERSION>_<PLATFORM>.zip` and `EductionGrammars_<VERSION>_COMMON.zip`.  The sample programs cover topics:

- compiling an XML grammar into an ECR file
- performing different types of extraction / redaction.

Refer to the [Example Programs](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/EductionSDK_25.4_Documentation/Guides/html/Content/EductionSDK/APIReference/Example_Programs.htm) section of the documentation for details on the `EductionSDK_<VERSION>_<PLATFORM>\samples`.

The `EductionGrammars_<VERSION>_COMMON.zip` has PII specific samples, as well as C++ API examples.

Go ahead and build and run `eduction_from_config` and/or `compile` for you preferred API language / platform. Refer to `C:\OpenText\EductionSDK_25.4.0_WINDOWS_X86_64\samples\README.md` for guidance and follow the API language specific lessons below.

- [C](./eduction_sdk_api_c.md),
- [Java](./eduction_sdk_api_java.md)
- [Python](./eduction_sdk_api_python.md)
- [.NET](./eduction_sdk_api_dotnet.md).

## Conclusion

You now understand the basics of the Named Entity Recognition SDK API.

As extra credit, build and run the other sample programs in `EductionSDK_<VERSION>_<PLATFORM>\samples` and `EductionGrammars_<VERSION>_COMMON\pii\edk_samples`.

Next, why not try more tutorials to explore some of the other features available in Named Entity Recognition, linked from [here](../eduction/README.md#capability-showcase).

## See also

- [Named Entity Recognition SDK User and Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/EductionSDK_25.4_Documentation/Guides/html/)
- [Named Entity Recognition Server User and Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/EductionServer_25.4_Documentation/Help/Content/_ACI_Welcome.htm)
- [Named Entity Recognition Grammars User Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/EductionGrammars_25.4_Documentation/Help/)
- [Knowledge Discovery Release Notes - Named Entity Recognition](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/IDOLReleaseNotes_25.4_Documentation/idol/Content/SDKs/Eduction.htm)
