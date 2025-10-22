# Testing API Error Handling

The OpenText File Content Extraction (formerly known as KeyView) Filter SDK APIs can return error exceptions under various circumstances like when trying to extract the contents of a password  protected file or when a timeout occurs.  An application's code will catch these exceptions and have differing code paths for the handling of these exceptions.  The properly test the application code paths one has to provide input documents that trigger these various exceptions or have a way to do so artificially.  In the 25.4 release a special reader `poisonsr` was introduced to faciltate this.

Refer to the documentation section [Test Error Handling and Recovery](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/filter/Testing_poisonsr.htm) on this topic for more details.

In this lesson, you will:

- learn how to configure `poisonsr`
- trigger various exception conditions

> NOTE: This guide assumes you have already completed the [Filter SDK introduction](./introduction.md#introduction-to-filter-sdk) lesson.

---

- [Setup](#setup)
  - [Resources](#resources)
  - [Configure `poisonsr`](#configure-poisonsr)
- [Use `poisonsr`](#use-poisonsr)
  - [Trigger specific Filter SDK exception](#trigger-specific-filter-sdk-exception)
  - [Trigger text extraction timeout](#trigger-text-extraction-timeout)
  - [Trigger sub-file extraction timeout](#trigger-sub-file-extraction-timeout)
  - [Trigger format detection crash](#trigger-format-detection-crash)
- [Conclusion](#conclusion)
- [See also](#see-also)

---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

> NOTE: This lesson assumes you have already completed the [Filter SDK introduction](../keyview_filter/introduction.md) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic Filter SDK concepts.

### Resources

Be sure to download the following resources before you continue:

- [poisonsr command files](../../resources/keyview_filter/poisonsr/README.md)

### Configure `poisonsr`

By default the `poisonsr` is not enabled. It's purpose is for testing and is never intended to be used in production deployments.

Refer to the [Setup](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/filter/Testing_poisonsr.htm#Setup-) instructions in the Filter SDK Programming Guide to enable the `poisonsr`.

To verify that you properly configured the `poisonsr` run the following:

```sh
> cd C:\OpenText\KeyviewFilterSDK_25.4.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> filtertest -ah  ..\..\..\idol-oem-tutorials\resources\keyview_filter\poisonsr\timeout_filter.txt out
WARNING: filtertest is a sample program only and is not for production use
autodetect: ..\..\..\..\idol-oem-tutorials\resources\keyview_filter\poisonsr\timeout_filter.txt to out
Return code is 0
filtertest finished with RC: 0

> type out
File Class:             1
Format Name (Number):   -100
Version:                0
Attributes:             0
Description:            OpenText File Content Extraction testing format for use with poisonsr
MIME Type:              -
```

The special format number `KeyView_Poison_Fmt (-100)` is returned if `poisonsr` is properly configured.  Otherwise, `ASCII_Text_Fmt (2)` will be returned since the `timeout_filter.txt` is a text file.

## Use `poisonsr`

Various document processing error scenarios that can be explicitly triggered for testing purposes will be explored in this lesson.

Refer to Filter SDK documentation section on [KVErrorCode](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/C/enum/KVErrorCode.htm) for the list of possible error codes that may be returned.

### Trigger specific Filter SDK exception

It is possible that a malformed file can be encountered by an application using Filter SDK.  Finding and/or producing a malformed test can be challenging. To facilitate testing your application's handling of this condition, `poisonsr` can be used to force this scenario to occur.

> NOTE: It is assumed that you've already followed the [Setup](#setup) instructions referenced in this tutorial.

Run `filtertest.exe` with the `throw_KVError_filter.txt` poisonsr command file.

```sh
> cd C:\OpenText\KeyviewFilterSDK_25.4.0_WINDOWS_X86_64\WINDOWS_X86_64\bin 
> filtertest ..\..\..\idol-oem-tutorials\resources\keyview_filter\poisonsr\throw_KVError_filter.txt out
WARNING: filtertest is a sample program only and is not for production use
filtertest: ..\..\..\..\idol-oem-tutorials\resources\keyview_filter\poisonsr\throw_KVError_filter.txt to out
fpFilterToFile error: ..\..\..\..\idol-oem-tutorials\resources\keyview_filter\poisonsr\throw_KVError_filter.txt
filtertest: Target CharSet is 53
Return code is 4
filtertest finished with RC: 4
```

As expected a KVError_BadInputStream (4) is returned per the command in `throw_KVError_filter.txt`.

### Trigger text extraction timeout

A timeout during processing of a large / complicated file will be encountered by applications using Filter SDK. To facilitate testing your application's handling of this condition, `poisonsr` can be used to force this scenario to occur.

> NOTE: It is assumed that you've already followed the [Setup](#setup) instructions referenced in this tutorial.

Run `filtertest.exe` with a timeout of 5 seconds using the `timeout_filter.txt` poisonsr command file configured to sleep for 10000 milliseconds.

```sh
> cd C:\OpenText\KeyviewFilterSDK_25.4.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> filtertest -to 5 ..\..\..\idol-oem-tutorials\resources\keyview_filter\poisonsr\timeout_filter.txt out
WARNING: filtertest is a sample program only and is not for production use
filtertest: ..\..\..\idol-oem-tutorials\resources\keyview_filter\poisonsr\timeout_filter.txt to out
fpFilterToFile() error: ..\..\..\..\idol-oem-tutorials\resources\keyview_filter\poisonsr\timeout_filter.txt
filtertest: Target CharSet is 53
Return code is 19
filtertest finished with RC: 19
```

As expected a KVError_ChildTimeOut (19) is returned per the command in `timeout_filter.txt`.  The child in this case is the Filter SDK out-of-process (OOP) handler.

Try running `filtertest.exe` again with 15 second timeout where you will get a KVError_Success.

> NOTE: The `out` file in is NOT intended to have any contents when using the `poisonsr`.

### Trigger sub-file extraction timeout

A timeout during the sub-file extraction of a large / complicated file will be encountered by applications using Filter SDK. To facilitate testing your application's handling of this condition, `poisonsr` can be used to force this scenario to occur.

> NOTE: It is assumed that you've already followed the [Setup](#setup) instructions referenced in this tutorial.

Run `tstxtract.exe` with a timeout of 5 seconds using the `timeout_extractSubFile.txt` poisonsr command file configured to sleep for 10000 milliseconds.

```sh
> cd C:\OpenText\KeyviewFilterSDK_25.4.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> mkdir _extract
> tstxtract -to 5 ..\..\..\idol-oem-tutorials\resources\keyview_filter\poisonsr\timeout_extractSubFile.txt _extract
WARNING: tstxtract is a sample program only and is not for production use
File ..\..\..\..\idol-oem-tutorials\resources\keyview_filter\poisonsr\timeout_extractSubFile.txt has 1 sub files, charset: 0, format: -100
Extracting #0 subfile subfile_kv0.tmp failed, error code:19
tstxtract return code: 19
```

As expected the KVError_ChildTimeOut (19) is returned.  The child in this case is the Filter SDK out-of-process (OOP) handler.

Try running `tstxtract.exe` again with 15 second timeout where you will get a KVError_Success (0).

> NOTE: The `_extract` directory is NOT intended to have any contents when using the `poisonsr`.

### Trigger format detection crash

While coding techniques are taken to avoid crashes, like with any software, it is possible for a document to cause a crash. To facilitate testing your application's handling of this condition, `poisonsr` can be used to force this scenario to occur.

> NOTE: It is assumed that you've already followed the [Setup](#setup) instructions referenced in this tutorial.

Run `filtertest.exe` with the `crash_autodet.txt` poisonsr command file.

```sh
> cd C:\OpenText\KeyviewFilterSDK_25.4.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> filtertest -ah ..\..\..\idol-oem-tutorials\resources\keyview_filter\poisonsr\crash_autodet.txt out
WARNING: filtertest is a sample program only and is not for production use
autodetect: ..\..\..\..\idol-oem-tutorials\resources\keyview_filter\poisonsr\crash_autodet.txt to out
AtoDetectInfo: error code returned is 63
Return code is 63
filtertest finished with RC: 63
```

As expected the KVError_OopCrashed (63) is returned.

Refer to the related documentation topic [Troubleshooting with Out-of-Process Dump Files](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/filter/Out_of_Process_Dump_Files.htm) where on Linux platforms the Filter SDK child process can produce a special dump file that can aid in troubleshooting.

## Conclusion

You are now familiar with the `poisonsr` that you can use to support your development and quality assurance processes.

> NOTE: Remember to not distribute the `poisonsr.dll` and to remove `formats.ini` change that enables it.

Next, why not try more tutorials to explore some of the other features available in Filter SDK, linked from [here](../keyview_filter/README.md#capability-showcase).

## See also

- [Filter SDK C Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/index.html)
- [Filter SDK C++ Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/cpp-programming/index.html)
- [Filter SDK Java Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/java-programming/index.html)
- [Filter SDK .NET Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/dotnet-programming/index.html)
- [Filter SDK Python Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/python-programming/)
- [File Content Extraction Release Notes](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/IDOLReleaseNotes_25.4_Documentation/oem/Content/_KeyView.htm)
