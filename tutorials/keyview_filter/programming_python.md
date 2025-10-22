# Filter SDK Python API

The Filter SDK allows you to embed file content extraction functionality into other services.

To facilitate embedding, the Filter SDK has APIs for C, C++, Java, .NET and Python.  In addition, the Filter SDK runs natively on the following platforms: Windows (x86_32, x86_64, ARM_64), Linux (x86_32, x86_64 and ARM_64), MacOS (x86_64 and Apple M*).

In this lesson, you will:

- Familiarize yourself with the Filter SDK's Python API
- Create a sample program that replicates a common use case of the Filter SDK

> NOTE: This guide assumes you have already completed the [Filter SDK introduction](./introduction.md#introduction-to-filter-sdk) lesson.

---

- [Setup](#setup)
  - [Resources](#resources)
  - [Environment and interpreters](#environment-and-interpreters)
    - [Interpreters](#interpreters)
  - [License key](#license-key)
- [API Setup](#api-setup)
- [Sample program use](#sample-program-use)
  - [Set environment variable](#set-environment-variable)
- [Format detection and extracting metadata / text](#format-detection-and-extracting-metadata--text)
- [Format detection and extracting sub-files](#format-detection-and-extracting-sub-files)
- [Conclusion](#conclusion)
- [See also](#see-also)

---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

> NOTE: This lesson assumes you have already completed the [Filter SDK introduction](./introduction.md#introduction-to-filter-sdk) lesson covering essential setup steps (for example, required downloads and installation steps) and basic Filter concepts.

### Resources

You must download the following resources before you continue:

- source code for this tutorial:
  - [extract_metadata_text.py](../../resources/keyview_filter/sdk/Python/extract_metadata_text.py)
  - [extract_sub_files.py](../../resources/keyview_filter/sdk/Python/extract_sub_files.py)
  - [helper batch files](../../resources/keyview_filter/sdk/Python/

### Environment and interpreters

#### Interpreters

To create a program that uses the Filter SDK for Python, you need to install a supported Python 3 interpreter.  The `%KEYVIEW_HOME%\pythonapi\keyview\*.whl` has encoded in the filename the Python version number (*e.g.* `*-cp310-*` for v3.10) supported.  Reference the documentation section [Install the Filter Python Module](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/python-programming/Content/Python/InstallModule.htm) for installation tips.

### License key

You need a Filter SDK license key to proceed with this lesson.  If you skipped the introduction setup step to acquire a license key, see [here](./introduction.md#activate-a-license-key).

> NOTE: The Python sample programs use the environment variable `KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH` to pass the `licensekey.dat` to the Filter SDK APIs.  The `run_extract_*.*` scripts set `KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH` and assume you deploy the `licensekey.dat` to `%KEYVIEW_HOME%`.

## API Setup

A Jupyter Notebook `pythonapi\notebooks\getting_started.ipynb` provides getting started tips.  The most essential step to execute is `Install the keyview.filter Python Module`.  The other steps are also valuable to learn the basics of API.

## Sample program use

The sample programs provided in this tutorial's resources require you to set environment variable and pass in the proper arguments for inputs, outputs and such.

```sh
> cd C:\OpenText\idol-oem-tutorials\resources\keyview_filter\sdk\Python
> python extract_metadata_text.py
usage: extract_metadata_text.py [-h] filterSDK_bin input_filepath metadata_output_filepath text_output_filepath
extract_metadata_text.py: error: the following arguments are required: filterSDK_bin, input_filepath, metadata_output_filepath, text_output_filepath
```

### Set environment variable

As in the pre-built sample programs (`filter` and `tstxtract`), the sample programs use `KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH` to pass the Filter SDK license key (`licensekey.dat`) to `keyview.FilterSession().  Set this variable appropriately for your environment and platform such that it's available to your Python interpreter.

> NOTE: The `run_extract_*.bat` (and `run_extract_*.sh`) scripts set `KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH` and assume you deploy the `licensekey.dat` to `%KEYVIEW_HOME%`.

```sh
set KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH=C:\OpenText\KeyviewFilterSDK_25.4.0_WINDOWS_X86_64\licensekey.dat
```

In VS Code, you can the augment your run configuration as illustrated below:

 ```json
    ....
    "launch": {
        "configurations": [
        {
            "name": "run-app",
            "type": "python",
            "request": "launch",
            "program": "${file}",
            "env": {
                "KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH": "C:\\OpenText\\KeyViewFilterSDK_25.4.0_WINDOWS_X86_64\\licensekey.dat"
            }
        }
        ]
    }
```

## Format detection and extracting metadata / text

The sample program `extract_metadata_text.py` processes an input document and outputs a `*_KV_METADATA.TXT` and `*_KV_TEXT.TXT`.

This sample program uses session.config.*() to enable engine settings that are dynamically controlled like `session.config.ocr(true)`.  There are additional engine level settings that are controlled via `<PLATFORM>\bin\formats.ini` file.  Below are some recommended changes to make that impact the `*_KV_TEXT.TXT` output:

```diff
[Options]
SanitizeAbsoluteExtractPaths=False

+GetHTMLHiddenInfo=1

+getsheetnames=1
+gethiddeninfo=1
+TabDelimited=TRUE
+OutputTableDelimiters=TRUE

+LogicalOrder=1
```

Reference the [Use the Filter API](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/cpp-programming/Content/Chapter_UseFilterAPI.htm) section of the Filter SDK Programming Guide.

Go ahead and run `extract_metadata_text.py`.  Don't forget to set the paths for the Filter SDK and your input files to match your environment.

```sh
> cd C:\OpenText\idol-oem-tutorials\resources\keyview_filter\sdk\Python
> run_extract_metadata_text.bat
...
Using the license key: C:\OpenText\KeyviewFilterSDK_25.4.0_WINDOWS_X86_64\licensekey.dat
Processing input document: ../../../idol-oem-tutorials/resources/keyview_filter/2022_calendar_HIDDEN_TEXT.docx

DocInfo(doc_class=<DocClass.adWORDPROCESSOR: 1>, doc_format=<DocFormat.MS_Word_2007_Fmt: 360>, version=16000, encrypted=False, mac_binary_encoded=False, apple_double_encoded=False, wang_gdl_encoded=False, window_rms_encrypted=False)

Extracting metadata to: ../../../idol-oem-tutorials/resources/keyview_filter/2022_calendar_HIDDEN_TEXT.docx_KV_METADATA.TXT
Extracting text to: ../../../idol-oem-tutorials/resources/keyview_filter/2022_calendar_HIDDEN_TEXT.docx_KV_TEXT.TXT
```

## Format detection and extracting sub-files

The sample program `extract_metadata_text.py` processes an input document and outputs the extracted sub_files to folder defined by `out_dir`.  Set this variable appropriately for your environment.  Otherwise, it will be located in `%KEYVIEW_HOME%\pythonapi\my_samples`.

Go ahead and run `extract_sub_files.py`.  Don't forget to set the paths for the Filter SDK and your input files to match your environment.

```sh
> cd C:\OpenText\idol-oem-tutorials\resources\keyview_filter\sdk\Python
> run_extract_sub_files.bat
...
Using the license key: C:\OpenText\KeyviewFilterSDK_25.4.0\licensekey.dat
---------------
```

A file called `extract_sub_files.LOG` will be generated containing output as below:

```txt
Processing the file: C:\OpenText\KeyviewFilterSDK_25.4.0_WINDOWS_X86_64\javaapi\KeyView.jar
DocInfo(doc_class=<DocClass.adENCAPSULATION: 8>, doc_format=<DocFormat.Executable_JAR_Fmt: 999>, version=0, encrypted=False, mac_binary_encoded=False, apple_double_encoded=False, wang_gdl_encoded=False, window_rms_encrypted=False)
Found a folder: META-INF/
 Index: 0
 Children: [1]

Found other SubFileTypes to extract.
Extracting META-INF/MANIFEST.MF
to C:\OpenText\idol-oem-tutorials\_WORK\output\META-INF\MANIFEST.MF
	Type: Main
	Index: 1
	Parent: 0
	Size (bytes): 104
	Time: 2024-03-19 15:38:00+00:00
---------------

Processing the file: C:\OpenText\idol-oem-tutorials\_WORK\output\META-INF\MANIFEST.MF
DocInfo(doc_class=<DocClass.adWORDPROCESSOR: 1>, doc_format=<DocFormat.ASCII_Text_Fmt: 2>, version=0, encrypted=False, mac_binary_encoded=False, apple_double_encoded=False, wang_gdl_encoded=False, window_rms_encrypted=False)
Found a folder: com/
 Index: 2
 Children: [3]
Found a folder: com/verity/
 Index: 3
 Children: [4]
Found a folder: com/verity/api/
 Index: 4
 Children: [5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]
Found a folder: com/verity/api/export/
 Index: 5
 Children: [20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78]
Found a folder: com/verity/api/filter/
 Index: 6
 Children: [79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103]
Found a folder: com/verity/api/internal/
 Index: 7
 Children: [104, 105, 106]
Found a folder: com/verity/api/metadata/
 Index: 8
 Children: [107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119]

Found other SubFileTypes to extract.
Extracting com/verity/api/Charset.class
to C:\OpenText\idol-oem-tutorials\_WORK\output\com\verity\api\Charset.class
	Type: Main
	Index: 9
	Parent: 4
	Size (bytes): 7208
	Time: 2024-03-19 15:38:02+00:00
---------------
...
```

There is an additional resource available that can perform the same types of detection, text, and metadata extractions: `extract_metadata_text_folder.py`.

## Conclusion

You have now used the Filter SDK API for Python to automatically detect the file format (and other key properties) and to extract metadata, text and sub-files.

Next, why not try more tutorials to explore some of the other features available in Filter SDK, linked from [here](../keyview_filter/README.md#capability-showcase).

## See also

- [Filter SDK C Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/index.html)
- [Filter SDK C++ Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/cpp-programming/index.html)
- [Filter SDK Java Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/java-programming/index.html)
- [Filter SDK .NET Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/dotnet-programming/index.html)
- [Filter SDK Python Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/python-programming/)
- [File Content Extraction Release Notes](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/IDOLReleaseNotes_25.4_Documentation/oem/Content/_KeyView.htm)
