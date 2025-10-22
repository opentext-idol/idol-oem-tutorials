# Optical Character Recognition (OCR)

Not all documents already contain machine usable text. These types of documents may be scans, screenshots or pictures.

When processing raster image files, the Filter SDK can perform Optical Character Recognition (OCR) to attempt to filter text that might be visible in the image. As of the 25.4.0 release, 46 languages covering Latin, Arabic, Chinese, Cyrillic and a few other alphabets.  See the [OCR Supported Languages](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/Shared/_KV_OCR_Supported_Languages.htm) appendix for more details.

In this lesson, you will:

- perform OCR on a PNG image file
- gain awareness of available OCR optimization options

> NOTE: This guide assumes you have already completed the [Filter SDK introduction](./introduction.md#introduction-to-filter-sdk) lesson.

---

- [Setup](#setup)
  - [Resources](#resources)
- [Perform OCR](#perform-ocr)
  - [Perform OCR with `filter`](#perform-ocr-with-filter)
  - [Perform OCR with `filtertest`](#perform-ocr-with-filtertest)
- [Conclusion](#conclusion)
- [See also](#see-also)
  
---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

> NOTE: This lesson assumes you have already completed the [Filter SDK introduction](../keyview_filter/introduction.md) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic Filter SDK concepts.

### Resources

Be sure to download the following resources before you continue:

- sample documents from [here](../../resources/keyview_filter/) and install to `C:\OpenText\idol-oem-tutorials\resources`

## Perform OCR

### Perform OCR with `filter`

```sh
> cd C:\OpenText\KeyviewFilterSDK_25.4.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> filter ..\..\..\idol-oem-tutorials\resources\keyview_filter\screenshot_TO_OCR.png ocr.txt
WARNING: filter is a sample program only and is not for production use
filter: ..\..\..\idol-oem-tutorials\resources\keyview_filter\screenshot_TO_OCR.png to ocr.txt
filter: error code returned is KVERR_Success
```

> NOTE: The `KVERR_Success` error code is a positive result where the destination `ocr.txt` file contains the output.  Use your UTF-8 capable text editor, so you can properly view the output - just in case complex character sets are represented in the test document.

View `ocr.txt` to see the OCR'd text output and also view `screenshot_TO_OCR.png` for reference. There may be some mistakes in the OCR'd text. OCR even for machine generated text isn't perfect.  Handwritten text has limited support and cursive text is not supported.

> NOTE: OCR is relatively CPU intensive process and takes extra time to process an image file vs doing no OCR.

Try `filter` performing OCR with your own image files.  Remember you may need to extract sub-files using `tstxtract` with `formats.ini [Options] ExtractImages=true` as discussed in the [Sub-file Extraction](./introduction.md#sub-file-extraction) lesson in the introduction.

### Perform OCR with `filtertest`

`filtertest` lets you skip OCR for supported and configure some available options with the following command line options:

```sh
     [-ocr languages orientation detectAlphabet textFindingMode] set OCR options (eg. -ocr en 1 2 3)
                languages: en (English), for a full list see KeyView documentation
                orientation: 0 (upright), 1 (any)
                detectAlphabet: 0 (off), 1 (listed), 2 (all)
                textFindingMode: 0 (document), 1 (scene), 2 (hollow), 3 (auto)
```

```sh
> cd C:\OpenText\KeyviewFilterSDK_25.4.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> filtertest -nocr ..\..\..\idol-oem-tutorials\resources\keyview_filter\screenshot_TO_OCR.png ocr.txt
WARNING: filtertest is a sample program only and is not for production use
filtertest: ..\..\..\idol-oem-tutorials\resources\keyview_filter\screenshot_TO_OCR.png to ocr.txt
filtertest: Target CharSet is 53
Return code is 0
filtertest finished with RC: 0
```

> NOTE: `RC: 0` is a positive result equivalent to `KVERR_Success` where the destination `ocr.txt` file contains the output. Use your UTF-8 capable text editor, so you can properly view the output - just in case complex character sets are represented in the test document.

The `ocr.txt` output file will contain no text since the `-nocr` flag was added.

Read up on the `languages orientation detectAlphabet` tuning options in the [Optical Character Recognition](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/filter/Optical_Character_Recognition.htm) section of the programming guide.

## Conclusion

With the Filter SDK supporting the OCR of images, more content is available for downstream processing.

Next, why not try more tutorials to explore some of the other features available in Filter SDK, linked from [here](../keyview_filter/README.md#capability-showcase).

## See also

- [Filter SDK C Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/index.html)
- [Filter SDK C++ Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/cpp-programming/index.html)
- [Filter SDK Java Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/java-programming/index.html)
- [Filter SDK .NET Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/dotnet-programming/index.html)
- [Filter SDK Python Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/python-programming/)
- [File Content Extraction Release Notes](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/IDOLReleaseNotes_25.4_Documentation/oem/Content/_KeyView.htm)
