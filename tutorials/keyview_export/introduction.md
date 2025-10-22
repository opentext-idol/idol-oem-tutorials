# Export SDK Introduction

In this lesson, you will:

- Learn about Export SDK's output options: HTML, XML and PDF.
- Use the out-of-the-box command line tools like `kvhtmlexport`, `cnv2xml` and `cnv2pdf` to develop your understanding of the basic capabilities and key features of the Export SDK.

---

- [Setup](#setup)
  - [Minimum requirements](#minimum-requirements)
  - [Resources](#resources)
  - [Useful third-party tools](#useful-third-party-tools)
  - [Export SDK components](#export-sdk-components)
    - [Activate a License Key](#activate-a-license-key)
    - [Download Export SDK components](#download-export-sdk-components)
    - [Install Export SDK components](#install-export-sdk-components)
- [Introduction to Export SDK](#introduction-to-export-sdk)
  - [Run `kvhtmlexport`](#run-kvhtmlexport)
  - [Run `cnv2xml`](#run-cnv2xml)
  - [Run `cnv2pdf`](#run-cnv2pdf)
- [Review](#review)
- [Conclusion](#conclusion)
- [See also](#see-also)

---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

### Minimum requirements

- 1 core, 1 GB RAM, 5GB free disk space
- Windows x86_64, Windows x86_32, Windows_ARM64, Linux_x86_64, Linux_ARM, MacOS_x86_64, MacOS_M1, ....
- Export SDK license (optional, not required until using Export SDK APIs)
- useful third party tools noted below.

> NOTE: Disk space includes room for installer zipped and unzipped and generous working space.

> NOTE: The following guide details steps for Windows.  Steps will be similar for other supported platforms.

> NOTE: Sizing for your own production tasks depends on your use case, as discussed later in these tutorials.

### Resources

Be sure to download the following resources before you continue:

- T.B.D.

> NOTE: `The ExportSDK_<PLATFORM>.zip` contains a folder called `testdocs` containing a collection of files to exercise ExportSDK capabilities.

### Useful third-party tools

- A (UTF-8 capable) text editor, *e.g.*:

  - [VS Code](https://code.visualstudio.com/download), or
  - [Notepad++](https://notepad-plus-plus.org/downloads/), or
  - your favorite equivalent.

- HTML renderer (web browser), *e.g.*:
  - Firefox
  - Microsoft Edge
  - Google Chrome
  - Safari
  - your favorite equivalent
  
- A Markdown viewer
  - Plugins to VS Code, Notepad++ and some web browsers are good options

- PDF viewer
  - [Adobe Acrobat Reader](https://www.adobe.com/acrobat/pdf-reader.html), or
  - your favorite equivalent.

- 7z/RAR/Zip/Jar reader
  - [7-Zip](https://www.7-zip.org/), or
  - your favorite equivalent

- Microsoft Excel, PowerPoint, Word or other "Office" file capable reader
  
- Image Viewer, *e.g*:
  - [Microsoft Paint](https://apps.microsoft.com/detail/9pcfs5b6t72h?hl=en-US&gl=US), or
  - [ImageMagick](https://imagemagick.org/index.php), or
  - your favorite equivalent.

> NOTE: the PDF, "zip", "office" and image viewers are helpful tools to have, but not necessarily required.

### Export SDK components

The File Content Extraction SDKs consist of the Filter SDK, Export SDK, Viewing SDK and Panopticon.  This lesson is focused on the Export SDK, which offers the following capabilities:

- automatic format detection
- produce HTML rendition
- produce XML rendition
- produce PDF rendition

#### Activate a License Key

The Export SDK requires a license key, which is unique to your project.

To obtain an license key, follow these [steps](../setup/license_key_keyview.md), then return here to continue.

![get-software](../../figs/get-software-keyview.png)

> NOTE: For the lessons that use `filter` and `tstxtract`, a built-in (but expiring) license key is embedded in these executables. This means you can activate a license key later.

#### Download Export SDK components

Download software from the [Software Licensing and Downloads](https://sld.microfocus.com/mysoftware/index) portal.

1. Under the *Downloads* tab, select your product, product name and version from the dropdowns:

1. From the list of available files, select and download the following (depending on your platform):
   - `KeyviewExportSDK_25.4.0_{PLATFORM}`, *e.g.* `KeyviewExportSDK_25.4.0_WINDOWS_X86_64.zip` or `KeyviewExportSDK_25.4.0_LINUX_X86_64.exe` or similar for other supported platforms
   - `KeyviewExportSDK_25.4.0_Documentation.zip`

  > NOTE: The installer `.exe` is only available for some available platforms: Linux_x86_32, Linux_x86_64, Windows_x86_32 and Windows_x86_64. This lesson will use the `.zip` package installation method.

1. From the list of available files, select and download any available patches for, *e.g.* `KeyviewExportSDK 25.4 Patch 25.4.x`.

  > NOTE: Be sure to click on the `Reference Material` link under the `Description` column to access the link to the patch documentation which includes the release notes.

  > NOTE: All platforms are contained in the zip package for Keyview patches.

#### Install Export SDK components

1. Copy your downloaded files into a new working folder.  The following guide assumes this is `C:\OpenText` on Windows.
1. Extract `KeyviewExportSDK_<VERSION>_<PLATFORM>.zip` file to:
   - `C:\OpenText\KeyviewExportSDK_25.4.0_WINDOWS_X86_64`
1. On Windows, you may need to install the included Visual C++ Redistributable packages. In the same FilterSDK's `vcredist` folder, right-click on `vcredist_2019.exe` then select 'Run as administrator'.

  > HINT: If you see a version conflict error here, you may need to first uninstall any existing version.

1. This lesson will refer to `C:\OpenText\KeyviewExportSDK_25.4.0_WINDOWS_X86_64` as `%KEYVIEW_HOME%`.
1. If a patch is available for version being used, then extract *e.g.* `KeyviewExportSDK_25.4.x.yyyy.zip` to:
   - `C:\OpenText\KeyviewExportSDK_25.4.x.yyyy`
1. Backup existing files and copy new ones from appropriate `KeyviewFilterSDK_<VERSION>\<PLATFORM>` folder. It is most likely that patch files will be updates to those in `%KEYVIEW_HOME%\<PLATFORM>\bin` folder and sub-folders:
   - `C:\OpenText\KeyviewExportSDK_25.4.0_WINDOWS_X86_64\WINDOWS_X86_64\bin`

> NOTE: Do NOT mix & match patch updates across versions. *Only apply a patch update to its intended version*.

See the [HTML Export SDK Programming Guide - Introducing Export SDK](
https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewExportSDK_25.4_Documentation/Guides/html/html-export-c/Content/export/Introduction/Introduction.htm) for more details on installation.

## Introduction to Export SDK

To get oriented with key concepts please read the [Introducing Export SDK - Features](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewExportSDK_25.4_Documentation/Guides/html/html-export-c/Content/export/Introduction/Features.htm) of the HTML/XML/PDF Export SDK * Programming Guides before continuing.
  
The following lesson will explore converting a document to HTML, XML and PDF using the sample programs: `kvhtmlexport`, `cnv2pdf` and `cnv2pdf`.  
  
### Run `kvhtmlexport`

The sample program `kvhtmlexport` is a command line tool that demonstrates some of the HTML Export API capabilities.  The source code for it ships in the `%KEYVIEW_HOME%\htmlexport\libkvhtmlexport` folder.  A pre-built binary is located in `%KEYVIEW_HOME%\<PLATFORM>\bin`.
  
```sh
> cd C:\OpenText\KeyviewExportSDK_25.4.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> kvhtmlexport
WARNING: kvhtmlexport is a sample program only and is not for production use
Note that this program must run from the KeyView Export SDK bin directory

usage: kvhtmlexport [options] <input file path> <output file path>

Options:
  --fullscreen                                          Export Presentation Graphics in Fullscreen mode
  --no-document-font-colors                             Disable color attributes appear in the <font> tags
  --generate-urls                                       Add anchor tags(<a ...></a>) to text starting with
                                                        'www', 'http:', 'file:'
  --remove-empty-columns                                Remove empty columns in spreadsheet
  --output-vector-graphic-type [KVGFX_JPEG|KVGFX_SVG]   Set the output format of vector graphics

By default, this sample program uses an embedded trial license. If the environment variable
KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH is set, this file will be read and its content will
be passed as a license to KeyView. This mechanism exists only to allow this program to be used
in testing after the expiry of its trial license, and should not be done in production code.
```

See the [HTML Export SDK Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewExportSDK_25.4_Documentation/Guides/html/html-export-c/Content/C/samples_export/kvhtmlexport.htm) for more details about `kvhtmlexport`.

To perform a conversion to HTML provide an input filepath and output filepath as shown below:

```sh
> cd C:\OpenText\KeyviewExportSDK_25.4.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> mkdir ..\..\testdocs\_HTMLExport
> kvhtmlexport ..\..\testdocs\Investment_Portfolio.xlsx ..\..\testdocs\_HTMLExport\export.html
WARNING: kvhtmlexport is a sample program only and is not for production use
Conversion complete
```

Open `..\..\testdocs\_HTMLExport\export.html` in your favorite web browser.  Compare the HTML rendition to the original file (`..\..\testdocs\Investment_Portfolio.xlsx`) as viewed in Microsoft Excel.

Try the `kvhtmlexport` with the other Export SDK `testdocs` and your own documents.
  
### Run `cnv2xml`

The sample program `cnv2xml` is a command line tool that demonstrates some of the XML Export API capabilities.  The source code for it ships in the `%KEYVIEW_HOME%\xmlexport\programs\cnv2xml` folder.  A pre-built binary is located in `%KEYVIEW_HOME%\<PLATFORM>\bin`.
  
```sh
> cd C:\OpenText\KeyviewExportSDK_25.4.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> cnv2xml
WARNING: cnv2xml is a sample program only and is not for production use
Usage: cnv2xml [options] inputfile outputfile
        Convert inputfile to XML and store result in outputfile
        options are:
                [-c KVCFG_DISABLEZONE] Disable conversion of MS Word bookmarks to zone elements
                [-c KVCFG_SUPPRESSIMAGES] Supress image processing
                [-c KVCFG_ENABLEPOSITIONINFO] Enable position information processing
                [-c KVCFG_DELSOFTHYPHEN] Remove soft hyphens at the end of line
                [-c KVCFG_SETPASSWORD srcPassword] Specify the source document password
                [-pdfltr] Specify that the input PDF file is
                     left-to-right dominate for logical order
                [-pdfrtl] Specify that the input PDF file is
                     right-to-left dominate for logical order
                [-pdfauto] Specify Logical Order Output for
                     the input PDF file
        All auxillary output is placed in the same directory as outputfile

By default, this sample program uses an embedded trial license. If the environment variable
KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH is set, this file will be read and its content will
be passed as a license to KeyView. This mechanism exists only to allow this program to be used
in testing after the expiry of its trial license, and should not be done in production code.
```

See the [XML Export SDK Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewExportSDK_25.4_Documentation/Guides/html/xml-export-c/Content/C/samples_export/cnv2xml.htm) for more details about `cnv2xml`.

To perform a conversion to XML provide an input filepath and output filepath as shown below:

```sh
> cd C:\OpenText\KeyviewExportSDK_25.4.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> mkdir ..\..\testdocs\_XMLExport
> cnv2xml ..\..\testdocs\Annual_Report.docx ..\..\testdocs\_XMLExport\export.xml
WARNING: cnv2xml is a sample program only and is not for production use
Conversion of ..\..\testdocs\Annual_Report.docx to XML completed.
```

Open `..\..\testdocs\_XMLExport\export.xml` in your favorite XML Viewer (most modern web browsers render XML).

Try the `cnv2xml` with the other Export SDK `testdocs` and your own documents.

### Run `cnv2pdf`

The sample program `cnv2xml` is a command line tool that demonstrates some of the XML Export API capabilities.  The source code for it ships in the `%KEYVIEW_HOME%\pdfexport\cnv2pdf` folder.  A pre-built binary is located in `%KEYVIEW_HOME%\<PLATFORM>\bin`.
  
```sh
> cd C:\OpenText\KeyviewExportSDK_25.4.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> cnv2pdf
WARNING: cnv2pdf is a sample program only and is not for production use
Usage: cnv2pdf.exe inputfile outputfile
        Convert inputfile to PDF and store result in outputfile.
                [-p password] Specify the source document password.
                [-s pagesize] Specify the page size (in inches) for printing as 'w h',  e.g. '-s 8.5 11'.  If not specified, defaults to US letter size.
                [-t thumbsize] Generate PNG thumbnail instead of PDF. Specify the thumbnail size (in pixels) for printing as 'w h', e.g. '-t 2000 1500'
        This must be run from the directory containing the keyview binaries.

By default, this sample program uses an embedded trial license. If the environment variable
KV_SAMPLE_PROGRAM_LICENSE_FROM_FILEPATH is set, this file will be read and its content will
be passed as a license to KeyView. This mechanism exists only to allow this program to be used
in testing after the expiry of its trial license, and should not be done in production code.
```

See the [PDF Export SDK Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewExportSDK_25.4_Documentation/Guides/html/pdf-export-c/Content/C/samples_export/cnv2pdf.htm) for more details about `cnv2pdf`.

To perform a conversion to PDF provide an input filepath and output filepath as shown below:

```sh
> cd C:\OpenText\KeyviewExportSDK_25.4.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> mkdir ..\..\testdocs\_PDFExport
> cnv2pdf ..\..\testdocs\Annual_Report.docx ..\..\testdocs\_PDFExport\Annual_Report.docx.KVExport.PDF
WARNING: cnv2pdf is a sample program only and is not for production use
cnv2pdf: loading kvpdf
cnv2pdf: loading kvpdf interface
cnv2pdf: initialising kvpdf interface
cnv2pdf: converting file
cnv2pdf: shutting down kvpdf
cnv2pdf: unloading kvpdf
```

Open `..\..\testdocs\_PDFExport\Annual_Report.docx.KVExport.PDF` in your favorite PDF Viewer (most modern web browsers render PDF or use Adobe Acrobat).  Compare the PDF rendition to the original file (`..\..\testdocs\Annual_Report.docx`) as viewed in Microsoft Word.

Try the `cnv2pdf` with the other Export SDK `testdocs` and your own documents.

## Review

In this lesson, you used the Export SDK to convert documents to HTML, XML and PDF.
  
## Conclusion

You should now be confident in the basics of the HTML Export SDK.

Next, why not try more tutorials to explore some of the other features available in Export SDK, linked from the [main page](../README.md#export-sdk-showcase).

## See also

- [HTML Export SDK C Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewExportSDK_25.4_Documentation/Guides/html/html-export-c/index.html)
- [HTML SDK Java Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewExportSDK_25.4_Documentation/Guides/html/html-export-java/index.html)
- [XML Export C Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewExportSDK_25.4_Documentation/Guides/html/xml-export-c/index.html)
- [XML Export Java Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewExportSDK_25.4_Documentation/Guides/html/xml-export-java/)
- [PDF Export C Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewExportSDK_25.4_Documentation/Guides/html/pdf-export-c/index.html)
- [File Content Extraction Release Notes](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/IDOLReleaseNotes_25.4_Documentation/oem/Content/_KeyView.htm)
