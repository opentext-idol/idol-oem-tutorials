# Filter SDK Java API

The Filter SDK allows you to embed file content extraction functionality into other services.

To facilitate embedding, the Filter SDK has APIs for C, C++, Java, .NET and Python.  In addition, the Filter SDK runs natively on the following platforms: Windows (x86_32, x86_64, ARM_64), Linux (x86_32, x86_64 and ARM_64), MacOS (x86_64 and Apple M*).

In this lesson, you will:

- Familiarize yourself with the Filter SDK's Java API
- Build from source code and use a sample program that replicates a common use case of the Filter SDK

> NOTE: This guide assumes you have already completed the [Filter SDK introduction](./introduction.md#introduction-to-filter-sdk) lesson.

---

- [Setup](#setup)
  - [Resources](#resources)
  - [Environment and compilers](#environment-and-compilers)
    - [Compiler](#compiler)
    - [Other](#other)
  - [License key](#license-key)
- [API Setup](#api-setup)
  - [Building the sample program](#building-the-sample-program)
- [Process files](#process-files)
- [Conclusion](#conclusion)
- [See also](#see-also)

---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

> NOTE: This lesson assumes you have already completed the [Filter SDK introduction](./introduction.md#introduction-to-filter-sdk) lesson covering essential setup steps (for example, required downloads and installation steps) and basic Filter SDK concepts.

### Resources

You must download the following resources before you continue:

- source code for this tutorial: [StreamingTutorial](../../resources/keyview_filter/sdk/Java/StreamingTutorial)
- optional sample files for detection and various extraction options located [here](../../resources/keyview_filter)

### Environment and compilers

#### Compiler

To create a program that uses the Filter SDK, you need to install a [supported compiler](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/KeyviewFilterSDK_25.1_Documentation/Guides/html/java-programming/Content/Shared/_KV_Platform_Compilers.htm), and use it to build your program.

#### Other

Apache [Ant](https://ant.apache.org/) is used with `StreamingTutorial`.  Ant version 1.9.16 is recommended.

### License key

You need a Filter SDK license key to proceed with this lesson.  If you skipped the introduction setup step to acquire a license key, see [here](./introduction.md#activate-a-license-key).

## API Setup

### Building the sample program

Deploy the downloaded `StreamingTutorial` build tools and source files to the location of your choice.  This tutorial uses `C:\OpenText\KeyviewFilterSDK_25.1.0_WINDOWS_X86_64\javaapi\StreamingTutorial`.

To build `StreamingTutorial` a few modifications of the provided resources are required:

1. Copy `idol-oem-tutorials\resources\keyview_filter\sdk\Java\StreamingTutorial` to `%KEYVIEW_HOME%\javaapi\StreamingTutorial`.
1. The `build.xml` should properly resolve the relative path to `KeyView.jar`.
1. Update the provided `build.bat` or `build.sh` to set the `JAVA_HOME` and `ANT_HOME` environment variables that match your system.
1. Update `src\Config.java`, replacing the `KEYVIEW_LICENSEKEY_STRING` with the contents of the `licensekey.dat` file and `KEYVIEW_BIN_FOLDER` with the location of your Filter SDK bin folder.

Go ahead and run `build.bat` or `build.sh`.

```sh
> cd C:\OpenText\KeyviewFilterSDK_25.1.0_WINDOWS_X86_64\javaapi\StreamingTutorial
> build.bat

Buildfile: C:\OpenText\KeyviewFilterSDK_25.1.0_WINDOWS_X86_64\javaapi\StreamingTutorial\build.xml

compile:
    [javac] Compiling 11 source files to C:\OpenText\KeyviewFilterSDK_25.1.0_WINDOWS_X86_64\javaapi\StreamingTutorial\build\classes

jar:
    [mkdir] Created dir: C:\OpenText\KeyviewFilterSDK_25.1.0_WINDOWS_X86_64\javaapi\StreamingTutorial\build\jar
      [jar] Building jar: C:\OpenText\KeyviewFilterSDK_25.1.0_WINDOWS_X86_64\javaapi\StreamingTutorial\build\jar\StreamingTutorial.jar

BUILD SUCCESSFUL
Total time: 1 second
```

## Process files

To run `StreamingTutorial` a few modifications of the provided resources are required:
1. Update the provided `StreamingTutorial.bat` or `StreamingTutorial.sh` to set the `JAVA_HOME` and `KEYVIEW_BIN_FOLDER` environment variables that match your system.

Run `StreamingTutorial.bat`.
```sh
> cd C:\OpenText\KeyviewFilterSDK_25.1.0_WINDOWS_X86_64\javaapi\StreamingTutorial
> StreamingTutorial.bat 
Processing input file C:\OpenText\idol-oem-tutorials\resources\keyview_filter\KeyViewFilterSDK_12.12.0_ReleaseNotes_en.rar to C:\OpenText\idol-oem-tutorials\resources\keyview_filter\KeyViewFilterSDK_12.12.0_ReleaseNotes_en.rar.KV_25.1.0_TEXT.TXT
Processing subfile KeyViewFilterSDK_12.12.0_ReleaseNotes_en.rar/KeyViewFilterSDK_12.12.0_ReleaseNotes_en.pdf
```

Try `StreamingTutorial` with other sample documents provided with this tutorial and your own files.

## Conclusion

You have now used the Filter SDK API for Java to automatically detect the file format (and other key properties) and to extract metadata, text and sub-files.

Next, why not try more tutorials to explore some of the other features available in Filter SDK, linked from [here](../keyview_filter/README.md#capability-showcase).

## See also

- [Filter SDK C Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/KeyviewFilterSDK_25.1_Documentation/Guides/html/c-programming/index.html)
- [Filter SDK C++ Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/KeyviewFilterSDK_25.1_Documentation/Guides/html/cpp-programming/index.html)
- [Filter SDK Java Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/KeyviewFilterSDK_25.1_Documentation/Guides/html/java-programming/index.html)
- [Filter SDK .NET Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/KeyviewFilterSDK_25.1_Documentation/Guides/html/dotnet-programming/index.html)
- [Filter SDK Python Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/KeyviewFilterSDK_25.1_Documentation/Guides/html/python-programming/)
- [File Content Extraction Release Notes](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.1/IDOLReleaseNotes_25.1_Documentation/oem/Content/_KeyView.htm)