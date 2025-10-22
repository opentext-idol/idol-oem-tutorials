# Advanced Format Detection

As we saw in the introduction lesson for OpenText File Content Extraction (formerly known as KeyView) Filter SDK, the format type (and class) and other attributes can be automatically detected for files.  The Filter SDK relies on a format signature to uniquely identify the format code (with >2000 supported as of the 25.4 release).  Relying on a file extension is dangerous and can result in mis-processing with extra downstream processing costs.  Encryption & password protection often limits the visibility inside files.  The Filter SDK does its best to uniquely identify protected files and also set a separate flag indicating encryption status.

In this lesson, you will:

- explore not relying on the file extension
- explore password / encryption detection

> NOTE: This guide assumes you have already completed the [Filter SDK introduction](./introduction.md#introduction-to-filter-sdk) lesson.

---

- [Setup](#setup)
  - [Resources](#resources)
- [Do not rely on the file extension](#do-not-rely-on-the-file-extension)
  - [Perform detection on SmartCipher file](#perform-detection-on-smartcipher-file)
- [Password / Encryption detection](#password--encryption-detection)
  - [Perform password / encryption detection](#perform-password--encryption-detection)
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

## Do not rely on the file extension

The OpenText SmartCipher encrypted file `SmartCipher_Fmt.txt` was a text file originally in this case.  For this lesson, it was copied with `.BOGUS_EXTENSION` appended.

### Perform detection on SmartCipher file

```sh
> cd C:\OpenText\KeyviewFilterSDK_25.4.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> filtertest -ah "..\..\..\idol-oem-tutorials\resources\keyview_filter\SmartCipher_Fmt.txt" detect
WARNING: filter is a sample program only and is not for production use
autodetect: ..\..\..\idol-oem-tutorials\resources\keyview_filter\SmartCipher_Fmt.txt to detect
Return code is 0
filtertest finished with RC: 0

> type detect
File Class:             8
Format Number:          SmartCipher_Fmt (1255)
Version:                0
Attributes:             1 (Encrypted)
Description:            SmartCipher encrypted file
MIME Type:              -
```

> NOTE: A return code of `0` is a positive result. 

The file is correctly detected as format code 1255 and as encrypted per `Attributes: 1`.

The same exact result is returned when processing `SmartCipher_Fmt.txt.BOGUS_EXTENSION`.

Try `filtertest -ah` with other file formats. If you have some (or can acquire them), business intelligence (BI) files from Tableau and others are often a `.zip` file containing their respective interesting data. The [resources README.md](../../resources/keyview_filter/README.md#coffee-chaintwbx) for this tutorial contains a link to a Tableau Packaged Workbook (`.TWBX`) file.  A `.TWBX` that is technically a `.zip` file but contains a Tableau Workbook file (`.TWB`) (technically XML), data file(s) of varying formats and other resources.

> NOTE: Microsoft DOCX/PPT/XLSX files are technically zip files. Apple iWork, OpenOffice and many other file formats are also technically zip files.  Open example files that you have in a text editor and you'll see 'PK...' in the beginning.  And you will also be able to open most flavors of these files that you find with WinZip, 7-Zip or similar. By doing so, you will get a sense for the complexity in intelligently extract information from any file format.

## Password / Encryption detection

Many file formats allow for their contents to be password protected and/or encrypted.  When possible, Filter SDK will identify this scenario and return this as part of the format detection attributes data.

### Perform password / encryption detection

In the above example with `SmartCipher_Fmt.txt`, the attribute for `encrypted` file was returned.  This lesson will explore this further with a 7-zip file.

```sh
> cd C:\OpenText\KeyviewFilterSDK_25.4.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> filtertest -ah "..\..\..\idol-oem-tutorials\resources\keyview_filter\KeyViewFilterSDK_12.12.0_ReleaseNotes_en.pdf_PASSWORD.7z" detect
WARNING: filter is a sample program only and is not for production use
autodetect: ..\..\..\idol-oem-tutorials\resources\keyview_filter\KeyViewFilterSDK_12.12.0_ReleaseNotes_en.pdf_PASSWORD.7z to detect
Return code is 0
filtertest finished with RC: 0

> type detect
File Class:             8
Format Number:          Z7Z_Fmt (387)
Version:                400
Attributes:             1 (Encrypted)
Description:            7-Zip archive (7z)
MIME Type:              application/7z
```

> NOTE: A return code of `0` is a positive result. 

The password protect version returned `Attributes: 1` meaning `encrypted` per `ENdocAttributes` in `%KEYVIEW_HOME%\include\adinfo.h`.

## Conclusion
  
Knowing a files is encrypted is the next best thing to be able to decrypt and extract its contents.  The Filter SDK provides this level of detail for many file formats.

Relying on a file's extension to determine if and how to further process a given file is dangerous. You may treat gibberish text as plain text processing large amounts of it for no good reason.  Or you may unpack a zip file that is one of many other file formats and thus treat the many contained files as something interesting to process when in practice much more intelligence is required to exclude the noise and correctly parse the interesting bits.

Next, why not try more tutorials to explore some of the other features available in Filter SDK, linked from [here](../keyview_filter/README.md#capability-showcase).

## See also

- [Filter SDK C Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/index.html)
- [Filter SDK C++ Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/cpp-programming/index.html)
- [Filter SDK Java Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/java-programming/index.html)
- [Filter SDK .NET Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/dotnet-programming/index.html)
- [Filter SDK Python Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/python-programming/)
- [File Content Extraction Release Notes](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/IDOLReleaseNotes_25.4_Documentation/oem/Content/_KeyView.htm)
