# Eduction SDK APIs

As noted in the IDOL, KeyView and Eduction APIs [README.md](./README.md), the Eduction SDK is designed to be embedded into other services.

To facilitate embedding, the Eduction SDK has APIs for C, Java and .Net.  In addition, the Eduction SDK runs natively on the following platforms: Windows (x86_64), Linux (x86_64 and ARM_64), MacOS (x86_64 and Apple M*). 

In this lesson, you will:
- learn the locations of documentation to setup and use the Eduction SDK APIs
- use the Eduction SDK APIs to perform extraction using a configuration file
- use the Eduction SDK APIs to compile a grammar XML into an ECR

The [Eduction User and Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_12/EductionSDK_12.12_Documentation/Guides/html/Content/EductionSDK/APIReference/apiReference.htm) has excellent sections on this topic which will be heavily relied upon in this lesson.

> NOTE: This lesson only covers the Eduction SDK APIs and does not cover Eduction Server. See [here](../tutorials/README.md#use-idol-eduction-server) for a lesson on Eduction Server.

> NOTE: This guide assumes you have already completed the introductory Eduction [tutorial](../eduction/introduction.md#eduction-sdk-introduction).

---

- [Setup](#setup)
  - [Required third-party tools](#required-third-party-tools)
- [API Documentation](#api-documentation)
- [Example programs](#example-programs)
  - [Perform extraction](#perform-extraction)
  - [Compile grammar](#compile-grammar)
- [Conclusion](#conclusion)
- [See also](#see-also)
  
---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

Refer to `README.md` in the `C:\MicroFocus\EductionSDK_12.12.0_WINDOWS_X86_64\samples` folder for API language and platform specific requirements and instructions to build the sample programs.

> NOTE: This lesson assumes you have already completed the [Eduction SDK introduction](../eduction/introduction.md#eduction-sdk-introduction) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic Eduction concepts.

### Required third-party tools

- Refer to the `Requirements - Software Dependencies` section of the [Release Notes](https://www.microfocus.com/documentation/idol/IDOL_12_12/EductionSDK_12.12_Documentation/Eduction_12.12.0_ReleaseNotes_en.pdf) for API and platform specific software dependencies.  
- And again the `README.md` in `C:\MicroFocus\EductionSDK_12.12.0\samples` notes more API language and platform specific requirements (*e.g.* compiler information, build tools) and build tips.

## API Documentation

API specific documentation is located in sub-folders of `C:\MicroFocus\EductionSDK_12.12.0_WINDOWS_X86_64\` as noted below:
- C - `c_api\help\index.html`
- Java - `java_api\help\index.html`
- .Net - `dotnet_api\help\index.html`

## Example programs

Example programs (with resources) ship with the `EductionSDK_<VERSION>_<PLATFORM>.zip` and `EductionGrammars_<VERSION>_COMMON.zip`.  The sample programs cover topics:
- compiling an XML grammar into an ECR file
- performing different types of extraction / redaction.
 
Refer to the [Example Programs](https://www.microfocus.com/documentation/idol/IDOL_12_12/EductionSDK_12.12_Documentation/Guides/html/Content/EductionSDK/APIReference/Example_Programs.htm) section of the documentation for details on the EductionSDK_<VERSION>_<PLATFORM>.zip` samples.  

The `EductionGrammars_<VERSION>_COMMON.zip` has PII specific samples as well as C++ API examples.

### Perform extraction

To get started with the Eduction SDK APIs, it is recommended to start with `eduction_from_config`.  The C, Java and .Net versions of `eduction_from_config` each accepts a configuration file as you've been using in the other Eduction lessons, an UTF-8 text file, a path to the output JSON file and some optional arguments to override the configuration.

Go ahead and build and run `eduction_from_config` for you preferred API language / platform. Again refer to `C:\MicroFocus\EductionSDK_12.12.0_WINDOWS_X86_64\samples\README.md` for guidance. 

### Compile grammar

In some use cases for Eduction, custom grammars configurable by end-users (usually administrators) is made available.  While the Eduction SDK engine does support XML based resource files, pre-compiling them into ECRs is recommended.

Go ahead and build and run `compile` for you preferred API language / platform.  Again refer to `C:\MicroFocus\EductionSDK_12.12.0_WINDOWS_X86_64\samples\README.md` for guidance.

## Conclusion

You now understand the basics of the Eduction SDK API.

As extra credit, build and run the other sample programs in `EductionSDK_<VERSION>_<PLATFORM>\samples` and `EductionGrammars_<VERSION>_COMMON\pii\edk_samples`.

If you haven't already done so, try more tutorials that explore some of the other features available in IDOL Eduction, linked from the [main page](../README.md#capability-showcase-examples).

## See also

- [IDOL Eduction SDK User and Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_12/EductionSDK_12.12_Documentation/Guides/html)
