# KeyView Filter SDK Python API

The KeyView Filter SDK allows you to embed KeyView functionality into other services.

To facilitate embedding, the KeyView Filter SDK has APIs for C, C++, Java, .NET and Python.  In addition, the KeyView Filter SDK runs natively on the following platforms: Windows (x86_32, x86_64, ARM_64), Linux (x86_32, x86_64 and ARM_64), MacOS (x86_64 and Apple M*). 

In this lesson, you will:

- Familiarize yourself with the Filter SDK's Python API
- Create a sample program that replicates a common use case of the Filter SDK

> NOTE: This guide assumes you have already completed the introductory KeyView Filter SDK [tutorial](introduction.md#keyview-filter-sdk-introduction).

---

- [Setup](#setup)
  - [Resources](#resources)
  - [Environment and interpreters](#environment-and-interpreters)
    - [Interpreters](#interpreters)
  - [License key](#license-key)
- [API Setup](#api-setup)
- [Sample program setup](#sample-program-setup)
  - [Configure paths](#configure-paths)
  - [Set environment variable](#set-environment-variable)
- [Format detection and extracting metadata / text](#format-detection-and-extracting-metadata--text)
- [Format detection and extracting sub-files](#format-detection-and-extracting-sub-files)
- [Conclusion](#conclusion)
- [See also](#see-also)

---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

> NOTE: This lesson assumes you have already completed the [KeyView Filter SDK introduction](introduction.md#keyview-filter-sdk-introduction) lesson covering essential setup steps (for example, required downloads and installation steps) and basic KeyView Filter concepts.

### Resources

You must download the following resources before you continue:
- source code for this tutorial:
  -  [extract_metadata_text.py](../../resources/keyview_filter/sdk/Python/extract_metadata_text.py)
  -  [extract_sub_files.py](../../resources/keyview_filter/sdk/Python/extract_sub_files.py)

> NOTE: Deploy these resources to the `%KEYVIEW_HOME%/pythonapi/my_samples` folder.
 
### Environment and interpreters

#### Interpreters

To create a program that uses the KeyView Filter SDK for Python, you need to install a supported Python 3 interpreter.  The `%KEYVIEW_HOME%\pythonapi\keyview\*.whl' has encoded in the filename the Python version number (e.g. `*-cp310-* for v3.10) supported.  Reference the documentation section [Install the KeyView Filter Python Module](https://www.microfocus.com/documentation/idol/IDOL_24_2/KeyviewFilterSDK_24.2_Documentation/Guides/html/python-programming/Content/Python/InstallModule.htm) for installation tips.

### License key

You need a KeyView license key to proceed with this lesson.  If you skipped the introduction setup step to acquire a license key, see [here](introduction.md#activate-a-license-key).

> NOTE: The Python sample programs use the environment variable `KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH` to pass the `licensekey.dat` to the KeyView APIs.

## API Setup

A Jupyter Notebook `pythonapi\notebooks\getting_started.ipynb` provides getting started tips.  The most essential step to execute is `Install the keyview.filter Python Module`.  The other steps are also valuable to learn the basics of API.

## Sample program setup

Both of the sample programs provided in this tutorial's resources require you to configure some paths and set environment variable.

### Configure paths

The `keyview.FilterSession()` method requires knowledge of the KeyView bin folder (e.g. `C:\OpenText\KeyViewFilterSDK_24.2.0\WINDOWS_X86_64\bin`).  The sample programs default to the `WINDOWS_X86_64` platform, but you can easily switch the platform and paths.  The `platform` and `filterSDK_home` variables are the key ones to set appropriately for your environment.  The `exportSDK_home` is optional in that it's used as an additional source of sample input documents.

Be sure to also set `input_filepath` variable to your test document(s).

### Set environment variable

As in the pre-built sample programs (`filter` and `tstxtract`), the sample programs use `KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH` to pass the KeyView license key (`licensekey.dat`) to `keyview.FilterSession().  Set this variable appropriately for your environment and platform such that it's available to your Python interpreter.

```sh
set KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH=C:\OpenText\licensekey.dat
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
                "KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH": "C:\\OpenText\\licensekey.dat"
            }
        }
        ]
    }
```

## Format detection and extracting metadata / text

The sample program `extract_metadata_text.py` processes input documents and outputs a `*_KV_METADATA.TXT` and `*_KV_TEXT.TXT`. 

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

Reference the [Use the Filter API](https://www.microfocus.com/documentation/idol/IDOL_24_2/KeyviewFilterSDK_24.2_Documentation/Guides/html/cpp-programming/Content/Chapter_UseFilterAPI.htm) section of the KeyView Filter SDK Programming Guide.

Go ahead and run `extract_metadata_text.py`.  Don't forget to set the paths for KeyView and your input files to match your environment.
```sh
> cd C:\OpenText\KeyViewFilterSDK_24.2.0\pythonapi\my_samples
> python extract_metadata_text.py

Processing input document: ../../../idol-oem-tutorials/resources/keyview_filter/2022_calendar_HIDDEN_TEXT.docx

DocInfo(doc_class=<DocClass.adWORDPROCESSOR: 1>, doc_format=<DocFormat.MS_Word_2007_Fmt: 360>, version=16000, encrypted=False, mac_binary_encoded=False, apple_double_encoded=False, wang_gdl_encoded=False, window_rms_encrypted=False)

Extracting metadata to: ../../../idol-oem-tutorials/resources/keyview_filter/2022_calendar_HIDDEN_TEXT.docx_KV_METADATA.TXT
Extracting text to: ../../../idol-oem-tutorials/resources/keyview_filter/2022_calendar_HIDDEN_TEXT.docx_KV_TEXT.TXT
```

## Format detection and extracting sub-files

The sample program `extract_metadata_text.py` processes input documents and outputs the extracted sub_files to folder defined by `out_dir`.  Set this variable appropriately for your environment.  Otherwise, it will be located in `%KEYVIEW_HOME%\pythonapi\my_samples`.

Go ahead and run `extract_sub_files.py`.  Don't forget to set the paths for KeyView and your input files to match your environment.
```sh
> cd C:\OpenText\KeyViewFilterSDK_24.2.0\pythonapi\my_samples
> python extract_sub_files.py

Processing /data//OpenText/KeyviewFilterSDK_24.2.0_LINUX_X86_64/javaapi/KeyView.jar

DocInfo(doc_class=<DocClass.adENCAPSULATION: 8>, doc_format=<DocFormat.Executable_JAR_Fmt: 999>, version=0, encrypted=False, mac_binary_encoded=False, apple_double_
encoded=False, wang_gdl_encoded=False, window_rms_encrypted=False)

Found a folder: META-INF/
        Index: 0
        Children: [1]
Found other SubFileTypes to extract. Extracting to /data/OpenText/KeyviewFilterSDK_24.2.0_LINUX_X86_64/pythonapi/my_samples/_extract/META-INF/MANIFEST.MF

Extracting META-INF/MANIFEST.MF
        Type: Main
        Index: 1
        Parent: 0
        Size (bytes): 101
        Time: 2023-09-07 12:40:36+00:00
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
        Children: [20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 5
6, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78]
Found a folder: com/verity/api/filter/
        Index: 6
        Children: [79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103]
Found a folder: com/verity/api/internal/
        Index: 7
        Children: [104, 105, 106]
Found a folder: com/verity/api/metadata/
        Index: 8
        Children: [107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119]
Found other SubFileTypes to extract. Extracting to /data/OpenText/KeyviewFilterSDK_24.2.0_LINUX_X86_64/pythonapi/my_samples/_extract/com/verity/api/Charset.class

Extracting com/verity/api/Charset.class
        Type: Main
        Index: 9
        Parent: 4
        Size (bytes): 7208
        Time: 2023-09-07 12:40:36+00:00
Found other SubFileTypes to extract. Extracting to /data/OpenText/KeyviewFilterSDK_24.2.0_LINUX_X86_64/pythonapi/my_samples/_extract/com/verity/api/DocClass.class
```

There are two additional resources available that can perform the same types of detection, text, metadata and sub-file extractions: `extract_metadata_text_folder.py` and `extract_sub_files_folder.py`.

## Conclusion

You have now used the KeyView Filter SDK API for Python to automatically detect the file format (and other key properties) and to extract metadata, text and sub-files.

Next, why not try more tutorials to explore some of the other features available in Filter SDK, linked from [here](../keyview_filter/README.md#capability-showcase).

## See also

- [KeyView Filter SDK C Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_2/KeyviewFilterSDK_24.2_Documentation/Guides/html/c-programming/index.html)
- [KeyView Filter SDK C++ Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_2/KeyviewFilterSDK_24.2_Documentation/Guides/html/cpp-programming/index.html)
- [KeyView Filter SDK Java Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_2/KeyviewFilterSDK_24.2_Documentation/Guides/html/java-programming/index.html)
- [KeyView Filter SDK .NET Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_2/KeyviewFilterSDK_24.2_Documentation/Guides/html/dotnet-programming/index.html)
- [KeyView Filter SDK Python Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_2/KeyviewFilterSDK_24.2_Documentation/Guides/html/python-programming/)
- [KeyView Release Notes](https://www.microfocus.com/documentation/idol/IDOL_24_2/IDOLReleaseNotes_24.2_Documentation/oem/Content/_KeyView.htm)

