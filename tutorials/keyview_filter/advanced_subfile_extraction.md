# Advanced Sub File Extraction

As we saw in the introduction lesson for OpenText File Content Extraction (formerly known as KeyView) Filter SDK, files contained within a file can be extracted for further processing.

In this lesson, you will:

- extract sub file(s) from RAR v5 file
- extract sub file(s) from password protected 7-Zip file
- extract sub files from E-Mail (MSG) with attachment
- gain a better understanding of the complexity of sub files

> NOTE: This guide assumes you have already completed the [Filter SDK introduction]tutorial](./introduction.md#introduction-to-filter-sdk).

---

- [Setup](#setup)
  - [Resources](#resources)
  - [Clean up `tstxtract` destination folder](#clean-up-tstxtract-destination-folder)
- [Perform Sub File Extraction](#perform-sub-file-extraction)
  - [Perform Sub File Extraction on RAR (v5) file](#perform-sub-file-extraction-on-rar-v5-file)
  - [Perform Sub File Extraction on 7-Zip file with password protection](#perform-sub-file-extraction-on-7-zip-file-with-password-protection)
  - [Perform Sub File Extraction on E-mail with attachment](#perform-sub-file-extraction-on-e-mail-with-attachment)
- [Conclusion](#conclusion)
- [See also](#see-also)
  
---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

> NOTE: This lesson assumes you have already completed the [Filter SDK introduction](./introduction.md#introduction-to-filter-sdk) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic Filter SDK concepts.

### Resources

Be sure to download the following resources before you continue:

- sample documents from [here](../../resources/keyview_filter/) and install to `C:\OpenText\idol-oem-tutorials\resources`

> NOTE: This lesson assumes you have already completed the [Filter SDK introduction](../keyview_filter/introduction.md) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic Filter SDK concepts.

### Clean up `tstxtract` destination folder

You may already have the `tstxtract` destination `_extract` from the introduction lesson.  Delete the folder and its contents and re-create the destination folder.

```sh
> cd C:\OpenText\KeyviewFilterSDK_25.4.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> rmdir /s _extract
_extract, Are you sure (Y/N)? y
> mkdir _extract
```

## Perform Sub File Extraction

### Perform Sub File Extraction on RAR (v5) file

The `KeyViewFilterSDK_12.12.0_ReleaseNotes_en.rar` was created with [WinRAR](https://www.win-rar.com/start.html).

> NOTE: Per notes [above](#clean-up-tstxtract-destination-folder), delete the contents of `_extract` folder and recreate before continuing.

```sh
> cd C:\OpenText\KeyviewFilterSDK_25.4.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> tstxtract ..\..\..\idol-oem-tutorials\resources\keyview_filter\KeyViewFilterSDK_12.12.0_ReleaseNotes_en.rar _extract
WARNING: tstxtract is a sample program only and is not for production use
File ..\..\..\idol-oem-tutorials\resources\keyview_filter\KeyViewFilterSDK_12.12.0_ReleaseNotes_en.rar has 1 sub files, charset: 0, format: 485
tstxtract return code: 0
```

> NOTE: `return code: 0` is a positive result equivalent to `KVERR_Success`.

The format code is identified as 485 which is a RAR v5 and the single PDF file contained with it is extracted.

Try `tstxtract` with your own variants of zip-like formats.  Don't forget that self-extracting exe files can be produced by [`WinRar`](https://www.win-rar.com), [`PKZip`](https://www.pkware.com/products/pkzip), [`WinZip`](https://www.winzip.com/en/), and [`7-zip`](https://www.7-zip.org/).  And many of these applications also support varying compression methods.  Extracting sub-files for further analysis should be expected regardless of these variations.

### Perform Sub File Extraction on 7-Zip file with password protection

Password protected files will inevitably be encountered by any application that handles files in the wild. Keyview Filter SDK can recognize this scenario and report on it in a useful manner and in the event you know the password or use a tool or brute force allow for sub file extraction to occur.

The `KeyViewFilterSDK_12.12.0_ReleaseNotes_en_PASSWORD.7z` was created with [7-Zip](https://www.7-zip.org/).

> NOTE: Per notes [above](#clean-up-tstxtract-destination-folder), delete the contents of `_extract` folder and recreate before continuing.

```sh
> cd C:\OpenText\KeyviewFilterSDK_25.4.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> tstxtract ..\..\..\idol-oem-tutorials\resources\keyview_filter\KeyViewFilterSDK_12.12.0_ReleaseNotes_en.pdf_PASSWORD.7z _extract
WARNING: tstxtract is a sample program only and is not for production use
Cannot open file ..\..\..\idol-oem-tutorials\resources\keyview_filter\KeyViewFilterSDK_12.12.0_ReleaseNotes_en.pdf_PASSWORD.7z, returned code is 8
tstxtract return code: 8
```

> NOTE: `return code: 8` indicates the file is password protected.

Filter SDK does support you providing a password (or password(s)) to `tstxtract`.

```sh
> tstxtract -p KeyView ..\..\..\idol-oem-tutorials\resources\keyview_filter\KeyViewFilterSDK_12.12.0_ReleaseNotes_en.pdf_PASSWORD.7z _extract
WARNING: tstxtract is a sample program only and is not for production use
File .\..\..\idol-oem-tutorials\resources\keyview_filter\KeyViewFilterSDK_12.12.0_ReleaseNotes_en.pdf_PASSWORD.7z has 1 sub files, charset: 0, format: 485
tstxtract return code: 0
```

Try `tstxtract` with your own password protected files of varying formats.

### Perform Sub File Extraction on E-mail with attachment

E-mails commonly contain attachments where the attachment will often contain sub-files.  Filter SDK can extract sub files in this scenario, too.

> NOTE: Per notes [above](#clean-up-tstxtract-destination-folder), delete the contents of `_extract` folder and recreate before continuing.

```sh
> cd C:\OpenText\KeyviewFilterSDK_25.4.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> tstxtract "..\..\..\idol-oem-tutorials\resources\keyview_filter\email with zip attachment.msg" _extract
WARNING: tstxtract is a sample program only and is not for production use
File ..\..\..\idol-oem-tutorials\resources\keyview_filter\email with zip attachment.msg has 2 sub files, charset: 51, format: 345
tstxtract return code: 0
```

> NOTE: `return code: 0` is a positive result equivalent to `KVERR_Success`.

Two files are extracted, the zip attachment and .mail representing e-mail message.

Now, let's process the same file with `[-r] recursively extract sub files`.  Create a different `tstxtract` destination folder so we can easily compare the different output.

```sh
> mkdir _extract.2
> tstxtract -r "..\..\..\idol-oem-tutorials\resources\keyview_filter\email with zip attachment.msg" _extract.2
WARNING: tstxtract is a sample program only and is not for production use
File ..\..\..\..\idol-oem-tutorials-main\resources\keyview_filter\email with zip attachment.msg has 2 sub files, charset: 51, format: 345
File _extract.2\email wi/demo_HAS_EMBEDDED_DOC.zip has 1 sub files, charset: 0, format: 157
File _extract.2\email wi/demo_HAS_EMBEDDED_DOC.zip.dir\demo_EMBEDDED_DOCS+HIDDEN_TEXT.pptx has 2 sub files, charset: 53, format: 362
File _extract.2\email wi/demo_HAS_EMBEDDED_DOC.zip.dir\demo_EMBEDDED_DOCS+HIDDEN_TEXT.pptx.dir\Microsoft_Word_Document.docx has 1 sub files, charset: 53, format: 360
File _extract.2\email wi/demo_HAS_EMBEDDED_DOC.zip.dir\demo_EMBEDDED_DOCS+HIDDEN_TEXT.pptx.dir\Microsoft_Excel_Worksheet.xlsx has 0 sub files, charset: 0, format: 361
tstxtract return code: 0
```

> NOTE: `return code: 0` is a positive result equivalent to `KVERR_Success`.

This time the PPTX in the attached zip file is extracted, as well as the sub files within the PPTX.  All of the counts of the extacted files are pretty obvious if you open each file in their native application with the exception of the `_extract\Microsoft_Word_Document.docx`.  The 1 sub file noted in it is a link to the template used to create the DOCX with no additional currently extracted with `tstxtract`.

If you enable image extraction in the formats.ini as explained [here](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/Shared/_KV_xtract_Extract_Images.htm) even more sub files will be extracted. The XLSX contains 6 embedded PNG images.

```sh
> tstxtract -r "..\..\..\idol-oem-tutorials\resources\keyview_filter\email with zip attachment.msg" _extract
WARNING: tstxtract is a sample program only and is not for production use
File ..\..\..\..\idol-oem-tutorials-main\resources\keyview_filter\email with zip attachment.msg has 2 sub files, charset: 51, format: 345
File _extract\email wi/demo_HAS_EMBEDDED_DOC.zip has 1 sub files, charset: 0, format: 157
File _extract\email wi/demo_HAS_EMBEDDED_DOC.zip.dir\demo_EMBEDDED_DOCS+HIDDEN_TEXT.pptx has 2 sub files, charset: 53, format: 362
File _extract\email wi/demo_HAS_EMBEDDED_DOC.zip.dir\demo_EMBEDDED_DOCS+HIDDEN_TEXT.pptx.dir\Microsoft_Word_Document.docx has 1 sub files, charset: 53, format: 360
File _extract\email wi/demo_HAS_EMBEDDED_DOC.zip.dir\demo_EMBEDDED_DOCS+HIDDEN_TEXT.pptx.dir\Microsoft_Excel_Worksheet.xlsx has 6 sub files, charset: 0, format: 361
tstxtract return code: 0
```

> NOTE: `return code: 0` is a positive result equivalent to `KVERR_Success`.

## Conclusion

Many more document formats can contain sub files than you may initially imagine.  This lesson covered obvious ones like RAR, 7-Zip, MSG, as well as slightly less obvious formats like PPTX, DOCX, XLSX.  Plus there can be different types of embedded objects and/or files contained within a given document

Next, why not try more tutorials to explore some of the other features available in Filter SDK, linked from [here](../keyview_filter/README.md#capability-showcase).

## See also

- [Filter SDK C Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/index.html)
- [Filter SDK C++ Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/cpp-programming/index.html)
- [Filter SDK Java Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/java-programming/index.html)
- [Filter SDK .NET Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/dotnet-programming/index.html)
- [Filter SDK Python Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/python-programming/)
- [File Content Extraction Release Notes](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/IDOLReleaseNotes_25.4_Documentation/oem/Content/_KeyView.htm)
