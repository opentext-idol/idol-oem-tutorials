# Microsoft RMS Files

The Microsoft Rights Management Service (RMS) allows you to classify and optionally encrypt documents. This service forms the rights management part of Microsoft Azure Information Protection (AIP).

For many of the files that Azure RMS can classify and encrypt, the Filter SDK can identify whether they have been encrypted with RMS encryption. It can also extract metadata (including the RMS classification) and XrML associated with the document.  Document decryption is also supported.

In this lesson, you will:

- perform detection on a RMS protected file
- extract metadata from a RMS protected file
- extract XrML metadata from a RMS protected file
- attempt to extract text from a RMS protected file

> NOTE: This guide assumes you have already completed the [Filter SDK introduction](./introduction.md#introduction-to-filter-sdk) lesson.

---

- [Setup](#setup)
  - [Resources](#resources)
- [Perform detection](#perform-detection)
- [Extract metadata](#extract-metadata)
- [Extract XrML](#extract-xrml)
- [Extract text](#extract-text)
- [Conclusion](#conclusion)
- [See also](#see-also)

---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

> NOTE: This lesson assumes you have already completed the [Filter SDK introduction](../keyview_filter/introduction.md) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic Filter SDK concepts.

### Resources

Be sure to download the following resources before you continue:

- sample documents from [here](../../resources/keyview_filter/) and install to `C:\OpenText\idol-oem-tutorials\resources`

## Perform detection

As you have likely already done in other lessons, let's run `filtertest -ah` to perform automatic format detection.

```sh
> cd C:\OpenText\KeyviewFilterSDK_25.4.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> filtertest -ah ..\..\..\idol-oem-tutorials\resources\keyview_filter\keyview_confidential_RMS.docx detect
WARNING: filtertest is a sample program only and is not for production use
autodetect:  ..\..\..\idol-oem-tutorials\resources\keyview_filter\keyview_confidential_RMS.docx to detect
Return code is 0
filtertest finished with RC: 0

> type detect
File Class:             12
Format Number:          370
Version:                0
Attributes:             33 (Encrypted, WindowRMSEncrypted)
Description:            Office 2007 document that cannot be further classified (often RMS-encrypted)
MIME Type:              -

```

> NOTE: A return code of `0` is a positive result.

The input file is a protected Microsoft Word file, so a `Format ID: 370` is correct - indicating that it's an Office document that cannot be further classified.  If the Word document was RMS classified, but not protected then a more precise format classification is possible.  See the [Supported Formats](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/kv_RMS/_KV_RMS_support.htm) documentation for more details.

Besides the `Format ID`, the `Attributes: 33` data provides extra insights into this file.  The attributes are a bit mask with `1` indicating the file is `encrypted` and `32`  indicating the file is `RMS encrypted`.  Refer to `%KEYVIEW_HOME%\include\adinfo.h` for more details on document attributes.

## Extract metadata

As you likely have already done in other lessons, let's run `filtertest -m` to extract the document metadata.

```sh
> cd C:\OpenText\KeyviewFilterSDK_25.4.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> filtertest -m ..\..\..\idol-oem-tutorials\resources\keyview_filter\keyview_confidential_RMS.docx metadata
WARNING: filtertest is a sample program only and is not for production use
filtertest: ..\..\..\idol-oem-tutorials\resources\keyview_filter\keyview_confidential_RMS.docx to metadata
Return code is 0
filtertest finished with RC: 0
```

>> NOTE: A return code of `0` is a positive result.  Use your UTF-8 capable text editor, so you can properly view the output - just in case complex character sets are represented in the test document.

Even though the file is RMS protected, the document metadata can still be extracted.  Typical office-style document metadata is extracted, but the additionally extracted classification tags should also be of interest to determine what to do with or to simply find this document.

## Extract XrML

To facilitate decryption of RMS protected documents, an XrML document is embedded into the file.  The Filter SDK considers the XrML file a sub-file.  So let's use `tstxtract` to extract it.

```sh
> cd C:\OpenText\KeyviewFilterSDK_25.4.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> rmdir /s _extract
> mkdir _extract
> tstxtract ..\..\..\idol-oem-tutorials\resources\keyview_filter\keyview_confidential_RMS.docx _extract
WARNING: tstxtract is a sample program only and is not for production use
File ..\..\..\idol-oem-tutorials\resources\keyview_filter\keyview_confidential_RMS.docx has 1 sub files, charset: 0, format: 370
tstxtract return code: 0
```

> NOTE: `return code: 0` is a positive result equivalent to `KVERR_Success`.

A single sub-file `_extract\subfile_kv0.tmp` is extracted.  The XrML content contains additional metadata that can be used to decrypt the document.  The Filter SDK and Panopticon both support decryption of Microsoft RMS protected files.  However, decryption is not currently part of this lesson.

## Extract text

Let's see what happens when we try to extract text from a RMS protected file, but without providing any credentials.

``` sh
> cd C:\OpenText\KeyviewFilterSDK_25.4.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> filtertest ..\..\..\idol-oem-tutorials\resources\keyview_filter\keyview_confidential_RMS.docx text
fpFilterToFile() error: ..\..\..\idol-oem-tutorials\resources\keyview_filter\keyview_confidential_RMS.docx
filtertest: Target CharSet is 53
Return code is 51
filtertest finished with RC: 51
```

Per `%KEYVIEW_HOME%\include\kverrorcodes.h` an `51` is `KVError_RMSCredentialsRequired`.  This is the expected response since no credentials where provided to decrypt the RMS protected document.

If proper credentials were provided and the Azure decryption service could be reached, then text would be attempted to be extracted from the temporary decrypted file.  See [Filter SDK Programming Guide- fpConfigureRMS()](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/kv_RMS/_KV_RMS_fpConfigureRMS.htm)

## Conclusion

With the Filter SDK supporting Microsoft RMS classified & protected files more content is available for downstream processing.

Next, why not try more tutorials to explore some of the other features available in Filter SDK, linked from [here](../keyview_filter/README.md#capability-showcase).

## See also

- [Filter SDK C Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/index.html)
- [Filter SDK C++ Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/cpp-programming/index.html)
- [Filter SDK Java Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/java-programming/index.html)
- [Filter SDK .NET Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/dotnet-programming/index.html)
- [Filter SDK Python Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/python-programming/)
- [File Content Extraction Release Notes](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/IDOLReleaseNotes_25.4_Documentation/oem/Content/_KeyView.htm)
- [Wikipedia - XrML](https://en.wikipedia.org/wiki/XrML)
- [Microsoft - What is Azure Information Protection](https://learn.microsoft.com/en-us/azure/information-protection/what-is-information-protection)
