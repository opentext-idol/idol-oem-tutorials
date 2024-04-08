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
- [Preserve logical reading order in Presentation formats](#preserve-logical-reading-order-in-presentation-formats)
  - [Perform logical order preservation](#perform-logical-order-preservation)
- [Extra Credit](#extra-credit)
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

## Headers / Footers

Word processing, spreadsheet, presentation and some other file formats optionally allow for headers / footers to be inserted.  

### Perform header / footer extraction

Let's run text extraction on the same file `2022_calendar_HIDDEN_TEXT.docx` without and with header/footer mode enabled.

```sh
> cd C:\OpenText\KeyviewFilterSDK_24.2.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> filter ..\..\..\idol-oem-tutorials\resources\keyview_filter\2022_calendar_HIDDEN_TEXT.docx text_no_hf.txt
WARNING: filter is a sample program only and is not for production use
filter: ..\..\..\idol-oem-tutorials\resources\keyview_filter\2022_calendar_HIDDEN_TEXT.docx to text_no_hf.txt
filter: error code returned is KVERR_Success

> filter -h ..\..\..\idol-oem-tutorials\resources\keyview_filter\2022_calendar_HIDDEN_TEXT.docx text_hf.txt
WARNING: filter is a sample program only and is not for production use
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
> cd C:\OpenText\KeyviewFilterSDK_24.2.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> filter -rm ..\..\..\idol-oem-tutorials\resources\keyview_filter\2022_calendar_HIDDEN_TEXT.docx text_revison_marks.txt
WARNING: filter is a sample program only and is not for production use
filter: ..\..\..\idol-oem-tutorials\resources\keyview_filter\2022_calendar_HIDDEN_TEXT.docx text_revison_marks.txt
filter: error code returned is KVERR_Success
```

> NOTE: The `KVERR_Success` error code is a positive result where the destination `hidden_text` file contains the output.  Use your UTF-8 capable text editor, so you can properly view the output - just in case complex character sets are represented in the test document.  

Compare `text_revison_marks.txt` and `text_no_hf.txt`. You will see that `February` is added to the output because it was tracked as a change when the month name was changed to `febbraio`.

Try `filter` to extract hidden text with your own test files. Good luck!

### Perform extraction excluding comments

Your use case for KeyView FilterSDK may not benefit from including comments.

```sh
> cd C:\OpenText\KeyviewFilterSDK_24.2.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> filter -nc ..\..\..\idol-oem-tutorials\resources\keyview_filter\2022_calendar_HIDDEN_TEXT.docx text_no_comments.txt
WARNING: filter is a sample program only and is not for production use
filter: ..\..\..\idol-oem-tutorials\resources\keyview_filter\2022_calendar_HIDDEN_TEXT.docx to text_no_comments.txt
filter: error code returned is KVERR_Success
```

> NOTE: The `KVERR_Success` error code is a positive result where the destination `hidden_text` file contains the output.  Use your UTF-8 capable text editor, so you can properly view the output - just in case complex character sets are represented in the test document.

Compare `text_no_comments.txt` and `text_no_hf.txt`.  You will see that the comments are no longer output at the bottom.

### Perform extraction of slide master

Presentation formats like PowerPoint have the concept of slide masters where some slide master content is only visible when you're editing the slider masters.

```sh
> cd C:\OpenText\KeyviewFilterSDK_24.2.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> filter ..\..\..\idol-oem-tutorials\resources\keyview_filter\demo_EMBEDDED_DOCS+HIDDEN_TEXT.pptx text_no_slidemaster.txt
WARNING: filter is a sample program only and is not for production use
filter: ..\..\..\idol-oem-tutorials\resources\keyview_filter\demo_EMBEDDED_DOCS+HIDDEN_TEXT.pptx text_no_slidemaster.txt
filter: error code returned is KVERR_Success

> filter -sh ..\..\..\idol-oem-tutorials\resources\keyview_filter\demo_EMBEDDED_DOCS+HIDDEN_TEXT.pptx text_slidemaster.txt
WARNING: filter is a sample program only and is not for production use
filter: ..\..\..\idol-oem-tutorials\resources\keyview_filter\demo_EMBEDDED_DOCS+HIDDEN_TEXT.pptx text_slidemaster.txt
filter: error code returned is KVERR_Success
```

> NOTE: The `KVERR_Success` error code is a positive result where the destination `hidden_text` file contains the output.  Use your UTF-8 capable text editor, so you can properly view the output - just in case complex character sets are represented in the test document.

A lot of additional output is included in `text_slidemaster.txt`.  It's the text `Secret text in the slide master` that was added to the default content.  A user may have illicitly added text in the slide master in the hopes of evading detection.

## Preserve logical reading order in Presentation formats

With some file formats, for example Microsoft PowerPoint presentations, the order of the text inside the file has no relation to the layout of the text on the page or screen. Recently modified text might appear at the end of a file, even though that text belongs at the beginning of the document.

Refer to the [Keyview Filter SDK Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_2/KeyviewFilterSDK_24.2_Documentation/Guides/html/c-programming/Content/filter_shared/Presentation_LogicalOrder.htm) for more details about KeyView's support for preserving logical reading order.

### Perform logical order preservation

The KeyView resources README.md references a file [AmeliorationFertiliteDesSols.pptx](../../resources/keyview_filter/README.md#AmeliorationFertiliteDesSolspptx) that exhibits this behavior.  Please download it place it in the `idol-oem-tutorials\resources\keyview_filter` folder.

Use `filter` to extract text with `LogicalOrder` disabled.
```sh
> cd C:\OpenText\KeyviewFilterSDK_24.2.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> filter ..\..\..\idol-oem-tutorials\resources\keyview_filter\AmeliorationFertiliteDesSols.pptx text_LO=F.txt
WARNING: filter is a sample program only and is not for production use
filter: ..\..\..\idol-oem-tutorials\resources\keyview_filter\AmeliorationFertiliteDesSols.pptx text_LO=F.txt
filter: error code returned is KVERR_Success
```

Preservation of logical reading order is disabled by default.  Modify `formats.ini` as shown below to enable it.
```diff
[Options]
+LogicalOrder=1
```

 Use `filter` to extract text with `LogicalOrder` enabled.
```sh
> cd C:\OpenText\KeyviewFilterSDK_24.2.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> filter ..\..\..\idol-oem-tutorials\resources\keyview_filter\AmeliorationFertiliteDesSols.pptx text_LO=T.txt`
WARNING: filter is a sample program only and is not for production use
filter: ..\..\..\idol-oem-tutorials\resources\keyview_filter\AmeliorationFertiliteDesSols.pptx text_LO=T.txt
filter: error code returned is KVERR_Success
```

The following is the text from slide 1 with `LogicalOrder=0`:
```
Amélioration de la fertilité des sols
					   
															  
Auteur du document : Benjamin LISAN. Email : benjamin.lisan@free.fr 
1
Culture en semis direct. Source : www.la-ferme-du-hourcot.com 
Par des moyens naturels

Amélioration de la fertilité des sols
```

The following is the text from slide 1 with `LogicalOrder=1`:
```
1
Amélioration de la fertilité des sols
Par des moyens naturels
Culture en semis direct. Source : www.la-ferme-du-hourcot.com 
Auteur du document : Benjamin LISAN. Email : benjamin.lisan@free.fr 
 
															  
					   

Amélioration de la fertilité des sols
```
Notice the differences with the location of the sub title text `Par des moyens naturels` and the `Auteur du document` text. 

Preservation of the logical reading order is valuable for any downstream solutions that may rely on the the proximity and/or order of text. This can include text search or text analytics for use cases such as eDiscovery or Data Loss Prevention (DLP).

## Extra Credit

The [keyview_filter resources](../../resources/keyview_filter/README.md#advanced-text-extraction) has a few other files not included in this lesson but illustrate additional forms of visible and hidden text:
- [Simple meal planner1.xlsx](../../resources/keyview_filter#simple-meal-planner1xlsx)
- [Robin Zupanc Resume_RESTRICTED.docx](../../resources/keyview_filter#robin-zupanc-resume_restricteddocx)
Leverage `filter` as you've explored in this lesson to extract text from these additional sample files.

## Conclusion

There are multiple types of text that a given file format may contain. KeyView Filter SDK strives to extract as much information as is possible from file formats.

Next, why not try more tutorials to explore some of the other features available in KeyView Filter SDK, linked from the [main page](../README.md#keyview-filter-showcase).

## See also

- [KeyView Filter SDK C Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_2/KeyviewFilterSDK_24.2_Documentation/Guides/html/c-programming/index.html)
- [KeyView Filter SDK C++ Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_2/KeyviewFilterSDK_24.2_Documentation/Guides/html/cpp-programming/index.html)
- [KeyView Filter SDK Java Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_2/KeyviewFilterSDK_24.2_Documentation/Guides/html/java-programming/index.html)
- [KeyView Filter SDK .NET Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_2/KeyviewFilterSDK_24.2_Documentation/Guides/html/dotnet-programming/index.html)
- [KeyView Filter SDK Python Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_2/KeyviewFilterSDK_24.2_Documentation/Guides/html/python-programming/)
- [KeyView Release Notes](https://www.microfocus.com/documentation/idol/IDOL_24_2/IDOLReleaseNotes_24.2_Documentation/oem/Content/_KeyView.htm)
