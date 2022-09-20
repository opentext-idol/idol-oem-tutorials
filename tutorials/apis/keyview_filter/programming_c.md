# KeyView Filter SDK C API

As noted in the IDOL, KeyView and Eduction APIs [README.md](../README.md), the KeyView Filter SDK is designed to be embedded into other services.

To facilitate embedding, the KeyView Filter SDK has APIs for C, C++, Java and .Net.  In addition, the KeyView Filter SDK runs natively on the following platforms: Windows (x86_32, x86_64), Linux (x86_32, x86_64 and ARM_64), MacOS (x86_64 and Apple M*). 

In this lesson, you will:

- Familiarize yourself with the Filter SDK's C API
- Create a sample program that replicates a common use case of the Filter SDK

> NOTE: This guide assumes you have already completed the introductory KeyView Filter SDK [tutorial](../../keyview_filter/introduction.md#keyview-filter-sdk-introduction).

---

- [Setup](#setup)
  - [Resources](#resources)
  - [Environment and compilers](#environment-and-compilers)
    - [Compilers](#compilers)
  - [License key](#license-key)
- [API Setup](#api-setup)
  - [Building the sample program](#building-the-sample-program)
  - [Linking against KeyView Filter SDK](#linking-against-keyview-filter-sdk)
    - [Linking using GCC](#linking-using-gcc)
    - [Linking using Clang](#linking-using-clang)
    - [Linking using Visual Studio](#linking-using-visual-studio)
  - [Loading the Filter interface](#loading-the-filter-interface)
  - [Creating a Filter context](#creating-a-filter-context)
- [Filter a file](#filter-a-file)
  - [Filtering text](#filtering-text)
  - [Handling extended errors](#handling-extended-errors)
  - [Filtering hidden information](#filtering-hidden-information)
- [Changing functionality based on format](#changing-functionality-based-on-format)
  - [Detecting the file format](#detecting-the-file-format)
  - [Using file format information](#using-file-format-information)
  - [Checking if a file is supported](#checking-if-a-file-is-supported)
- [Retrieving metadata](#retrieving-metadata)
- [Extracting sub files](#extracting-sub-files)
  - [Loading the Extract interface](#loading-the-extract-interface)
  - [Opening a container](#opening-a-container)
  - [Extracting sub files](#extracting-sub-files-1)
  - [Retrieving mail metadata](#retrieving-mail-metadata)
- [Conclusion](#conclusion)
- [See also](#see-also)

---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

> NOTE: This lesson assumes you have already completed the [KeyView Filter SDK introduction](../../keyview_filter/introduction.md#keyview-filter-sdk-introduction) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic KeyView Filter concepts.

### Resources

Be sure to download the following resources before you continue:
- source code for this tutorial: [tutorial_file.c](../../../resources/apis/keyview_filter/tutorial_file.c)
-  optional sample files for detection and various extraction options located [here](../../../resources/keyview_filter/)

### Environment and compilers

#### Compilers

In order to create a program that uses KeyView, you will need to install a [supported compiler](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#Shared/_KV_Platform_Compilers.htm), and use it to build and link your program.

> NOTE: When building with the Visual Studio compiler, you will need to ensure you have opened the correct command prompt for the installed version – for example, ensuring you are using "x64 Native Tools Command Prompt" if you have installed the WINDOWS_X86_64 version of KeyView.

### License key

A KeyView license key is required to proceed with this lesson.  If you skipped the introduction setup step to acquire a license key, see [here](../../keyview_filter/introduction.md#activate-a-license-key).

## API Setup

### Building the sample program

In this tutorial, we will be gradually building a working tutorial program, which aims to replicate a common use case of the KeyView Filter SDK. Sample code for this program is provided, but the fpInitWithLicenseData call needs to be changed in order to compile.

Update the `tutorial.h` file with the following information:
- The values of YOUR_LICENSE_ORGANIZATION and YOUR_LICENSE_KEY will need to be replaced with the organization name and key from your license. 
- The YOUR_BIN_DIR variable needs to be changed to the location of the KeyView bin directory.

> NOTE: Refer to the `tutorial_file.c` source code for compilation tips.

### Linking against KeyView Filter SDK

Before we can get access to any KeyView functionality, we will first need to link against the kvfilter shared library. The resulting binary needs to be placed in the Filter bin directory (i.e. the directory containing kvfilter.so or kvfilter.dll), although the binary may be run from a different working directory. 

> **Security**: The advanced programming tutorial has some suggestions on security best practices, including how to mitigate against [DLL preloading attacks](programming_c_advanced.md#dll-pre-loading-attacks)

#### Linking using GCC

On Linux, you need to link against kvfilter.so, and also pass in the `–rpath $ORIGIN` option to the linker, e.g. `%KEYVIEW_HOME%/LINUX_X86_64/bin/kvfilter.so -Wl,-rpath,'$ORIGIN'`

> When called from within a makefile, $ORIGIN may need to be escaped to $$ORIGIN

#### Linking using Clang

On MacOS, you need to link against kvfilter.so, and also pass in the `–rpath @loader_path` option to the linker, e.g. `%KEYVIEW_HOME%/MACOS_X86_64/bin/kvfilter.so -Wl,-rpath,@loader_path`

#### Linking using Visual Studio

On Windows, you need to link against the import library for kvfilter.dll. This is provided as part of the KeyView Filter SDK, under {platform}/lib/kvfilter.lib.

### Loading the Filter interface

Now we can access KeyView functionality, we will need to include the required headers and load the interface functions from the kvfilter library, using [KV_GetFilterInterfaceEx()](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#C/filtering_functions/KV_GetFilterInterfaceEx.htm)

```c
#include "kvtypes.h"
#include "kvfilt.h"

KVFltInterfaceEx filter;
KVErrorCode error = KVERR_Success;

error = KV_GetFilterInterfaceEx(&filter, KVFLTINTERFACE_REVISION);

if(error != KVERR_Success)
{
    //return error;
}
```

This call fills out the interface structure, which contains the function pointers for the rest of Filter's functionality. 

Now that the interface has been successfully loaded, we are ready to use the KeyView Filter SDK.

### Creating a Filter context

All KeyView functionality requires a context pointer, which must be initialized at the start of processing, and shutdown at the end of processing.

```c
void* context = NULL;

context = filter.fpInitWithLicenseData(NULL, NULL,
    "/path/to/keyview/bin",
    "CompanyName", "24QD22D-2M6FV66-2KPF23S-2G8M59B",
     KVCS_UTF8, KVF_HEADERFOOTER);

if(!context) 
{
     //return error 
}

//Perform KeyView Functionality
        
filter.fpShutdown(context);
```

Initialization is done with the function [fpInitWithLicenseData()](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#C/filtering_functions/fpInitWithLicenseData.htm), which needs to be provided with the path to the KeyView bin folder, along with the company name and license string in your license.

> **Performance:** Multiple files can be processed in a single session, which may improve performance by reducing costs associated with start-up and shutdown.

> **Multi-threading:** To maximize throughput when processing multiple files, you may choose to call KeyView from multiple threads. All KeyView functions will be thread-safe when called in this manner, but each thread using KeyView must create its own context by call fpInitWithLicenseData. Filter contexts must not be shared between threads.

> **Security:** By default, KeyView will perform most of its operations out-of-process, creating a separate process to parse file data. This protects your main application from the effects of rare problems like memory leaks or crashes. Additional protection can be added by [running KeyView with reduced privileges](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#C/filter_api/Run_KeyView_Reduced_Privileges.htm).

Now that API setup is complete, we are able to perform KeyView Filter functionality on documents.

## Filter a file

A main aspect of KeyView is to filter text from documents and in this section we will learn how to get text from a file stored on disk.

### Filtering text

This can be done using the [fpFilterFile()](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#C/filtering_functions/fpFilterFile.htm) function.

```c
error = filter.fpFilterFile(context, pathToInputFile, pathToOutputFile, NULL);

if(error != KVERR_Success)
{
    //Return error
}
```

As with most KeyView functions, the first argument is the context we created earlier. We also need to provide the path to the input and output files.

> **Mail Files:** Mail files, such as EML or MSG, are considered a form of container, and cannot be filtered directly. We will learn more about how to filter mail files in [Extracting sub files](#extracting-sub-files).

### Handling extended errors

Until now we've only had to deal with basic errors, but we can receive additional error information by looking at extended errors. When the error returned is KVERR_General (or for some functions, FALSE) we should call the function [fpGetKvErrorCodeEx()](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#C/filtering_functions/fpGetKvErrorCodeEx.htm) to receive an additional error code with more information.

```c
if(error != KVERR_Success)
{
    if(error == KVERR_General)
    {
        return filter.fpGetKvErrorCodeEx(context);
    }

    return error;
}
```

We recommend that all error are handled this way, and will assume this is being done for the rest of this tutorial.

### Filtering hidden information

KeyView provides a number of options that control what text is output, and how that text is converted or displayed. One common requirement of KeyView is that it displays as much text as possible, including text that is not normally visible in the document, such as hidden cells or slides, or ancillary text like comments or notes. These can be displayed by enabling the hidden text option, using [fpFilterConfig()](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#C/filtering_functions/fpFilterConfig.htm).

```c
if(!filter.fpFilterConfig(context, KVFLT_SHOWHIDDENTEXT, TRUE, NULL))
{
    KVErrorCodeEx extError = filter.fpGetKvErrorCodeEx(context);
    
    return extError ? extError : KVERR_General;
}
```

## Changing functionality based on format

In many workflows, it may be necessary to change what operations are performed on a file based on its format. For example, you may only want KeyView to perform [OCR](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#filter_shared/OCR.htm) on PDF files, or need to provide security credentials for encrypted file. Alternatively, your own application may need to perform certain activities, like generating a user report, for certain file types. 

KeyView provides the ability to reliably determine the file format of a huge range of documents. This is done by analyzing the internal structure and content of file, rather than relying on file names or extensions. Detection prioritizes both accuracy and speed, only processing as much of the file as necessary to rule out false positives.

### Detecting the file format

This functionality is exposed through the API function [fpGetDocInfoFile()](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#C/filtering_functions/fpGetDocInfoFile.htm). This function returns FALSE on failure, rather than an error code, but more error information can still be obtained through the extended errors. Additionally, the [eClass of the structure](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#C/filtering_structures/ADDOCINFO.htm) will report if detection was unable to determine the format of the file.

```c
ADDOCINFO adInfo;
if(!filter.fpGetDocInfoFile(context, pathToInputFile, &adInfo))
{
    if(adInfo.eClass == AutoDetFail)
    {
        return KVERR_AutoDetFail;
    }
    else if(adInfo.eClass == AutoDetNoFormat)
    {
        return KVERR_AutoDetNoFormat;
    }
    else
    {
        return filter.fpGetKvErrorCodeEx(context);
    }
}
```

> **Source Code Detection:** KeyView can also provide detection of source code, attempting to identify the programming language that it is written in. You can learn more in [Source Code Identification](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#Shared/_KV_Code_Identification.htm).

### Using file format information

The [ADDOCINFO class](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#C/filtering_structures/ADDOCINFO.htm) contains the information KeyView was able to determine about the file: its format and version, the class of document it belongs to, and additional attributes such as encryption. This information can be used by your application to call handle files differently. For example:

```c
//Only enable OCR for PDFs
BOOL doOcr = adInfo.eFormat == PDF_Fmt; 
if(!filter.fpFilterConfig(context, KVFLT_OCR, doOcr, NULL))
{
    //Handle Error
}

//Restrict document version
if(adInfo.lVersion > 1000l)
{
    printf("Only version 1.0 is supported");
}

//Provide password for encrypted documents
if(adInfo.ulAttributes & kEncrypted)
{
    if(!filter.fpFilterConfig(context, KVFLT_SETSRCPASSWORD, 11, "password123"))
    {
        //Handle Error
    }
}
```

### Checking if a file is supported

KeyView provides a convenient function, [fpCanFilterFile()](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#C/filtering_functions/fpCanFilterFile.htm) for performing detection, and determining if the file can be passed to fpFilterFile().

```c
error = filter.fpCanFilterFile(context, pathToInputFile);
```

If this does not return success, the error returned will explain why the format cannot be filtered – for example, because KeyView could not determine the format, because the file doesn't exist, or because the format isn't supported for filtering.

While this step isn't strictly necessary, it can simplify many workflows.

## Retrieving metadata

> INSTRUCTIONS COMING SOON!

## Extracting sub files

KeyView Filter SDK allows access to sub files of a document, from both pure containers (such as zips or tars) and from documents embedded inside other files (such as an Excel spreadsheet embedded in a Word document).

### Loading the Extract interface

We can load the Extract interface by including the `kvxtract.h` header, and calling the [KVGetExtractInterface()](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#kv_xtract_functions/_KV_XTRACT_funct_KVGetExtractInterface.htm) function within the kvfilter shared library.

```c
#include "kvxtract.h"

KVExtractInterfaceRec extract;

KVStructInit(&extract);

error = KVGetExtractInterface (context, &extract);

if(error != KVERR_Success)
{
    //return error
}
```

The interface function takes the filter context we created earlier, as well as the interface to be filled out.

This code gives us our first introduction to the `KVStructInit()` macro. This ensures that a struct is correctly set up for use with the KeyView interface, including versioning information for backwards compatibility. Any KeyView struct containing a [KVStructHead](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#C/filtering_structures/KVStructHead.htm) member must be initialized with the `KVStructInit()` macro.

### Opening a container

Before we can access the sub files within a container, we first need to open the container. This is done using the [fpOpenFile()](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#kv_xtract_functions/_KV_XTRACT_funct_fpOpenFile.htm) function. This function creates a file-specific context pointer that we will use with the other functions in the extract interface. This context must be closed after use.

```c
void* fileContext = NULL;
KVOpenFileArgRec        openArg;

KVStructInit(&openArg);
openArg.extractDir = "path/to/extract/dir";
openArg.filePath = pathToInputFile;

error = extract.fpOpenFile(context, &openArg, &fileContext);

if(error != KVERR_Success)
{
	//Handle extended error as above
}

extract.fpCloseFile(fileContext);
```

KeyView can then get information about the container itself using the function [fpGetMainFileInfo()](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#kv_xtract_functions/_KV_XTRACT_funct_fpGetMainFileInfo.htm). Most importantly, this will tell us the number of sub files. This struct must also be freed after use.

```c
KVMainFileInfo          fileInfo = NULL;

error = extract.fpGetMainFileInfo(fileContext, fileInfo);

if(error != KVERR_Success)
{
	//Handle extended error as above
}

//Use main file info

Extract.fpFreeStruct(fileContext, fileInfo);
```

### Extracting sub files

Before we extract the sub file itself, we first need to get some information about the sub file. This is done by calling the [fpGetSubFileInfo()](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#kv_xtract_functions/_KV_XTRACT_funct_fpGetSubFileInfo.htm) function, using the index to identify the sub file. This structure must also be freed after use.

```c
for(int ii = 0; ii < fileInfo->numSubFiles; ++ii)
{
    KVSubFileInfo subFileInfo = NULL;
    error = extract.fpGetSubFileInfo(fileContext, ii, &subFileInfo);

    if(error != KVERR_Success)
    {
        //Handle extended error as above
    }

    //Use sub file info
    
    extract.fpFreeStruct(fileContext, subFileInfo);
}
```

Once we have this sub file info, we can use it to construct the necessary arguments for extraction.

```c
KVSubFileExtractInfo extractInfo = NULL;
KVExtractSubFileArgRec extractArg;
KVStructInit(&extractArg);

if(subFileInfo->subFileType == KVSubFileType_Folder ||
    subFileInfo->subFileType == KVSubFileType_External)
{
    goto skipfile;
}

extractArg.index = ii;
extractArg.extractionFlag = KVExtractionFlag_CreateDir | KVExtractionFlag_Overwrite;
extractArg.filePath = subFileInfo->subFileName;

error = extract.fpExtractSubFile(fileContext, &extractArg, &extractInfo);

if(error)
{
    //Handle extended error as above
}

//Do more processing, such as filtering the sub file

extract.fpFreeStruct(fileContext, extractInfo);
```

The [fpExtractSubFile()](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#kv_xtract_functions/_KV_XTRACT_funct_fpExtractSubFile.htm) function fills out the KVSubFileExtractInfo pointer, which tells us more information about what the function actually did – for example, the actual location it extracted the file to.

> **Mail Files:** In KeyView, mail files are treated as containers, where the first sub file is the contents of the mail file, and subsequent sub files are the attachments. 

By default, images are not extracted when extracting sub files. These can be enabled with the [fpFilterConfig()](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#C/filtering_functions/fpFilterConfig.htm) function we used earlier. As before, this is set globally for the session, so can be outside of the loop used to process files.

```c
if(!filter.fpFilterConfig(context, KVFLT_EXTRACTIMAGES, TRUE, NULL))
{
    KVErrorCodeEx extError = filter.fpGetKvErrorCodeEx(context);
    
    return extError ? extError : KVERR_General;
}
```

### Retrieving mail metadata

KeyView can retrieve mail metadata for a particular sub file using the function [fpGetSubFileMetaData()](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#kv_xtract_functions/_KV_XTRACT_funct_fpGetSubFileMetaData.htm). This function has a number of options for retrieving different subsets of the mail metadata. We will use the option to retrieve all metadata, by passing -1 to the metaNameCount.

```c
KVSubFileMetaData metadata = NULL;
KVGetSubFileMetaArgRec metaArg;
KVStructInit(&metaArg);
metaArg.index = ii;
metaArg.trgCharset = KVCS_UTF8;
metaArg.metaNameCount = -1;

error = extract.fpGetSubFileMetaData(fileContext, &metaArg, &metadata);

if(error)
{
    //Handle extended error as above
}
```

KeyView can then output the metadata in a similar way to Summary Information.

```c
for(int ii=0; ii < metadata->nElem; ++ii)
{
    KVMetadataElem* element = metadata->ppElem[ii];
    
    if(element == NULL || !element->isDataValid)
    {
        continue;
    }
    fprintf(fpOut, "%s (0x%8X): ", element->strType, element->dataID);

    switch(element->type)
    {
    case KVMetadata_Int4:
        //data contains an actual int, not a pointer
        fprintf(fpOut, "%d", (int)element->data); 
        break;
    case KVMetadata_Bool:
        //NULL pointer is false, true otherwise
        fprintf(fpOut, "%s", element->data ? "true" : "false");
        break;
    case KVMetadata_Double:
        //Pointer to double
        fprintf(fpOut, "%lf", *(double*)element->data);
        break;
    case KVMetadata_Float:
        //Pointer to float
        fprintf(fpOut, "%lf", *(float*)element->data);
        break;
    case KVMetadata_DateTime:
    {
        //Pointer to Windows file time
        //That is, 64-bit value representing 100-nanosecond intervals since 1601-01-01T00:00 UTC
        const long long intervalsPerSecond = 10000000LL;
        const long long windowsToUnixSeconds = 11644473600LL;
        time_t unixTime = (*(long long*)element->data / intervalsPerSecond) - windowsToUnixSeconds;
        fprintf(fpOut, "%s", asctime(localtime(&unixTime)));
        break;
    }
    case KVMetadata_String:
        //Null-terminated C-string
        fprintf(fpOut, "%s", (char*)element->data);
        break;
    case KVMetadata_Unicode:
        //Null-terminated wide C-string
        fprintf(fpOut, "%ls", (unsigned short*)element->data);
        break;
    case KV_Binary:
        //Byte array
        fprintf(fpOut, "%.*s", (unsigned char*)element->data);
        break;
    default:
        fprintf(fpOut, "Value could not be interpreted");
        break;
    }
}
```

## Conclusion

You should now have built a basic sample program, processing documents using file mode. To learn about more advanced features, such as processing files in stream mode, take a look at the [Advanced Tutorial](./programming_c_advanced.md#keyview-filter-sdk-c-api-advanced-topics)

And if you haven't already done so, why not try more tutorials to explore some of the other features available in KeyView Filter SDK, linked from the [main page](../../README.md#keyview-filter-sdk-showcase).

## See also

- [KeyView Filter SDK C Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html)
