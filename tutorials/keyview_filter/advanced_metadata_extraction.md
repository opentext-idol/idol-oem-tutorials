# Advanced Metadata Extraction

As we saw in the introduction lesson for KeyView Filter SDK, files often contain metadata.  In practice there are varying flavors of metadata.

In this lesson, you will explore:
- XMP metadata extraction
- identification of document restrictions

> NOTE: This guide assumes you have already completed the introductory KeyView Filter [tutorial](./introduction.md#keyview-filter-sdk-introduction).

---

- [Setup](#setup)
  - [Resources](#resources)
- [XMP Metadata](#xmp-metadata)
  - [Perform XMP metadata extraction](#perform-xmp-metadata-extraction)
- [Document Restrictions](#document-restrictions)
  - [Identify Document Restrictions](#identify-document-restrictions)
- [Conclusion](#conclusion)
- [See also](#see-also)

---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

> NOTE: This lesson assumes you have already completed the [KeyView Filter SDK introduction](./introduction.md#keyview-filter-sdk-introduction) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic Filter SDK concepts.

### Resources

Be sure to download the following resources before you continue:
- sample documents from [here](../../resources/keyview_filter/) and install to `C:\OpenText\idol-oem-tutorials\resources`

> NOTE: This lesson assumes you have already completed the [KeyView Filter SDK introduction](../keyview_filter/introduction.md#keyview-sdk-introduction) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic KeyView Filter SDK concepts.

## XMP Metadata

XMP stands for [Extensible Metadata Platform](https://en.wikipedia.org/wiki/Extensible_Metadata_Platform). PDF, image, audio and video files are the typical format categories that may contain XMP metadata.

Refer to the [Keyview Filter SDK Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_2/KeyviewFilterSDK_24.2_Documentation/Guides/html/c-programming/Content/C/filtering_functions/fpGetMetadataList.htm) for more details about KeyView's support for XMP metadata.

### Perform XMP metadata extraction

```sh
> cd KeyviewFilterSDK_24.2.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> filter -m "..\..\..\idol-oem-tutorials\resources\keyview_filter\screenshot_HAS_XMP.png" xmp
WARNING: filter is a sample program only and is not for production use
filter: ..\..\..\idol-oem-tutorials\resources\keyview_filter\screenshot_HAS_XMP.png to xmp
filter: error code returned is KVERR_Success
```

> NOTE: The `KVERR_Success` error code is a positive result where the destination `xmp` file contains the output. Use your UTF-8 capable text editor, so you can properly view the output - just in case complex character sets are represented in the test document.

`filter -m` extracts standard, custom and XMP metadata.

Try `filter -m` with your own test files. Good luck!

## Document Restrictions

Some applications, and corresponding file formats, allow users to restrict the ways in which a document can be used. For example, you might be able to read a document but additional credentials (such as a password) could be required to modify the document content, add comments, or print the document. 

### Identify Document Restrictions

The document `Robin Zupanc Resume_RESTRICTED.docx` included in this tutorial's resources was created using this [Microsoft.com knowledge article](https://support.microsoft.com/en-us/office/make-a-document-read-only-5c25909c-46d9-4eb0-9d1f-d072a560e340) as guidance. 

Reference the Keyview documentation on [Document Restrictions](https://www.microfocus.com/documentation/idol/IDOL_24_2/KeyviewFilterSDK_24.2_Documentation/Guides/html/c-programming/Content/filter_shared/DocumentRestrictions.htm) for more details like supported formats.

The `filtertest` utility will be used for this lesson.  `filtertest` works similarly to `filter` with a few additional options.

```sh
> cd C:\OpenText\KeyviewFilterSDK_24.2.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> filtertest -restrictions "..\..\..\idol-oem-tutorials\resources\keyview_filter\Robin Zupanc Resume_RESTRICTED.docx" restrictions
WARNING: filtertest is a sample program only and is not for production use
filtertest finished with RC: 0
```

> NOTE: `RC: 0` is a positive result equivalent to `KVERR_Success` where the destination `restrictions` file contains the output. Use your UTF-8 capable text editor, so you can properly view the output - just in case complex character sets are represented in the test document.

```sh
> type restrictions
Write restriction: true
```

Try the `filtertest -restrictions` with other tutorial resource PPT, DOCX, XLSX, PDF files and your own with/without write restrictions.

## Conclusion

There are multiple types of metadata that a given file format may contain. KeyView Filter SDK strives to extract as much information as is possible from file formats.

Next, why not try more tutorials to explore some of the other features available in Filter SDK, linked from [here](../keyview_filter/README.md#capability-showcase).

## See also

- [KeyView Filter SDK C Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_2/KeyviewFilterSDK_24.2_Documentation/Guides/html/c-programming/index.html)
- [KeyView Filter SDK C++ Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_2/KeyviewFilterSDK_24.2_Documentation/Guides/html/cpp-programming/index.html)
- [KeyView Filter SDK Java Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_2/KeyviewFilterSDK_24.2_Documentation/Guides/html/java-programming/index.html)
- [KeyView Filter SDK .NET Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_2/KeyviewFilterSDK_24.2_Documentation/Guides/html/dotnet-programming/index.html)
- [KeyView Filter SDK Python Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_2/KeyviewFilterSDK_24.2_Documentation/Guides/html/python-programming/)
- [KeyView Release Notes](https://www.microfocus.com/documentation/idol/IDOL_24_2/IDOLReleaseNotes_24.2_Documentation/oem/Content/_KeyView.htm)
