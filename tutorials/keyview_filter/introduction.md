# KeyView Filter SDK Introduction

In this lesson, you will:

- Use the out-of-the-box command line tools `filter` and `tstxtract` to develop your understanding of the basic capabilities and key features of the KeyView Filter SDK.
- Familiarize yourself with Filter SDK output of the out-of-the-box command line tools.
- Familiarize yourself with Filter SDK configuration files.

---

- [Setup](#setup)
  - [Minimum requirements](#minimum-requirements)
  - [Useful third-party tools](#useful-third-party-tools)
  - [KeyView Filter SDK components](#keyview-filter-sdk-components)
    - [Activate a License Key](#activate-a-license-key)
    - [Download KeyView Filter SDK components](#download-keyview-filter-sdk-components)
    - [Install KeyView Filter SDK components](#install-keyview-filter-sdk-components)
- [Introduction to KeyView Filter SDK](#introduction-to-keyview-filter-sdk)
  - [Run `filter`](#run-filter)
  - [Format Detection](#format-detection)
  - [Metadata Extraction](#metadata-extraction)
    - [Perform general metadata extraction](#perform-general-metadata-extraction)
  - [Text Extraction](#text-extraction)
    - [Visible text](#visible-text)
  - [Sub-file Extraction](#sub-file-extraction)
    - [Run `tstxtract`](#run-tstxtract)
    - [Perform sub-file extraction](#perform-sub-file-extraction)
- [Review](#review)
- [Conclusion](#conclusion)
- [See also](#see-also)

---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

### Minimum requirements

- 1 core, 1 GB RAM, 5GB free disk space
- Windows x86_64, Windows x86_32, Linux_x86_64, Linux_ARM, MacOS_x86_64, MacOS_M1, ....
- KeyView license (optional, until using APIs or not using v12.12 or greater)
- useful third party tools noted below.

> NOTE: Disk space includes room for zips, unzipped version and generous working space.

> NOTE: The following guide details steps for Windows.  Steps will be similar for other supported platforms.

> NOTE: Sizing for your own production tasks depends on your use case, as discussed later in these tutorials.

### Useful third-party tools

- A (UTF-8 capable) text editor, *e.g.*:

  - [VS Code](https://code.visualstudio.com/download), or
  - [Notepad++](https://notepad-plus-plus.org/download), or
  - your favorite equivalent.

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
  - [Microsoft Paint](https://apps.microsoft.com/store/detail/paint/9PCFS5B6T72H?hl=en-us&gl=US), or
  - [ImageMagick](https://imagemagick.org/index.php), or
  - your favorite equivalent.

> NOTE: the PDF, "zip", "office" and image viewers are helpful tools to have, but not necessarily required.
 
### KeyView Filter SDK components

The KeyView SDKs consist of the Filter SDK, Export SDK, Viewing SDK and Panopticon.  This lesson is focused on the Filter SDK, which offers the following capabilities:
- automatic format detection
- standard, custom and XMP metadata extraction
- text extraction
- character set detection and conversion
- sub-file extraction
- RMS decryption 
- Optical Character Recognition (OCR)

#### Activate a License Key

The KeyView SDKs require a license key, which is unique to your project. 

To obtain an KeyView license key, follow these [steps](../setup/license_key_keyview.md), then return here to continue.

![get-software](../../figs/get-software.png)

> NOTE: For the lessons that use `filter` and `tstxtract`, a built-in (but expiring) license key is embedded in these executables. This means you can activate a license key later.

#### Download KeyView Filter SDK components

Download software from the [Software Licensing and Downloads](https://sld.microfocus.com/mysoftware/index) portal.

1. Under the *Downloads* tab, select your product, product name and version from the dropdowns:

2. From the list of available files, select and download the following (depending on your platform):
   - `KeyviewFilterSDK_12.13.0_{PLATFORM}`, *e.g.* `KeyviewFilterSDK_12.13.0_WINDOWS_X86_64.zip` or `KeyviewFilterSDK_12.13.0_LINUX_X86_64.exe`
   - `KeyviewFilterSDK_12.13_Documentation.zip`

  > NOTE: The installer `.exe` is only available for some available platforms: Linux_x86_32, Linux_x86_64, Windows_x86_32 and Windows_x86_64. This lesson will use the `.zip` package installation method.

3. From the list of available files, select and download any available patches for 
  - *e.g.* `KeyviewFilterSDK 12.13 Patch 12.13.2`
 
  > NOTE: Be sure to click on the `Reference Material` link under the `Description` column to access the link to the patch documentation which includes the release notes.
  
  > NOTE: All platforms are contained in the zip package for Keyview patches.

#### Install KeyView Filter SDK components

1. Copy your downloaded files into a new working folder.  The follow guide assumes this is `C:\MicroFocus` on Windows.
2. Extract `KeyviewFilterSDK_<VERSION>_<PLATFORM>.zip` file to:
   - `C:\MicroFocus\KeyviewFilterSDK_12.13.0_WINDOWS_X86_64`
3. On Windows, you may need to install the included Visual C++ Redistributable packages. In the the same FilterSDK's `vcredist` folder, right-click on `vcredist_2013.exe` then select 'Run as administrator'.  Repeat for `vcredist_2019.exe`.

  > HINT: If you see a version conflict error here, you may need to first uninstall any existing version.

4. This lesson will refer to `C:\MicroFocus\KeyviewFilterSDK_12.13.0_WINDOWS_X86_64` as `%KEYVIEW_HOME%`.
5. If a patch is available for version being used, then extract *e.g.* `KeyviewFilterSDK_12.13.0.8234.zip` to:
   - `C:\MicroFocus\KeyviewFilterSDK_12.13.x.yyyy`
6. Backup existing files and copy new ones from appropriate `KeyviewFilterSDK_<VERSION>\<PLATFORM>` folder. It is most likely that patch files will be updates to those in `%KEYVIEW_HOME%\<PLATFORM>\bin` folder and sub-folders:
   - `C:\MicroFocus\KeyviewFilterSDK_12.13.0_WINDOWS_X86_64\WINDOWS_X86_64\bin`

> NOTE: Do NOT mix & match patch updates across versions. *Only apply a patch update to its intended version*.

See the [KeyView Filter SDK Programming Guide - Introducing Filter SDK](
https://www.microfocus.com/documentation/idol/IDOL_12_13/KeyviewFilterSDK_12.13_Documentation/Guides/html/c-programming/index.html#filter_shared/filtersdk_intro/intro_filtersdk.htm) for more details.

## Introduction to KeyView Filter SDK

To get oriented with key concepts please read the [Getting Started section](https://www.microfocus.com/documentation/idol/IDOL_12_13/KeyviewFilterSDK_12.13_Documentation/Guides/html/c-programming/index.html#Chapter_GettingStarted.htm) of the KeyView Filter SDK * Programming Guide before continuing.
  
The following lesson will explore file format detection and metadata / text / sub-file extraction using the sample programs: `filter` and `tstxtract`.  
  
### Run `filter`

The sample program `filter` is a command line tool that demonstrates Filter API capabilities.  The source code for it ships in the `%KEYVIEW_HOME%\samples\filter` folder.  A pre-built binary is located in `%KEYVIEW_HOME%\<PLATFORM>\bin`.
  
```sh
> cd C:\MicroFocus\KeyviewFilterSDK_12.13.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> filter
Usage: filter [options] inputfile outputfile
options are:
     [-i] get doc summary info
     [-c] do not create a separate process for filtering
     [-e] run filtering in stream-based mode
     [-h] add headers/footers
     [-d] get the format information for a file
     [-k] create a separate process for detection
     [-l] do not create a separate process for detection
     [-mt] Enable memory management in Kvoop
     [-mtN] Disable memory management in Kvoop
     [-L] Enable Log in Kvoop
     [-LN] Disable Log in Kvoop
     [-AF] Add input file name to Kvoop Log
     [-rm] Include revision marks
     [-sh] Include hidden text from Word
     [-nc] No comments from Word or PowerPoint
     [-x xmlconfigfile] Specify the configuration file for XML reader
     [-z tmpdir] Specify a directory where temp files are created
     [-t timeout] Specify the number of seconds after which filter should time out (only for oop use)
     [-ps srcPassword] Specify the source document password
     [-pdfauto] Specify Logical Order output for the input PDF file
     [-pdfltr] Specify that the input PDF file is left-to-right dominate for logical order
     [-pdfrtl] Specify that the input PDF file is right-to-left dominate for logical order
     [-pdfraw] Use config api to force raw order mode for pdfsr reader
     [-xmp] get Extensible Metadata Platform (XMP) information structure
     [-xmpr] get raw XMP data packet

By default, an embedded trial license is used. If environment variables KV_SAMPLE_PROGRAM_LICENSE_ORGANIZATION and KV_SAMPLE_PROGRAM_LICENSE_KEY are set, their values will be used instead.
```

See the [reference guide](https://www.microfocus.com/documentation/idol/IDOL_12_13/KeyviewFilterSDK_12.13_Documentation/Guides/html/c-programming/index.html#Chapter_Samples.htm) for more details.
  
### Format Detection

The KeyView Filter SDK automatically recognizes the file type being filtered. Your application does not need to rely on the file extension to determine the file types.  Other general file attributes like format version and encryption status are also provided as part of automatic format detection.

From the command line, enter the following:
```sh
> filter -d "..\..\Release Notes\KeyViewFilterSDK_12.13.0_ReleaseNotes_en.pdf" detect
The file ..\..\Release Notes\KeyViewFilterSDK_12.13.0_ReleaseNotes_en.pdf
> cd C:\MicroFocus\KeyviewFilterSDK_12.13.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
File Class:             1
Format Name (Number):   PDF_Fmt (230)
Version:                1400
Attributes:             0
Description:            Adobe PDF (Portable Document Format)
MIME Type:              application/pdf

KWAD: error code returned is KVERR_Success  
```

> NOTE: The `KVERR_Success` error code is a positive result.

KeyView correctly identified this file as a PDF.  `Class ID: 1` refers to the `adWORDPROCESSOR` category.  See [Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_13/KeyviewFilterSDK_12.13_Documentation/Guides/html/c-programming/index.html#kv_formats/_KV_FMT__Detected.htm) for more details about format class/category and format id/number.

For the PDF file format, the `Major Version: 1400` refers `PDF1.4`.  And there are zero attributes applied to `KeyViewFilterSDK_12.13.0_ReleaseNotes_en.pdf`.

> NOTE: The class and format ID assignment scheme was created for KeyView and does not relate to any standard. When applicable the [Appendixes - Supported Formats](https://www.microfocus.com/documentation/idol/IDOL_12_13/KeyviewFilterSDK_12.13_Documentation/Guides/html/c-programming/index.html#kv_formats/_KV_FMT__Detected.htm) documentation does note the MIME type, but not all file formats have MIME types.

Try `filter -d` with your own test files and the additional lessons covered in the [showcase examples](../README.md#keyview-filter-sdk-showcase).

Good luck!

### Metadata Extraction
  
Documents can contain different flavors of metadata:
  - There are the document properties like `title`, `author` and others.  Some formats support custom document properties where document author makes up the key for the assigned value.
  - Some formats support [XMP Metadata](https://en.wikipedia.org/wiki/Extensible_Metadata_Platform).  PDF and image/audio/video file formats are the most common format categories that may contain XMP metadata.
  - Some applications, and corresponding file formats, allow users to restrict the ways in which a document can be used. KeyView supports identification of `write restrictions` for some file formats.  See [Document Restrictions](https://www.microfocus.com/documentation/idol/IDOL_12_13/KeyviewFilterSDK_12.13_Documentation/Guides/html/c-programming/index.html#filter_shared/DocumentRestrictions.htm?Highlight=document%20restrictions) for more details.
  
#### Perform general metadata extraction

KeyView refers to this topic as `document summary information`.

```sh
> filter -i "..\..\Release Notes\KeyViewFilterSDK_12.13.0_ReleaseNotes_en.pdf" metadata
filter: ..\..\Release Notes\KeyViewFilterSDK_12.13.0_ReleaseNotes_en.pdf to metadata
> cd C:\MicroFocus\KeyviewFilterSDK_12.13.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
filter: error code returned is KVERR_Success
```
> NOTE: The `KVERR_Success` error code is a positive result where the destination `metadata` file contains the output. Use your UTF-8 capable text editor, so you can properly view the output - just in case complex character sets are represented in the test document.

```
0 0  (null)
1 1 "IDOL KeyView Filter SDK 12.13.0 Release Notes" Title
0 0  (null)
1 1 "Micro Focus" Author
0 0  (null)
0 0  (null)
0 0  (null)
0 0  (null)
0 0  (null)
0 0  (null)
0 0  (null)
1 3 Fri Oct 21 08:21:17 2022 Create_DTM
1 3 Fri Oct 21 08:21:17 2022 LastSave_DTM
1 2 10 PageCount
0 0  (null)
0 0  (null)
0 0  (null)
1 1 "madbuild" AppName
...
```

The first column of the output is a flag indicating there is a value.  The second column indicates the datatype (*e.g.* 1 = string, 2 = integer, 3 = date). The third column is the value with the last column the field name.

Open `..\..\Release Notes\KeyViewFilterSDK_12.13.0_ReleaseNotes_en.pdf` in Adobe Acrobat Reader.  Go to `File --> Properties` and compare what you see in vs the output from `filter -i`.

Try `filter -i` with your own test files and the additional lessons covered in the [showcase examples](../README.md#keyview-filter-sdk-showcase). 

Good luck!

### Text Extraction

Filter SDK supports the extraction of different types of text, which we'll divide up into visible and hidden text.

#### Visible text

Visible text is what you easily see when you edit, view or print a document.

```sh
> .\filter "..\..\Release Notes\KeyViewFilterSDK_12.13.0_ReleaseNotes_en.pdf" text
filter: ..\..\Release Notes\KeyViewFilterSDK_12.13.0_ReleaseNotes_en.pdf to text
> cd C:\MicroFocus\KeyviewFilterSDK_12.13.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
filter: error code returned is KVERR_Success
```
> NOTE: The `KVERR_Success` error code is a positive result where the destination `text` file contains the output. Use your UTF-8 capable text editor, so you can properly view the output - just in case complex character sets are represented in the test document. 

Open `..\..\Release Notes\KeyViewFilterSDK_12.13.0_ReleaseNotes_en.pdf` in Adobe Acrobat Reader. You'll notice that the `filter` output contains all of the visible text with the formatting resembling the original document.

Try `filter` with your own test files and the additional lessons covered in the [showcase examples](../README.md#keyview-filter-sdk-showcase).

Good luck!

### Sub-file Extraction

Many file formats can contain other files. ZIP and similar files are the most obvious of these. But emails often contain attachments, which in turn can contain other files. Inserting images or a spreadsheet into an "Office" style document like a presentation file is very common. PDFs can even contain other files.

Let's perform sub-file extraction on the Filter SDK Java API KeyView.jar.

#### Run `tstxtract`

The sample program `tstxtract` is a command line tool that demonstrates Extract API capabilities.  The source code for it ships in the `%KEYVIEW_HOME%\samples\tstxtract` folder.  A pre-built binary is located in `%KEYVIEW_HOME%\<PLATFORM>\bin`.

```sh
> cd C:\MicroFocus\KeyviewFilterSDK_12.13.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> tstxtract
Usage: [options] <source file> <output directory> <keyview directory - optional>
Example: tstxtract inputfile outputdir
Example: tstxtract -l logfile -lm inputfile outputdir
When input file is a PST, please use absolute path
options are :
        [-c charset ] specify target character set (eg. "KVCS_SJIS")
        [-cf credfile1,credfile2,... ] specify input credential file(s) (eg. private key)
        [-l logfile ] give path and file name for logfile
        [-lm ] get default metadata and output to logfile
        [-lms metaname1,metaname2,... ] get metadata with string metanames and output to logfile (for MSG, EML, MBX, NSF, *etc.*)
        [-lmi metaint1,metaint2,... ] get metadata with integer (hexadecimal) metanames and output to logfile (for PST)
        [-lma] get all metadata and output to logfile (NSF and DXL only)
        [-i ] run as in-process
        [-r ] recursively extract subfiles that "needs extraction" to outputdir
        [-msg ] extract mail subfiles as native email (eg. extract MSG from PST)
        [-f ] extract mail subfiles in formatted (HTML or RTF or MHT) text
        [-e ] extract as stream with custom input and custom output stream
        [-p password1,password2,... ] specify password(s) to input file or the credential file(s)
        [-t ] preserve timestamp of embedded files when possible
        [-h ] extract hidden text
        [-to timeInSecs ] set kvoop extraction timeout (Filter SDK only)

By default, an embedded trial license is used. If environment variables KV_SAMPLE_PROGRAM_LICENSE_ORGANIZATION
and KV_SAMPLE_PROGRAM_LICENSE_KEY are set, their values will be used instead.
```
  
#### Perform sub-file extraction

Before we run `tstxtract`, we'll create an output folder `_extract`. Any location and name for the extraction destination directory will suffice where `_extract` and its location was chosen for convenience.

```sh
> cd C:\MicroFocus\KeyviewFilterSDK_12.13.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> mkdir _extract
> .\tstxtract ..\..\javaapi\KeyView.jar _extract
File ..\..\javaapi\KeyView.jar has 111 sub-files, charset: 0, format: 999
tstxtract return code: 0
```

> NOTE: return code: 0 is a positive result equivalent to `KVERR_Success`.

```
> dir _extract
Volume in drive D is DDrive
 Volume Serial Number is 66F6-7BE6

 Directory of C:\MicroFocus\KeyviewFilterSDK_12.13.0\WINDOWS_X86_64\bin\_extract

07/01/2022  09:16 AM    <DIR>          .
07/01/2022  09:16 AM    <DIR>          ..
07/01/2022  09:16 AM    <DIR>          com
07/01/2022  09:16 AM             4,960 htmlinfo.properties
07/01/2022  09:16 AM    <DIR>          META-INF
07/01/2022  09:16 AM             4,000 xmlinfo.properties
               2 File(s)          8,960 bytes
               4 Dir(s)  1,461,157,371,904 bytes free
```
111 sub-files are extracted with the directory structure preserved.
  
> NOTE: In some cases Filter SDK will auto-generate a filename for extract files.
  
> NOTE: Image extraction is not enabled by default. See [Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_13/KeyviewFilterSDK_12.13_Documentation/Guides/html/c-programming/index.html#Shared/_KV_xtract_Extract_Images.htm?Highlight=extractimages) for details on how to enable. You'll learn a little bit about the `filter\formats.ini` file.
  
> NOTE: Remember to delete the extracted contents of the `_extract` folder between each iteration.  

Try `tstxtract` with your own test files and the additional lessons covered in the [showcase examples](../README.md#keyview-filter-sdk-showcase).

Good luck!
  
## Review

In this lesson, you used Filter SDK to automatically detect the file format, perform basic metadata and text extraction, extract sub-files and configure `formats.ini`. There are other nuances with Filter SDK that you'll encounter over time.  File formats are at times inherently more complex than you can imagine.
  
## Conclusion

You should now be confident in the basics of KeyView Filter SDK.

Next, why not try more tutorials to explore some of the other features available in Filter SDK, linked from the [main page](../README.md#keyview-filter-sdk-showcase).

## See also

- [KeyView Filter SDK C Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_13/KeyviewFilterSDK_12.13_Documentation/Guides/html/c-programming/index.html)
- [KeyView Filter SDK C++ Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_13/KeyviewFilterSDK_12.13_Documentation/Guides/html/cpp-programming/index.html)
- [KeyView Filter SDK Java Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_13/KeyviewFilterSDK_12.13_Documentation/Guides/html/java-programming/index.html)
- [KeyView Filter SDK .NET Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_13/KeyviewFilterSDK_12.13_Documentation/Guides/html/dotnet-programming/index.html)
