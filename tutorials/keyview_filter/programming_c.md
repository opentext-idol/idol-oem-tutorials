# Filter SDK C API

The Filter SDK allows you to embed file content extraction functionality into other services.

To facilitate embedding, the Filter SDK has APIs for C, C++, Java, .NET and Python.  In addition, the Filter SDK runs natively on the following platforms: Windows (x86_32, x86_64, ARM_64), Linux (x86_32, x86_64 and ARM_64), MacOS (x86_64 and Apple M*).

In this lesson, you will:

- Familiarize yourself with the Filter SDK's C API
- Create a sample program that replicates a common use case of the Filter SDK

> NOTE: This guide assumes you have already completed the [Filter SDK introduction](./introduction.md#introduction-to-filter-sdk) lesson.

---

- [Setup](#setup)
  - [Resources](#resources)
  - [Environment and compilers](#environment-and-compilers)
    - [Compilers](#compilers)
  - [License key](#license-key)
- [API Setup](#api-setup)
  - [Building the sample program](#building-the-sample-program)
  - [Linking against Filter SDK](#linking-against-filter-sdk)
    - [Linking using GCC](#linking-using-gcc)
    - [Linking using Clang](#linking-using-clang)
    - [Linking using Visual Studio](#linking-using-visual-studio)
  - [Loading the Filter interface](#loading-the-filter-interface)
  - [Creating a Filter session](#creating-a-filter-session)
- [Opening a document](#opening-a-document)
- [Filter a file](#filter-a-file)
  - [Filtering text](#filtering-text)
  - [Filtering hidden information](#filtering-hidden-information)
- [Changing functionality based on format](#changing-functionality-based-on-format)
  - [Detecting the file format](#detecting-the-file-format)
  - [Using file format information](#using-file-format-information)
  - [Checking if a file is supported](#checking-if-a-file-is-supported)
- [Retrieving metadata](#retrieving-metadata)
  - [Getting the metadata list](#getting-the-metadata-list)
  - [Iterating through the list](#iterating-through-the-list)
  - [Interpreting a metadata element](#interpreting-a-metadata-element)
  - [Standardized metadata elements](#standardized-metadata-elements)
- [Extracting sub files](#extracting-sub-files)
  - [Loading the Extract interface](#loading-the-extract-interface)
  - [Opening a container](#opening-a-container)
  - [Sub file extraction](#sub-file-extraction)
  - [Retrieving mail metadata](#retrieving-mail-metadata)
- [Build \& Run](#build--run)
  - [Build](#build)
  - [Run](#run)
- [Conclusion](#conclusion)
- [See also](#see-also)

---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

> NOTE: This lesson assumes you have already completed the [Filter SDK introduction](./introduction.md#introduction-to-filter-sdk) lesson covering essential setup steps (for example, required downloads and installation steps) and basic Filter SDK concepts.

### Resources

You must download the following resources before you continue:

- source code for this tutorial: [tutorial_file.c](../../resources/keyview_filter/sdk/C/tutorial_file.c)
- optional sample files for detection and various extraction options located [here](../../resources/keyview_filter)

### Environment and compilers

#### Compilers

To create a program that uses the Filter SDK, you need to install a [supported compiler](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/Shared/_KV_Platform_Compilers.htm), and use it to build and link your program.

> NOTE: When you build with the Visual Studio compiler, you must ensure you have opened the correct command prompt for the installed version. For example, if you have installed the WINDOWS_X86_64 version of the Filter SDK, ensure you use "x64 Native Tools Command Prompt".

### License key

You need a Filter SDK license key to proceed with this lesson.  If you skipped the introduction setup step to acquire a license key, see [here](./introduction.md#activate-a-license-key).

## API Setup

### Building the sample program

In this tutorial, you will gradually build a working tutorial program, which aims to replicate a common use case of the Filter SDK. Sample code for this program is provided, but you must modify the fpInit call for the sample to compile.

Update the `tutorial.h` file with the following information:

- Replace the values of YOUR_LICENSE_KEY with your license.
- Change the YOUR_BIN_DIR variable to the location of the Filter SDK bin directory.

> NOTE: Refer to the `tutorial_file.c` source code for compilation tips.

### Linking against Filter SDK

To get access to the Filter SDK functionality, you must first link against the kvfilter shared library. You must place the resulting binary in the Filter bin directory (that is, the directory containing kvfilter.so or kvfilter.dll), although you can run the binary from a different working directory.

> **Security**: Loading shared libraries can expose your application to attacks. The Filter SDK documentation offers advice on [avoiding DLL preloading attacks](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/kv_security/_KV_DLLPreloading.htm)

#### Linking using GCC

On Linux, you must link against kvfilter.so, and also pass in the `–rpath $ORIGIN` option to the linker. For example, `%KEYVIEW_HOME%/LINUX_X86_64/bin/kvfilter.so -Wl,-rpath,'$ORIGIN'`

> When you call it from inside a makefile, you might need to escape \$ORIGIN to $$ORIGIN

#### Linking using Clang

On MacOS, you must link against kvfilter.so, and also pass in the `–rpath @loader_path` option to the linker. For example, `%KEYVIEW_HOME%/MACOS_X86_64/bin/kvfilter.so -Wl,-rpath,@loader_path`

#### Linking using Visual Studio

On Windows, you must link against the import library for kvfilter.dll. This library is provided as part of the Filter SDK, under {platform}/lib/kvfilter.lib.

### Loading the Filter interface

Now that you can access the Filter SDK functionality, you must include the required headers and load the interface functions from the kvfilter library, using [KV_GetFilterInterfaceEx()](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/C/filtering_functions/KV_GetFilterInterfaceEx.htm)

```c
#include "kvtypes.h"
#include "kvfilt.h"

KVFltInterfaceEx filter;

KVErrorCode error = KV_GetFilterInterfaceEx(&filter, KVFLTINTERFACE_REVISION);

if(error != KVError_Success)
{
    //return error;
}
```

This call fills out the interface structure, which contains the function pointers for the rest of Filter's functionality.

Like most Filter SDK functions, KV_GetFilterInterfaceEx() return a KVErrorCode. If this is KVError_Success, then the function succeeded. Otherwise, the error code indicates the problem that occurred. The rest of the tutorial assumes that you check the error code after each function call.

Now that you have successfully loaded the interface, you are ready to use the Filter SDK.

### Creating a Filter session

All Filter SDK functionality requires a session, which you must initialize at the start of processing, and shut down at the end of processing.

```c
KVFilterSession session = NULL;

KVFilterInitOptions options;
KVStructInit(&options);
options.outputCharSet = KVCS_UTF8;

error = filter.fpInit(
    "/path/to/filterSDK/bin",
    YOUR_LICENSE_KEY,
    &options,
    &session);

//Perform Filter SDK Functionality
        
filter.fpShutdown(session);
```

You initialize by using the function [fpInit()](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/C/filtering_functions/fpInit.htm), which you must provide with the path to the Filter SDK bin folder, and your license key.

This function also takes a pointer to a KVFilterInitOptions structure, which you must initialize using KVStructInit(). This macro ensures that a struct is correctly set up for use with the Filter SDK interface, including versioning information for backwards compatibility. Any Filter SDK struct that contains a [KVStructHead](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/C/filtering_structures/KVStructHead.htm) member must be initialized with the `KVStructInit()` macro.

> **Performance**
>
> _Session Lifetime:_ You can process multiple files in a single session, which might improve performance by reducing costs associated with start-up and shutdown.
>
> _Multi-threading:_ To maximize throughput when processing multiple files, you can call the Filter SDK from multiple threads. All Filter SDK functions are thread-safe when called in this manner, but each thread using the Filter SDK must create its own session by calling fpInit(). You must not share filter sessions between threads.

> **Security**
>
> _Privilege Reduction:_ By default, the Filter SDK performs most of its operations out-of-process, creating a separate process to parse file data. This protects your main application from the effects of rare problems like memory leaks or crashes. You can include additional protection by [running the Filter SDK with reduced privileges](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/kv_security/_KV_RunMinimalPrivileges.htm).
>
> _Temp Directory:_ While processing, the Filter SDK might place sensitive data in the temporary directory. You might want to consider [protecting the temporary directory](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/kv_security/_KV_ProtectTempDir.htm)

Now that you have set up the API, you can perform the Filter SDK functionality on documents.

## Opening a document

The Filter SDK functions operate on a KVDocument object, which is a representation of a document that is agnostic as to where the document actually lives. You can create a KVDocument from a file on disk by using fpOpenDocumentFromFile. You must close the KVDocument after use.

```c
KVDocument document = NULL;

error = filter.fpOpenDocumentFromFile(session, pathToInputFile, &document);

//Pass document to the Filter SDK functions

filter.fpCloseDocument(document);
```

## Filter a file

One of the most important features of the Filter SDK is filtering text from a document. This section shows you how to get text from a KVDocument object, and output it to a file on disk.

### Filtering text

You can filter text to an output file by using the [fpFilterToFile()](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/C/filtering_functions/fpFilterToFile.htm) function.

```c
error = filter.fpFilterToFile(document, pathToOutputFile);
```

> **Partial Filtering:** The fpFilterToFile() function filters the entire file in one go, but you might want to filter only part of the file, or filter the file in chunks. The advanced tutorial covers how to do [partial filtering](./programming_c_advanced.md#partial-filtering).

> **Mail Files:** Mail files, such as EML or MSG, are considered a form of container, and you cannot filter them directly. You will learn more about how to filter mail files in [Extracting sub files](#extracting-sub-files).

### Filtering hidden information

The Filter SDK provides a number of options that control what text to output, and how to convert or display that text. A common requirement of the Filter SDK is to display as much text as possible, including text that is not normally visible in the document, such as hidden cells or slides, or ancillary text like comments or notes. You can display this text by enabling the hidden text option in [fpSetConfig()](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/C/filtering_functions/fpSetConfig.htm).

```c
error = filter.fpSetConfig(session, KVFLT_SHOWHIDDENTEXT, TRUE, NULL);
```

## Changing functionality based on format

In many workflows, you might need to change what operations to perform on a file based on its format. For example, you might want the Filter SDK to perform [OCR](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/filter/OCR.htm) only on PDF files, or you might need to provide security credentials for encrypted files. Alternatively, your own application might need to perform certain activities, like generating a user report, for certain file types. 

The Filter SDK enables you to reliably determine the file format of a huge range of documents. It does this by analyzing the internal structure and content of the file, rather than relying on file names or extensions. Detection prioritizes both accuracy and speed, only processing as much of the file as necessary to rule out false positives.

### Detecting the file format

File format detection functionality is exposed through the API function [fpGetDocInfo()](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/C/filtering_functions/fpGetDocInfo.htm).

```c
ADDOCINFO adInfo;
error = filter.fpGetDocInfo(document, &adInfo);
```

> **Source Code Identification:** The Filter SDK can optionally detect source code, attempting to identify the programming language that it is written in. You can learn more in [Source Code Identification](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/Shared/_KV_Code_Identification.htm).

### Using file format information

The [ADDOCINFO class](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/C/filtering_structures/ADDOCINFO.htm) contains the information the Filter SDK was able to determine about the file: its format and version, the class of document it belongs to, and additional attributes such as encryption. Your application can use this information to handle files differently. For example:

```c
//Only enable OCR for PDFs
BOOL doOcr = (adInfo.eFormat == PDF_Fmt); 
error = filter.fpSetConfig(session, KVFLT_OCR, doOcr, NULL);

//Restrict document version
if(adInfo.lVersion > 1000l)
{
    printf("Only version 1.0 is supported");
}

//Provide password for encrypted documents
if(adInfo.ulAttributes & kEncrypted)
{
    error = filter.fpSetConfig(session, KVFLT_SETSRCPASSWORD, 11, "password123");
}
```

### Checking if a file is supported

The Filter SDK provides a convenience function, [fpCanFilter()](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/C/filtering_functions/fpCanFilter.htm) that performs detection and determines if you can pass the file to fpFilterFile().

```c
error = filter.fpCanFilter(document);
```

If this function does not return KVError_Success, the error returned explains why the Filter SDK cannot filter the format – for example, because the Filter SDK could not determine the format, because the file does not exist, or because the format is not supported for filtering.

While this step is not strictly necessary, it can simplify many workflows.

## Retrieving metadata

File formats can contains a variety of different metadata, and the Filter SDK makes it easy to access all of this information. The Filter SDK retrieves metadata from various sources in a file, such as:

- Format-specific standard metadata
- User-provided custom metadata
- Exif tags
- XMP elements
- MIP Labels

### Getting the metadata list

You can retrieve metadata elements by using [fpGetMetadataList()](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/C/filtering_functions/fpGetMetadataList.htm). This function fills out the [KVMetadataList](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/C/metadata/KVMetadataList.htm) structure, which you must free by using its fpFree function.

```c
const KVMetadataList* metadataList = NULL;
error = filter.fpGetMetadataList(document, &metadataList);

//Iterate through metadata

metadataList->fpFree(metadataList);
```

### Iterating through the list

You can retrieve individual metadata elements by iterating through the metadata list using KVMetadataList's fpGetNext() function, which fills out the [KVMetadataElement](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/C/metadata/KVMetadataElement.htm) structure. The information that this structure returns is valid only while the session is still alive, and becomes invalid after you call fpFree(). The end of the list is indicated by the retrieved element being NULL.

```c
while(1)
{
    const KVMetadataElement* element = NULL;
    error = metadataList->fpGetNext(metadataList, &element);
    
    if(error != KVError_Success)
    {
        //Handle error
    }
    
    if(element == NULL)
    {
        break;
    }
    
    //Process metadata element
}
```

### Interpreting a metadata element

Each metadata element is conceptually represented as a key-value pair, where pKey is the name of the metadata key, and pValue is the value of that piece of metadata. To know the type of the metadata object the pValue points to, you must first consult the eType member. Strings are output in the character set that you requested in the call to [fpInit()](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/C/filtering_functions/fpInit.htm).

```c
fprintf(fpOut, "%s: ", element->pName);
switch (element->eType)
{
case KVMetadataValue_Bool:
{
    BOOL value = *(BOOL*)element->pValue;
    //Process Bool value
    break;
}
case KVMetadataValue_Int64:
{
    int64_t value = *(int64_t*)element->pValue;
    //Process Int64 value
    break;
}
case KVMetadataValue_Double:
{
    double value = *(double*)element->pValue;
    //Process Doube value
    break;
}
case KVMetadataValue_WinFileTime:
{
    int64_t value = *(int64_t*)element->pValue;
    //Process WinFileTime value
    break;
}
case KVMetadataValue_String:
{
    KVString value = *(KVString*)element->pValue;
    //Process String value
    break;
}
case KVMetadataValue_Binary:
{
    KVBinary value = *(KVBinary*)element->pValue;
    //Process Binary value
    break;
}
case KVMetadataValue_MIPLabel:
{
    KVMIPLabel value = *(KVMIPLabel*)element->pValue;
    //Process MIPLabel value
    break;
}
default:
    //Handle unrecognised type
    break;
}
```

### Standardized metadata elements

Different file formats can store the same piece of information in different ways. For example, one file format might call the width of the image "width", another "image_width", and another "x_size". This behavior is often unhelpful, because you then need to maintain a list of fields that correspond to a particular piece of information. The Filter SDK solves this problem by [standardizing certain metadata fields](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/metadata/_KV_What_Is_Metadata.htm). 

## Extracting sub files

The Filter SDK allows access to sub files of a document, from both pure containers (such as zips or tars) and from documents embedded inside other files (such as an Excel spreadsheet embedded in a Word document).

### Loading the Extract interface

You can load the Extract interface by including the `kvxtract.h` header, and calling the [fpGetExtractInterface()](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/C/filtering_functions/fpGetExtractInterface.htm) function in the kvfilter shared library.

```c
#include "kvxtract.h"

KVExtractInterfaceRec extract;

KVStructInit(&extract);

error = filter.fpGetExtractInterface(session, &extract);
```

The interface function takes the filter session you created earlier, as well as the extraction interface to fill out.

### Opening a container

You must open a container file before you can access the sub files. You open the container by using the [fpOpenFileFromFilterSession()](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/C/extract/fpOpenFileFromFilterSession.htm) function. This function creates a file-specific context pointer that you can use with the other functions in the extract interface. You must close this context after use.

```c
void* fileContext = NULL;
KVOpenFileArgRec        openArg;

KVStructInit(&openArg);
openArg.extractDir = "path/to/extract/dir";
openArg.document = document;

error = extract.fpOpenFileFromFilterSession(session, &openArg, &fileContext);

extract.fpCloseFile(fileContext);
```

You can then get information about the container itself by using the function [fpGetMainFileInfo()](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/C/extract/fpGetMainFileInfo.htm). Most importantly, this tells you the number of sub files. You must free this structure after use.

```c
KVMainFileInfo          fileInfo = NULL;

error = extract.fpGetMainFileInfo(fileContext, fileInfo);

//Use main file info

Extract.fpFreeStruct(fileContext, fileInfo);
```

### Sub file extraction

Before you extract the sub file itself, you must first get some information about the sub file. You get this information by calling the [fpGetSubFileInfo()](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/C/extract/fpGetSubFileInfo.htm) function, using the index to identify the sub file. You must free this structure after use.

```c
for(int ii = 0; ii < fileInfo->numSubFiles; ++ii)
{
    KVSubFileInfo subFileInfo = NULL;
    error = extract.fpGetSubFileInfo(fileContext, ii, &subFileInfo);

    //Use sub file info
    
    extract.fpFreeStruct(fileContext, subFileInfo);
}
```

After you have this sub file info, you can use it to construct the necessary arguments for extraction.

```c
KVSubFileExtractInfo extractInfo = NULL;
KVExtractSubFileArgRec extractArg;
KVStructInit(&extractArg);

if(subFileInfo->subFileType == KVSubFileType_Folder ||
    subFileInfo->subFileType == KVSubFileType_External)
{
    goto skipfile;
}

extractArg.index = index;
extractArg.filePath = subFileInfo->subFileName;
extractArg.extractionFlag = 
    KVExtractionFlag_CreateDir | 
    KVExtractionFlag_Overwrite | 
    KVExtractionFlag_GetFormattedBody | 
    KVExtractionFlag_SanitizeAbsolutePaths;

error = extract.fpExtractSubFile(fileContext, &extractArg, &extractInfo);

//Do more processing, such as filtering the sub file

extract.fpFreeStruct(fileContext, extractInfo);
```

The [fpExtractSubFile()](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/C/extract/fpExtractSubFile.htm) function fills out the KVSubFileExtractInfo pointer, which tells you more about what the function actually did – for example, the location it extracted the file to.

> **Mail Files:** The Filter SDK treats mail files as containers, where the first sub file is the contents of the mail file, and subsequent sub files are the attachments.

> **Security:** KVExtractionFlag_SanitizeAbsolutePaths mitigates against certain path traversal attacks. You can read more in [Sanitize Absolute Paths](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/extract/Sanitize_paths.htm)

By default, the Filter SDK does not extract images when extracting sub files. You can enable image extraction by using the [fpSetConfig()](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/C/filtering_functions/fpSetConfig.htm) function we used earlier. This option is set globally for the session, so you can set it outside of the loop that you use to process files.

```c
error = filter.fpSetConfig(session, KVFLT_EXTRACTIMAGES, TRUE, NULL);
```

### Retrieving mail metadata

You can retrieve mail metadata for a particular sub file using the function [fpGetSubFileMetaDataList()](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/C/extract/fpGetSubFileMetadataList.htm). This function fills out the same KVMetadataList structure that you used in [Retrieving metadata](#retrieving-metadata), and can be handled in the same way. You must initialize [KVGetSubfileMetadataListArgRec](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/Content/C/extract/KVGetSubFileMetadataListArg.htm) using KVStructInit().

```c
const KVMetadataList* metadataList = NULL;

KVGetSubfileMetadataListArgRec metaArgs;
KVStructInit(&metaArgs);
metaArgs.index = index;
metaArgs.trgCharset = KVCS_UTF8;

error = extract.fpGetSubfileMetadataList(fileContext, &metaArg, &metadataList);

//Process metadata using metadataList->fpGetNext()

metadataList->fpFree(metadataList);
```

## Build & Run

### Build

1. Copy the `idol-oem-tutorials\resources\keyview_filter\sdk\tutorial` folder to `%KEYVIEW_HOME%\samples\tutorial`.  The provided makefile(s) leverage components of the samples' makefile where relative paths are used.
2. Use the provided makefile to build `*e.g.* nmake tutorial_file_win_x86_64.mak`
3. The `%KEYVIEW_HOME%\samples\tutorial` folder will have bin folder containing 

### Run

Since `tutorial.h` specified the `YOUR_BIN_DIR` for the Filter SDK, you can run the built exe from the `bin` folder as shown below:
```sh
> cd C:\OpenText\KeyviewFilterSDK_25.4.0_WINDOWS_X86_64\samples\tutorial\bin
> set PATH=C:\OpenText\KeyviewFilterSDK_25.4.0_WINDOWS_X86_64\WINDOWS_X86_64\bin
> tutorial_file ..\..\..\..\idol-oem-tutorials\resources\keyview_filter\KeyViewFilterSDK_12.13.0_ReleaseNotes_en.pdf out
```

The `out` file will have the text from the input PDF file.

For extra credit, try with your own input file(s) and/or the others provided with this tutorial.

## Conclusion

You have now built a basic sample program, processing documents using file mode. To learn about more advanced features, such as processing files in stream mode, take a look at the [Advanced Tutorial](./programming_c_advanced.md)

Next, why not try more tutorials to explore some of the other features available in Filter SDK, linked from [here](../keyview_filter/README.md#capability-showcase).

## See also

- [Filter SDK C Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/c-programming/index.html)
- [Filter SDK C++ Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/cpp-programming/index.html)
- [Filter SDK Java Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/java-programming/index.html)
- [Filter SDK .NET Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/dotnet-programming/index.html)
- [Filter SDK Python Programming Guide](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/KeyviewFilterSDK_25.4_Documentation/Guides/html/python-programming/)
- [File Content Extraction Release Notes](https://www.microfocus.com/documentation/idol/knowledge-discovery-25.4/IDOLReleaseNotes_25.4_Documentation/oem/Content/_KeyView.htm)

