# Eduction SDK APIs

The Eduction SDK is designed to be embedded into other services.

To facilitate embedding, the Eduction SDK has APIs for C, Java, Python and .NET.  In addition, the Eduction SDK runs natively on the following platforms: Windows (x86_64, x86_32 and ARM_64), Linux (x86_64 and ARM_64), MacOS (x86_64 and Apple M*). 

In this lesson, you will:
- learn the locations of documentation to setup and use the Eduction SDK APIs
- use the Eduction SDK APIs to perform extraction using a configuration file
- use the Eduction SDK APIs to compile a grammar XML into an ECR

The [Eduction User and Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_3/EductionSDK_24.3_Documentation/Guides/html/Content/EductionSDK/APIReference/apiReference.htm) has excellent sections on this topic which will be heavily relied upon in this lesson.

> NOTE: This lesson only covers the Eduction SDK APIs and does not cover Eduction Server. See [here](./README.md#use-idol-eduction-server) for a lesson on Eduction Server.

> NOTE: This guide assumes you have already completed the introductory Eduction [tutorial](../eduction/introduction.md#eduction-sdk-introduction).

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

Refer to `README.md` in the `C:\OpenText\EductionSDK_24.3.0_WINDOWS_X86_64\samples` folder for API language and platform specific requirements and instructions to build the sample programs.

> NOTE: This lesson assumes you have already completed the [Eduction SDK introduction](../eduction/introduction.md#eduction-sdk-introduction) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic Eduction concepts.

### Required third-party tools

- Refer to the `System Requirements` section of the [IDOL Getting Started Guide](https://www.microfocus.com/documentation/idol/IDOL_24_3/IDOLServer_24.3_Documentation/Guides/html/gettingstarted/Content/Install_Run_IDOL/Install/System_Requirements.htm) for general software dependencies.
- Refer to [Eduction User & Programming Guide - Deploy Eduction SDK](https://www.microfocus.com/documentation/idol/IDOL_24_3/EductionSDK_24.3_Documentation/Guides/html/Content/EductionSDK/DeployEductionSDK/deploySDK.htm) for API and platform specific software dependencies.
- And again the `README.md` in `C:\OpenText\EductionSDK_24.3.0_WINDOWS_X86_64\samples` notes more API language and platform specific requirements (*e.g.* compiler information, build tools) and build tips.
- The programming language specific sections include more details on this topic building upon the information in the `README.md`.

## API Documentation

API specific documentation is located in sub-folders of `C:\OpenText\EductionSDK_24.3.0_WINDOWS_X86_64\` as noted below:
- C - `c_api\help\index.html`
- Java - `java_api\help\index.html`
- Python - `python_api\help\index.html`
- .NET - `dotnet_api\help\index.html`

## Example programs

Example programs (with resources) ship with the `EductionSDK_<VERSION>_<PLATFORM>.zip` and `EductionGrammars_<VERSION>_COMMON.zip`.  The sample programs cover topics:
- compiling an XML grammar into an ECR file
- performing different types of extraction / redaction.
 
Refer to the [Example Programs](https://www.microfocus.com/documentation/idol/IDOL_24_3/EductionSDK_24.3_Documentation/Guides/html/Content/EductionSDK/APIReference/Example_Programs.htm) section of the documentation for details on the `EductionSDK_<VERSION>_<PLATFORM>\samples`.

The `EductionGrammars_<VERSION>_COMMON.zip` has PII specific samples, as well as C++ API examples.

Go ahead and build and run `eduction_from_config` and/or `compile` for you preferred API language / platform. Refer to `C:\OpenText\EductionSDK_24.3.0_WINDOWS_X86_64\samples\README.md` for guidance and follow the API language specific lessons below.
- [C](./eduction_sdk_api_c.md),
- [Java](./eduction_sdk_api_java.md)
- [Python](./eduction_sdk_api_python.md)
- [.NET](./eduction_sdk_api_dotnet.md).

## Conclusion

You now understand the basics of the Eduction SDK API.

As extra credit, build and run the other sample programs in `EductionSDK_<VERSION>_<PLATFORM>\samples` and `EductionGrammars_<VERSION>_COMMON\pii\edk_samples`.

Next, why not try more tutorials to explore some of the other features available in IDOL Eduction, linked from [here](../eduction/README.md#capability-showcase).

## See also

- [IDOL Eduction SDK User and Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_3/EductionSDK_24.3_Documentation/Guides/html/)
- [IDOL Eduction Server User and Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_3/EductionServer_24.3_Documentation/Help/Content/_ACI_Welcome.htm)
- [PCI Technical Note](https://www.microfocus.com/documentation/idol/IDOL_24_3/EductionGrammars_24.3_Documentation/PCI/)
- [PII Technical Note](https://www.microfocus.com/documentation/idol/IDOL_24_3/EductionGrammars_24.3_Documentation/PII/)
- [PHI Technical Note](https://www.microfocus.com/documentation/idol/IDOL_24_3/EductionGrammars_24.3_Documentation/PHI/)
- [Government Eduction Package Technical Note](https://www.microfocus.com/documentation/idol/IDOL_24_3/EductionGrammars_24.3_Documentation/GOV/)
- [IDOL and KeyView OEM Release Notes - Eduction](https://www.microfocus.com/documentation/idol/IDOL_24_3/IDOLReleaseNotes_24.3_Documentation/idol/Content/SDKs/Eduction.htm)