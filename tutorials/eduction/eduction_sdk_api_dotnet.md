# Eduction SDK .NET API

The Eduction SDK is designed to be embedded into other services.

To facilitate embedding, the Eduction SDK has APIs for C, Java and .NET.  In addition, the Eduction SDK runs natively on the following platforms: Windows (x86_64, x86_32 and ARM_64), Linux (x86_64 and ARM_64), MacOS (x86_64 and Apple M*).

In this lesson, you will:

- use the Eduction SDK .NET API to perform extraction using a configuration file
- use the Eduction SDK .NET API to compile a grammar XML into an ECR

The [Eduction User and Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/EductionSDK_25.1_Documentation/Guides/html/Content/EductionSDK/APIReference/DotNet_APIConcepts.htm) has sections on this topic which will be referenced in this lesson.

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
    - [Build and run `compile`](#build-and-run-compile)
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

There are no provided resources for this lesson.

### Environment and Compilers

- Refer to the `System Requirements` section of the [Getting Started Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/IDOLServer_25.1_Documentation/Guides/html/gettingstarted/Content/Install_Run_IDOL/Install/System_Requirements.htm) for general software dependencies.
- Refer to [Eduction User & Programming Guide - Deploy Eduction SDK - .NET API Component](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/EductionSDK_25.1_Documentation/Guides/html/Content/EductionSDK/DeployEductionSDK/DotNet_API.htm) for API and platform specific software dependencies.
- The `README.md` in `C:\OpenText\EductionSDK_25.1.0_WINDOWS_X86_64\samples` notes more API language and platform specific requirements (*e.g.* compiler information, build tools) and build tips.

> HINT: For example, if you use Visual Studio Community 2022 in Windows 11, installed from <https://visualstudio.microsoft.com/downloads/>, run the Visual Studio Installer and ensure you have the ".NET Core 2.1 Runtime" component installed:
>
> ![vs_2022_dotnet_install_2-1](./figs/vs_2022_dotnet_install_2-1.png)

## API Documentation

API specific documentation is located in sub-folders of `C:\OpenText\EductionSDK_25.1.0_WINDOWS_X86_64\` as noted below:

- .NET - `dotnet_api\help\index.html`

## Example programs

Example programs (with resources) ship with the `EductionSDK_<VERSION>_<PLATFORM>.zip` and `EductionGrammars_<VERSION>_COMMON.zip`.  The sample programs cover topics:

- performing different types of extraction / redaction.
- compiling an XML grammar into an ECR file

### `eduction_from_config`

The `eduction_from_config` sample program accepts a configuration file as you've been using in the other Eduction lessons, an UTF-8 text file, a path to the output JSON file and some optional arguments to override the configuration.

#### Sample `eduction_from_config` code

The C# sample `eduction_from_config` application code lives in: `C:\OpenText\EductionSDK_25.1.0_WINDOWS_X86_64\samples\eduction_from_config\dotnet`.

Double-click on the `eduction_from_config.csproj` to open the sample code, *e.g.* in Visual Studio 2022.

#### Build `eduction_from_config`

In the top menu bar, click the green play icon to build the project in debug mode:

![vs_2022_dotnet_debug_build](./figs/vs_2022_dotnet_debug_build.png)

After successfully building, the application will automatically run.

You will see an error message to explain that the sample application expects to received some input options to run:

![vs_2022_dotnet_debug_run](./figs/vs_2022_dotnet_debug_run.png)

#### Run `eduction_from_config`

Let's provide the required input options and run in debug mode again.

- Click the debug properties menu option to open the "Launch Profiles" window:
    ![vs_2022_dotnet_debug_props_menu](./figs/vs_2022_dotnet_debug_props_menu.png)

    > NOTE: This sample application comes with a resources folder containing test files, which we will use, located *e.g.* at `C:\OpenText\EductionSDK_25.1.0_WINDOWS_X86_64\samples\eduction_from_config\resources\test`.

- In the "Command line arguments" input box, enter the following three paths (separated onto new lines):

    ```sh
    "..\resources\test\config\test.cfg"
    "..\resources\test\input\input.txt"
    "..\resources\test\test_output_dotnet.json"
    ```

- In the "Working directory" input box, enter the following path:

    ```sh
    C:\OpenText\EductionSDK_25.1.0_WINDOWS_X86_64\samples\eduction_from_config\dotnet
    ```

    ![vs_2022_dotnet_debug_props_cmd](./figs/vs_2022_dotnet_debug_props_cmd.png)

- Close the "Launch Profiles" window.
  
- In the top menu bar, again click the green play icon to re-build the project in debug mode.
  
    ![vs_2022_dotnet_debug_run2](./figs/vs_2022_dotnet_debug_run2.png)

This time the program should run and produce an output file `C:\OpenText\EductionSDK_25.1.0_WINDOWS_X86_64\samples\eduction_from_config\resources\test\test_output_dotnet.json` containing two matches, as follows:

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

Review the `eduction_from_config` C# source code to gain more insights into how to incorporate the Eduction SDK .NET API into your application.

### `compile`

In some use cases for Eduction, custom grammars either for net-new entities and/or extending the entities in the licensed grammar packs.

> NOTE: While the Eduction SDK engine does support XML based resource files, pre-compiling them into ECRs is recommended.

The `compile` sample program accepts a grammar XML and output ECR.

#### Sample `compile` code

The C# sample `compile` application code lives in: `C:\OpenText\EductionSDK_25.1.0_WINDOWS_X86_64\samples\compile\dotnet`.

Double-click on the `compile.csproj` to open the sample code, *e.g.* in Visual Studio 2022.

#### Build and run `compile`

- In the top menu bar, click next to the green play icon to open the dropdown options menu:

    ![vs_2022_dotnet_debug_options](./figs/vs_2022_dotnet_debug_options.png)

- Click the debug properties menu option to open the "Launch Profiles" window:
  
    > NOTE: This sample application comes with a resources folder containing test files, which we will use, located *e.g.* at `C:\OpenText\EductionSDK_25.1.0_WINDOWS_X86_64\samples\compile\resources\test`.

- In the "Command line arguments" input box, enter the following three paths (separated onto new lines):

    ```sh
    "..\resources\test\source\test.xml"
    "..\resources\test\test_dotnet.ecr"
    ```

- In the "Working directory" input box, enter the following path:

    ```sh
    C:\OpenText\EductionSDK_25.1.0_WINDOWS_X86_64\samples\compile\dotnet
    ```

    ![vs_2022_dotnet_debug_props_cmd2](./figs/vs_2022_dotnet_debug_props_cmd2.png)

- Close the "Launch Profiles" window.
  
- In the top menu bar, click the green play icon to build and run the project in debug mode.

The program should run and produce a compiled grammar file `C:\OpenText\EductionSDK_25.1.0_WINDOWS_X86_64\samples\compile\resources\test\test_dotnet.ecr`.

```sh
> edktool list "..\resources\test\test_dotnet.ecr"

Eduction EDKTool Utility v25.1.0
Loading resource file:
..\resources\test\test_dotnet.ecr


Grammar version:        4.0

Compiled using Edktool: 25.1.0

Listing entities:
test/two_words

0.289 seconds elapsed
```

For extra credit, try `compile` on other Eduction grammar XML.

Review the `compile` C# source code to gain more insights into how to incorporate the Eduction SDK .NET API into your application.

## Conclusion

You now understand the basics of the Eduction SDK .NET API.

As extra credit, build and run the other sample programs in `EductionSDK_<VERSION>_<PLATFORM>\samples` and `EductionGrammars_<VERSION>_COMMON\pii\edk_samples`.  Refer to the changes in these resources and leverage the build tools & tips.

Next, why not try more tutorials to explore some of the other features available in Eduction, linked from [here](../eduction/README.md#capability-showcase).

## See also

- [Eduction SDK User and Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/EductionSDK_25.1_Documentation/Guides/html/)
- [Eduction Server User and Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/EductionServer_25.1_Documentation/Help/Content/_ACI_Welcome.htm)
- [Eduction Grammars User Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/EductionGrammars_25.1_Documentation/Help/)
- [Knowledge Discovery Release Notes - Eduction](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/IDOLReleaseNotes_25.1_Documentation/idol/Content/SDKs/Eduction.htm)
