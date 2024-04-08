# KeyView Filter SDK Java API

The KeyView Filter SDK allows you to embed KeyView functionality into other services.

To facilitate embedding, the KeyView Filter SDK has APIs for C, C++, Java, .NET and Python.  In addition, the KeyView Filter SDK runs natively on the following platforms: Windows (x86_32, x86_64, ARM_64), Linux (x86_32, x86_64 and ARM_64), MacOS (x86_64 and Apple M*). 

In this lesson, you will:

- Familiarize yourself with the Filter SDK's Java API
- Build from source code and use a sample program that replicates a common use case of the Filter SDK

> NOTE: This guide assumes you have already completed the introductory KeyView Filter SDK [tutorial](introduction.md#keyview-filter-sdk-introduction).

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

> NOTE: This lesson assumes you have already completed the [KeyView Filter SDK introduction](introduction.md#keyview-filter-sdk-introduction) lesson covering essential setup steps (for example, required downloads and installation steps) and basic KeyView Filter concepts.

### Resources

You must download the following resources before you continue:
- source code for this tutorial: [StreamingTutorial](../../resources/keyview_filter/sdk/Java/StreamingTutorial)
- optional sample files for detection and various extraction options located [here](../../resources/keyview_filter)

### Environment and compilers

#### Compiler

To create a program that uses KeyView, you need to install a [supported compiler](https://www.microfocus.com/documentation/idol/IDOL_24.2/KeyviewFilterSDK_24.2_Documentation/Guides/html/java-programming/Content/Shared/_KV_Platform_Compilers.htm), and use it to build your program.

#### Other

Apache [Ant](https://ant.apache.org/) is used with `StreamingTutorial`.  Ant version 1.9.16 is recommended.

### License key

You need a KeyView license key to proceed with this lesson.  If you skipped the introduction setup step to acquire a license key, see [here](introduction.md#activate-a-license-key).

## API Setup

### Building the sample program

Deploy the downloaded `StreamingTutorial` build tools and source files to the location of your choice.  This tutorial uses `C:\OpenText\KeyViewFilterSDK_24.2.0\javaapi\StreamingTutorial`.

To build `StreamingTutorial` a few modifications of the provided resources are required:
1. Update build.xml, replacing the `KEYVIEW_BIN_FOLDER` placeholder with the location of your KeyView bin folder so that that path to the `javaapi\KeyView.jar` can be resolved. For example,
```xml
	<path id="classpath">
		<fileset dir="C:\OpenText\KeyViewFilterSDK_24.2.0\WINDOWS_X86_64\bin\..\..\javaapi\" includes="KeyView.jar" />
	</path>
```
2. Update the provided `build.bat` or `build.sh` to set the `JAVA_HOME` and `ANT_HOME` environment variables that match your system.
3. Update `src\Config.java`, replacing the `KEYVIEW_LICENSEKEY_STRING` with the contents of the `licensekey.dat` file and `KEYVIEW_BIN_FOLDER` with the location of your KeyView bin folder.

Go ahead and run `build.bat` or `build.sh`.
```sh
> cd C:\OpenText\KeyViewFilterSDK_24.2.0\javaapi\StreamingTutorial
> build.bat

Buildfile: C:\OpenText\KeyViewFilterSDK_24.2.0\javaapi\StreamingTutorial\build.xml

compile:
    [javac] Compiling 11 source files to C:\OpenText\KeyViewFilterSDK_24.2.0\javaapi\StreamingTutorial\build\classes

jar:
    [mkdir] Created dir: C:\OpenText\KeyViewFilterSDK_24.2.0\javaapi\StreamingTutorial\build\jar
      [jar] Building jar: C:\OpenText\KeyViewFilterSDK_24.2.0\javaapi\StreamingTutorial\build\jar\StreamingTutorial.jar

BUILD SUCCESSFUL
Total time: 1 second
```

## Process files

To run `StreamingTutorial` a few modifications of the provided resources are required:
1. Update the provided `StreamingTutorial.bat` or `StreamingTutorial.sh` to set the `JAVA_HOME` and `KEYVIEW_BIN_FOLDER` environment variables that match your system.

Go ahead and run `StreamingTutorial.bat` to see the usage instructions.
```sh
> cd C:\OpenText\KeyViewFilterSDK_24.2.0\javaapi\StreamingTutorial
> StreamingTutorial.bat
Usage: StreamingTutorial <inputFile> <outputFile>
   Demonstrates usage of the Filter SDK by:
      * Filtering all the text from inputFile to outputFile
      * Outputting all the metadata from inputFile into outputFile
      * Extracting all subfiles of inputFile and performing and repeating
        these steps for each of them.
```

Re-run `StreamingTutorial.bat` provide and input file and output file as done below.
```sh
> cd C:\OpenText\KeyViewFilterSDK_24.2.0\javaapi\StreamingTutorial
> StreamingTutorial.bat 
C:\Opentext\KeyViewFilterSDK_24.2.0\javaapi\tutorial_java>StreamingTutorial.bat ..\KeyView.jar out.txt
Processing input file ..\KeyView.jar to out.txt
Processing subfile KeyView.jar/META-INF/
Processing subfile KeyView.jar/META-INF/MANIFEST.MF
Processing subfile KeyView.jar/com/
Processing subfile KeyView.jar/com/verity/
...
Processing subfile KeyView.jar/com/verity/api/metadata/StringMetadataElement.class
Processing subfile KeyView.jar/htmlinfo.properties
Processing subfile KeyView.jar/xmlinfo.properties
```

View `out.txt` where you will see KeyView generated detection information, extracted container and sub-file metadata and the extracted text when available.

Try `StreamingTutorial` with `idol-oem-tutorials\resources\keyview_filter\KeyViewFilterSDK_12.12.0_ReleaseNotes_en.rar`, other sample documents provided with this tutorial and your own sample files.

## Conclusion

You have now used the KeyView Filter SDK API for Java to automatically detect the file format (and other key properties) and to extract metadata, text and sub-files.

And if you haven't already, why not try more tutorials to explore some of the other features available in KeyView Filter SDK, linked from the [main page](../README.md#keyview-filter-showcase).

## See also

- [KeyView Filter SDK C Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_2/KeyviewFilterSDK_24.2_Documentation/Guides/html/c-programming/index.html)
- [KeyView Filter SDK C++ Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_2/KeyviewFilterSDK_24.2_Documentation/Guides/html/cpp-programming/index.html)
- [KeyView Filter SDK Java Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_2/KeyviewFilterSDK_24.2_Documentation/Guides/html/java-programming/index.html)
- [KeyView Filter SDK .NET Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_2/KeyviewFilterSDK_24.2_Documentation/Guides/html/dotnet-programming/index.html)
- [KeyView Filter SDK Python Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_2/KeyviewFilterSDK_24.2_Documentation/Guides/html/python-programming/)
- [KeyView Release Notes](https://www.microfocus.com/documentation/idol/IDOL_24_2/IDOLReleaseNotes_24.2_Documentation/oem/Content/_KeyView.htm)