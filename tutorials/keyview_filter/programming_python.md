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

To create a program that uses the KeyView Filter SDK for Python, you need to install a supported Python 3 interpreter.  The `%KEYVIEW_HOME%\pythonapi\keyview\*.whl' has encoded in the filename the Python version number (e.g. `*-cp310-* for v3.10) supported.

### License key

You need a KeyView license key to proceed with this lesson.  If you skipped the introduction setup step to acquire a license key, see [here](introduction.md#activate-a-license-key).

> NOTE: The Python sample programs use the environment variable `KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH` to pass the `licensekey.dat` to the KeyView APIs.

## API Setup

A Jupyter Notebook `pythonapi\notebooks\getting_started.ipynb` provides getting started tips.  The most essential step to execute is `Install the keyview.filter Python Module`.  The other steps are also valuable to learn the basics of API.

## Sample program setup

Both of the sample programs provided in this tutorial's resources require you to configure some paths and set environment variable.

### Configure paths

The `keyview.FilterSession()` method requires knowledge of the KeyView bin folder (e.g. `C:\OpenText\KeyViewFilterSDK_23.3.0\WINDOWS_X86_64\bin`).  The sample programs default to the `WINDOWS_X86_64` platform, but you can easily switch the platform and paths.  The `platform` and `filterSDK_home` variables are the key ones to set appropriately for your environment.  The `exportSDK_home` is optional in that it's used as an additional source of sample input documents.

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

Reference the [Use the Filter API](https://www.microfocus.com/documentation/idol/IDOL_23_3/KeyviewFilterSDK_23.3_Documentation/Guides/html/cpp-programming/Content/Chapter_UseFilterAPI.htm) section of the KeyView Filter SDK Programming Guide.

Go ahead and run `extract_metadata_text.py`.  Don't forget to set the paths for KeyView and your input files to match your environment.
```sh
> cd C:\OpenText\KeyViewFilterSDK_23.3.0\pythonapi\my_samples
> python3 extract_metadata_text.py

Processing input document: C:\OpenText\KeyViewExportSDK_23.3.0/testdocs/freezer2.ppt

DocInfo(doc_class=<DocClass.PRESENTATION: 6>, doc_format=<DocFormat.POWERPOINT_97: 120>, version=8000, encrypted=False, mac_binary_encoded=False, apple_double_encoded=False, wang_gdl_encoded=False, window_rms_encrypted=False)

Extracting metadata to: C:\OpenText\KeyViewExportSDK_23.3.0_WINDOWS_X86_64/testdocs/freezer2.ppt_KV_METADATA.TXT
Extracting text to: C:\OpenText\KeyViewExportSDK_23.3.0_WINDOWS_X86_64/testdocs/freezer2.ppt_KV_TEXT.TXT
```

## Format detection and extracting sub-files

The sample program `extract_metadata_text.py` processes input documents and outputs the extracted sub_files to folder defined by `out_dir`.  Set this variable appropriately for your environment.  Otherwise, it will be located in `%KEYVIEW_HOME%\pythonapi\my_samples`.

Go ahead and run `extract_sub_files.py`.  Don't forget to set the paths for KeyView and your input files to match your environment.
```sh
> cd C:\OpenText\KeyViewFilterSDK_23.3.0\pythonapi\my_samples
> python3 extract_sub_files.py

Processing input document: C:\OpenText\KeyViewExportSDK_23.3.0/testdocs/SquaresTemplate.zip

DocInfo(doc_class=<DocClass.ENCAPSULATION: 8>, doc_format=<DocFormat.PKZIP: 157>, version=2000, encrypted=False, mac_binary_encoded=False, apple_double_encoded=False, wang_gdl_encoded=False, window_rms_encrypted=False) 

Found other SubFileTypes to extract. Extracting to C:\OpenText\KeyViewFilterSDK\KeyViewFilterSDK_23.3.0\pythonapi\my_samples\_extract\Container\LetterHeadTemplate.docx
Extracting Container/LetterHeadTemplate.docx
        Type: Main
        Index: 0
        Parent: -1
        Size (bytes): 24020
        Time: 2022-08-08 16:22:42+00:00
Found other SubFileTypes to extract. Extracting to C:\OpenText\KeyViewFilterSDK\KeyViewFilterSDK_23.3.0\pythonapi\my_samples\_extract\Container\PresentationTemplate.pptx
Extracting Container/PresentationTemplate.pptx
        Type: Main
        Index: 1
        Parent: -1
        Size (bytes): 60652
        Time: 2022-08-10 21:08:48+00:00
Found other SubFileTypes to extract. Extracting to C:\OpenText\KeyViewFilterSDK\KeyViewFilterSDK_23.3.0\pythonapi\my_samples\_extract\Container\Squares-Logo.png
Extracting Container/Squares-Logo.png
        Type: Main
        Index: 2
        Parent: -1
        Size (bytes): 2033
        Time: 2022-08-05 23:57:30+00:00
```

## Conclusion

You have now used the KeyView Filter SDK API for Python to automatically detect the file format (and other key properties) and to extract metadata, text and sub-files.

And if you haven't already, why not try more tutorials to explore some of the other features available in KeyView Filter SDK, linked from the [main page](../README.md#keyview-filter-showcase).

## See also

- KeyView Filter SDK [C Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_23_3/KeyviewFilterSDK_23.3_Documentation/Guides/html/c-programming/)
- KeyView Filter SDK [C++ Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_23_3/KeyviewFilterSDK_23.3_Documentation/Guides/html/cpp-programming/)
- KeyView Filter SDK [Java Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_23_3/KeyviewFilterSDK_23.3_Documentation/Guides/html/java-programming/)
- KeyView Filter SDK [.NET Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_23_3/KeyviewFilterSDK_23.3_Documentation/Guides/html/dotnet-programming/)
- [KeyView Release Notes](https://www.microfocus.com/documentation/idol/IDOL_23_3/IDOLReleaseNotes_23.3_Documentation/idol/Content/_KeyView.htm)
