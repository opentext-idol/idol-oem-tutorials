# Eduction SDK APIs

The Eduction SDK is designed to be embedded into other services.

To facilitate embedding, the Eduction SDK has APIs for C, Java and .NET.  In addition, the Eduction SDK runs natively on the following platforms: Windows (x86_64), Linux (x86_64 and ARM_64), MacOS (x86_64 and Apple M*). 

In this lesson, you will:
- learn the locations of documentation to setup and use the Eduction SDK APIs
- use the Eduction SDK APIs to perform extraction using a configuration file
- use the Eduction SDK APIs to compile a grammar XML into an ECR

The [Eduction User and Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_1/EductionSDK_24.1_Documentation/Guides/html/Content/EductionSDK/APIReference/apiReference.htm) has excellent sections on this topic which will be heavily relied upon in this lesson.

> NOTE: This lesson only covers the Eduction SDK APIs and does not cover Eduction Server. See [here](./README.md#use-idol-eduction-server) for a lesson on Eduction Server.

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

Refer to `README.md` in the `C:\OpenText\EductionSDK_24.1.0_WINDOWS_X86_64\samples` folder for API language and platform specific requirements and instructions to build the sample programs.

> NOTE: This lesson assumes you have already completed the [Eduction SDK introduction](../eduction/introduction.md#eduction-sdk-introduction) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic Eduction concepts.

### Required third-party tools

- Refer to the `System Requirements` section of the [IDOL Getting Started Guide](https://www.microfocus.com/documentation/idol/IDOL_24_1/IDOLServer_24.1_Documentation/Guides/html/gettingstarted/Content/Install_Run_IDOL/Install/System_Requirements.htm) for general software dependencies.
- Refer to [Eduction User & Programming Guide - Deploy Eduction SDK](https://www.microfocus.com/documentation/idol/IDOL_24_1/EductionSDK_24.1_Documentation/Guides/html/Content/EductionSDK/DeployEductionSDK/deploySDK.htm) for API and platform specific software dependencies.
- And again the `README.md` in `C:\OpenText\EductionSDK_24.1.0_WINDOWS_X86_64\samples` notes more API language and platform specific requirements (*e.g.* compiler information, build tools) and build tips.

> NOTE: For the Java code, the `pom.xml` may need to be modified as the following:
> ```diff
> ...
> <dependencies>
>    ...
>    <dependency>
>      <groupId>com.autonomy.eduction</groupId>
>      <artifactId>edk</artifactId>
> -    <version>12.11.0</version>
> +    <version>24.1.0</version>
>    </dependency>
> </dependencies> 
> ```

## API Documentation

API specific documentation is located in sub-folders of `C:\OpenText\EductionSDK_24.1.0_WINDOWS_X86_64\` as noted below:
- C - `c_api\help\index.html`
- Java - `java_api\help\index.html`
- .NET - `dotnet_api\help\index.html`

## Example programs

Example programs (with resources) ship with the `EductionSDK_<VERSION>_<PLATFORM>.zip` and `EductionGrammars_<VERSION>_COMMON.zip`.  The sample programs cover topics:
- compiling an XML grammar into an ECR file
- performing different types of extraction / redaction.
 
Refer to the [Example Programs](https://www.microfocus.com/documentation/idol/IDOL_24_1/EductionSDK_24.1_Documentation/Guides/html/Content/EductionSDK/APIReference/Example_Programs.htm) section of the documentation for details on the `EductionSDK_<VERSION>_<PLATFORM>\samples`.

The `EductionGrammars_<VERSION>_COMMON.zip` has PII specific samples, as well as C++ API examples.

### Perform extraction

To get started with the Eduction SDK APIs, it is recommended to start with the code per the table below:
|API Language|Sample Code|Resources|Documentation Reference|
|-----|--------|-----|-----|
|C|eduction_from_config|eduction_from_config|[Standalone API Usage](https://www.microfocus.com/documentation/idol/IDOL_24_1/EductionSDK_24.1_Documentation/Guides/html/Content/EductionSDK/APIReference/Example_Programs.htm)|
|Java |eduction_from_config|eduction_from_config|[Standalone API Usage](https://www.microfocus.com/documentation/idol/IDOL_24_1/EductionSDK_24.1_Documentation/Guides/html/Content/EductionSDK/APIReference/Example_Programs.htm)|
|.Net |eduction_from_config|eduction_from_config|[Standalone API Usage](https://www.microfocus.com/documentation/idol/IDOL_24_1/EductionSDK_24.1_Documentation/Guides/html/Content/EductionSDK/APIReference/Example_Programs.htm)|

The C, Java and .NET versions of `eduction_from_config` and `table_extraction` each accepts a configuration file as you've been using in the other Eduction lessons, an UTF-8 text file, a path to the output JSON file and some optional arguments to override the configuration.

Go ahead and build and run `eduction_from_config` for you preferred API language / platform. Again refer to `C:\OpenText\EductionSDK_24.1.0_WINDOWS_X86_64\samples\README.md` for guidance. 

### Compile grammar

In some use cases for Eduction, custom grammars configurable by end-users (usually administrators) is made available.  Go ahead and build and run `compile` for you preferred API language / platform.  Again refer to `C:\OpenText\EductionSDK_24.1.0_WINDOWS_X86_64\samples\README.md` for guidance.

> NOTE: While the Eduction SDK engine does support XML based resource files, pre-compiling them into ECRs is recommended.

## Conclusion

You now understand the basics of the Eduction SDK API.

As extra credit, build and run the other sample programs in `EductionSDK_<VERSION>_<PLATFORM>\samples` and `EductionGrammars_<VERSION>_COMMON\pii\edk_samples`.

If you haven't already done so, try more tutorials that explore some of the other features available in IDOL Eduction, linked from the [main page](../README.md#capability-showcase-examples).

## See also

- [IDOL Eduction SDK User and Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_1/EductionSDK_24.1_Documentation/Guides/html/)
- [IDOL Eduction Server User and Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_1/EductionServer_24.1_Documentation/Help/Content/_ACI_Welcome.htm)
- [PCI Technical Note](https://www.microfocus.com/documentation/idol/IDOL_24_1/EductionGrammars_24.1_Documentation/PCI/)
- [PII Technical Note](https://www.microfocus.com/documentation/idol/IDOL_24_1/EductionGrammars_24.1_Documentation/PII/)
- [PHI Technical Note](https://www.microfocus.com/documentation/idol/IDOL_24_1/EductionGrammars_24.1_Documentation/PHI/)
- [Government Eduction Package Technical Note](https://www.microfocus.com/documentation/idol/IDOL_24_1/EductionGrammars_24.1_Documentation/GOV/)
- [IDOL and KeyView OEM Release Notes](https://www.microfocus.com/documentation/idol/IDOL_24_1/IDOLReleaseNotes_24.1_Documentation/idol/Content/SDKs/Eduction.htm)