# Advanced Text Extraction

As we saw in the introduction lesson for KeyView Filter SDK, files different flavors of text that is visible and hidden.

In this lesson, you will explore:
- extraction of headers and footers
- extraction of some flavors of hidden text

> NOTE: This guide assumes you have already completed the introductory KeyView Filter [tutorial](./introduction.md#keyview-filter-sdk-introduction).

---

- [Setup](#setup)
  - [Resources](#resources)
- [Headers / Footers](#headers--footers)
  - [Perform header / footer extraction](#perform-header--footer-extraction)
- [Hidden Text](#hidden-text)
  - [Perform extraction with revision marks](#perform-extraction-with-revision-marks)
  - [Perform extraction excluding comments](#perform-extraction-excluding-comments)
  - [Perform extraction of slide master](#perform-extraction-of-slide-master)
- [Conclusion](#conclusion)
- [See also](#see-also)
  
---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

> NOTE: This lesson assumes you have already completed the [KeyView Filter SDK introduction](./introduction.md#keyview-filter-sdk-introduction) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic Filter SDK concepts.

### Resources

Be sure to download the following resources before you continue:
- sample documents from [here](../../resources/keyview_filter/) and install to `C:\MicroFocus\idol-oem-tutorials\resources`

> NOTE: This lesson assumes you have already completed the [KeyView Filter SDK introduction](../keyview_filter/introduction.md#keyview-sdk-introduction) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic KeyView Filter SDK concepts.

## Headers / Footers

Word processing, spreadsheet, presentation and some other file formats optionally allow for headers / footers to be inserted.  

### Perform header / footer extraction

Let's run text extraction on the same file `2022_calendar_HIDDEN_TEXT.docx` without and with header/footer mode enabled.

```sh
> cd C:\MicroFocus\KeyviewFilterSDK_12.12.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> filter ..\..\..\idol-oem-tutorials\resources\keyview_filter\2022_calendar_HIDDEN_TEXT.docx text_no_hf.txt
filter: ..\..\..\idol-oem-tutorials\resources\keyview_filter\2022_calendar_HIDDEN_TEXT.docx to text_no_hf.txt
filter: error code returned is KVERR_Success

> filter -h ..\..\..\idol-oem-tutorials\resources\keyview_filter\2022_calendar_HIDDEN_TEXT.docx text_hf.txt
filter: ..\..\..\idol-oem-tutorials\resources\keyview_filter\2022_calendar_HIDDEN_TEXT.docx to text_hf.txt
filter: error code returned is KVERR_Success
```

> NOTE: The `KVERR_Success` error code is a positive result where the destination `hidden_text` file contains the output.  Use your UTF-8 capable text editor, so you can properly view the output - just in case complex character sets are represented in the test document.

The header '2022 CALENDAR' and footer 'Page` are now extracted.  Even though there are multiple pages in this document, a single instance of the header / footer is output since only a single header / footer format is defined in the document.

Try `filter` to extract headers/footers with your own test files. Good luck!

## Hidden Text

Hidden text may be in the form of comments, revision history, slide master content and more. Many word processing, spreadsheet and presentation file formats contain this type of data.

### Perform extraction with revision marks

Word processing and some other file formats allow for users to track revision history.  This markup is usually hidden, but can of interest for many user cases of KeyView Filter SDK.

```sh
> cd C:\MicroFocus\KeyviewFilterSDK_12.12.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> filter -rm ..\..\..\idol-oem-tutorials\resources\keyview_filter\2022_calendar_HIDDEN_TEXT.docx text_revison_marks.txt
filter: ..\..\..\idol-oem-tutorials\resources\keyview_filter\2022_calendar_HIDDEN_TEXT.docx text_revison_marks.txt
filter: error code returned is KVERR_Success
```

> NOTE: The `KVERR_Success` error code is a positive result where the destination `hidden_text` file contains the output.  Use your UTF-8 capable text editor, so you can properly view the output - just in case complex character sets are represented in the test document.  

The month of `February` is added to the output because it was tracked as a change when the month name was changed to `febbraio`.

Try `filter` to extract hidden text with your own test files. Good luck!

### Perform extraction excluding comments

Your use case for KeyView FilterSDK may not benefit from including comments.

```sh
> cd C:\MicroFocus\KeyviewFilterSDK_12.12.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> filter -nc ..\..\..\idol-oem-tutorials\resources\keyview_filter\2022_calendar_HIDDEN_TEXT.docx text_no_comments.txt
filter: ..\..\..\idol-oem-tutorials\resources\keyview_filter\2022_calendar_HIDDEN_TEXT.docx to text_no_comments.txt
filter: error code returned is KVERR_Success
```

> NOTE: The `KVERR_Success` error code is a positive result where the destination `hidden_text` file contains the output.  Use your UTF-8 capable text editor, so you can properly view the output - just in case complex character sets are represented in the test document.

If you compare the output from `text_no_comments.txt` with `text_no_hf.txt`, you'll see that the comments are no longer output at the bottom.

### Perform extraction of slide master

Presentation formats like PowerPoint have the concept of slide masters where some slide master content is only visible when you're editing the slider masters.

```sh
> cd C:\MicroFocus\KeyviewFilterSDK_12.12.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> filter  ..\..\..\idol-oem-tutorials\resources\keyview_filter\demo_EMBEDDED_DOCS+HIDDEN_TEXT.pptx text_no_slidemaster.txt
filter: ..\..\..\idol-oem-tutorials\resources\keyview_filter\demo_EMBEDDED_DOCS+HIDDEN_TEXT.pptx text_no_slidemaster.txt
filter: error code returned is KVERR_Success

> filter -sh ..\..\..\idol-oem-tutorials\resources\keyview_filter\demo_EMBEDDED_DOCS+HIDDEN_TEXT.pptx text_slidemaster.txt
filter: ..\..\..\idol-oem-tutorials\resources\keyview_filter\demo_EMBEDDED_DOCS+HIDDEN_TEXT.pptx text_slidemaster.txt
filter: error code returned is KVERR_Success
```

> NOTE: The `KVERR_Success` error code is a positive result where the destination `hidden_text` file contains the output.  Use your UTF-8 capable text editor, so you can properly view the output - just in case complex character sets are represented in the test document.

A lot of additional output is included in `text_slidemaster.txt`.  It's the text `Secret text in the slide master` that was added to the default content.  A user may have illicitly added text in the slide master in the hopes of evading detection.

## Conclusion

There are multiple types of text that a given file format may contain. KeyView Filter SDK strives to extract as much information as is possible from file formats.

Next, why not try more tutorials to explore some of the other features available in KeyView Filter SDK, linked from the [showcase](./README.md) page.

## See also

- [KeyView Filter SDK C Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html)
- [KeyView Filter SDK C++ Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/cpp-programming/index.html)
- [KeyView Filter SDK Java Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/java-programming/index.html)
- [KeyView Filter SDK .NET Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/dotnet-programming/index.html)
