# KeyView Filter SDK C API Advanced Topics

This lesson follows on from the [previous tutorial](./programming_c.md#keyview-filter-sdk-c-api)

In this lesson, you will:
- familiarize yourself with more advanced Filter SDK functionality.
- adapt the previous sample program to work on streams, rather than files.

> NOTE: This guide assumes you have already completed the introductory KeyView Filter SDK [tutorial](introduction.md#keyview-filter-sdk-introduction).

> NOTE: This lesson assumes you have also already completed the KeyView Filter SDK C API [tutorial](./programming_c.md).

---
- [Setup](#setup)
  - [Resources](#resources)
- [Using a custom stream](#using-a-custom-stream)
  - [Defining a custom stream](#defining-a-custom-stream)
  - [Opening a document from a stream](#opening-a-document-from-a-stream)
  - [Extracting subfiles using streams](#extracting-subfiles-using-streams)
- [Partial filtering](#partial-filtering)
- [Build \& Run](#build--run)
  - [Build](#build)
  - [Run](#run)
- [Conclusion](#conclusion)
- [See also](#see-also)

---

## Setup

### Resources

Download the following resources before you continue:
- source code for this tutorial: [tutorial_stream.c](../../resources/keyview_filter/sdk/C/tutorial_stream.c)
- optional sample files for detection and various extraction options located [here](../../resources/keyview_filter/)

## Using a custom stream

Until now, you have been operating exclusively on files on disk. However, there are many situations where the information is not stored in this way – perhaps it is being read from a network, or output by another operation. In these cases, you might want to use KeyView in stream mode.

### Defining a custom stream

You can implement a custom stream by filling out a [KVInputStream](https://www.microfocus.com/documentation/idol/IDOL_24_3/KeyviewFilterSDK_24.3_Documentation/Guides/html/c-programming/Content/C/filtering_structures/KVInputStream.htm) structure with functions that perform the appropriate actions. Each of these are equivalent to the ANSI counterparts (fopen, fread, and so on), except several functions return a BOOL rather than an error code.

To illustrate how to use a custom stream, the following example defines a very simple stream that forwards to the file-based operations.

```c
typedef struct
{
    const char* filename;
    FILE* fp;
    int openCount;
} StreamInfo;

BOOL pascal streamOpen(KVInputStream* stream)
{
    if(!stream || !stream->pInputStreamPrivateData)
    {
        return FALSE;
    }
    StreamInfo* info = (StreamInfo*)stream->pInputStreamPrivateData;
    
    //Open may be called more than once, and the subsequent calls should be a no-op
    if (info->fp == NULL)
    {
        info->fp = fopen(info->filename, "rb");
    }

    if (info->fp)
    {
        fseek(info->fp, 0, SEEK_SET);
        info->openCount++;
    }

    return info->fp != NULL;
}

UINT pascal streamRead(KVInputStream* stream, BYTE * buffer, UINT size)
{
    if(!stream || !stream->pInputStreamPrivateData)
    { 
        return 0;
    }
    StreamInfo* info = (StreamInfo*)stream->pInputStreamPrivateData;
    return fread(buffer, 1, size, info->fp);
}

BOOL pascal streamSeek (KVInputStream* stream, long offset, int whence)
{
    if(!stream || !stream->pInputStreamPrivateData)
    { 
        return FALSE;
    }
    StreamInfo* info = (StreamInfo*)stream->pInputStreamPrivateData;

    return fseek(info->fp, offset, whence) == 0;
}

long pascal streamTell(KVInputStream* stream)
{
    if(!stream || !stream->pInputStreamPrivateData)
    { 
        return FALSE;
    }
    StreamInfo* info = (StreamInfo*)stream->pInputStreamPrivateData;

    return ftell(info->fp);
}

BOOL pascal streamClose(KVInputStream* stream)
{
    if(!stream || !stream->pInputStreamPrivateData)
    { 
        return FALSE;
    }
    StreamInfo* info = (StreamInfo*)stream->pInputStreamPrivateData;
    int retval = 0;

    if (info->openCount > 0)
    {
        --info->openCount;
    }

    if (info->openCount == 0)
    {
        retval = fclose(info->fp);
        info->fp = NULL;
    }
    return retval == 0;
}

StreamInfo info = {pathToInputFile, NULL};
stream.pInputStreamPrivateData = &info;
stream.lcbFilesize = 0;
stream.fpOpen = streamOpen;
stream.fpRead = streamRead;
stream.fpSeek = streamSeek;
stream.fpTell = streamTell;
stream.fpClose = streamClose;
```

If you already know the size of the document when you create the stream, you can use this information to fill out the lcbFilesize member. This option can reduce the number of seeks required, because KeyView does not need to seek to the end of the file to determine the size.

If you do not know the size, you **must** set this member to zero. Failure to set this member results in undefined behavior.

### Opening a document from a stream

After you define a stream, you can create a KVDocument using the stream by calling [fpOpenDocumentFromStream](https://www.microfocus.com/documentation/idol/IDOL_24_3/KeyviewFilterSDK_24.3_Documentation/Guides/html/c-programming/Content/C/filtering_functions/fpOpenDocumentFromStream.htm). This functions in the same way as a document created using fpOpenDocumentFromFile. You must not open a second document from a stream until the first document has been closed.

```c
KVDocument document = NULL;

error = filter.fpOpenDocumentFromStream(session, &stream, &document);

//Pass document to KeyView functions

filter.fpCloseDocument(document);
```

Filtering text and extracting subfiles, on the other hand, have a slightly different interface, which offers more flexibility and can improve performance.

### Extracting subfiles using streams

KeyView also lets you access the subfiles as streams, rather than needing to extract them to disk. Because some KeyView operations do not need to read the entire file, you might get a performance benefit by avoiding the need to extract all the data from the file.

To access a subfile as a stream, use the [fpOpenSubFile()](https://www.microfocus.com/documentation/idol/IDOL_24_3/KeyviewFilterSDK_24.3_Documentation/Guides/html/c-programming/Content/kv_xtract_functions/_KV_XTRACT_funct_fpOpenSubFile.htm) function, rather than using `fpExtractSubFile()`. The [KVExtractSubFileArgRec](https://www.microfocus.com/documentation/idol/IDOL_24_3/KeyviewFilterSDK_24.3_Documentation/Guides/html/c-programming/Content/kv_xtract_structures/_KV_XTRACT_struct_KVExtractSubFileArg.htm) is the same as before.

```c
KVInputStream substream = NULL;
error = extract.fpOpenSubFile(fileContext, &extractArg, &substream);

//Use sub file stream

extract.fpCloseSubFile(substream);
```

You can use the [fpGetExtractInfo](https://www.microfocus.com/documentation/idol/IDOL_24_3/KeyviewFilterSDK_24.3_Documentation/Guides/html/c-programming/Content/kv_xtract_functions/_KV_XTRACT_funct_fpGetExtractInfo.htm) function to retrieve the KVSubFileExtractInfo structure associated with the subfile, and the [fpGetExtractStatus()](https://www.microfocus.com/documentation/idol/IDOL_24_3/KeyviewFilterSDK_24.3_Documentation/Guides/html/c-programming/Content/kv_xtract_functions/_KV_XTRACT_funct_fpGetExtractStatus.htm) function to return more information about any errors encountered when using the subfile stream.

When you parse this stream back into the KeyView Filter interface, it must be on a different session to the one that started the Extract session. Because initializing a new session can incur a performance cost, we recommend that you do this once, and then reuse this session for each sub file.

## Partial filtering

For some use cases, you may not need all of the text from the file, or want to analyze the text in small pieces. The [fpFilter()](https://www.microfocus.com/documentation/idol/IDOL_24_3/KeyviewFilterSDK_24.3_Documentation/Guides/html/c-programming/Content/C/filtering_functions/fpFilter.htm) function outputs the text in chunks, by filling out a [KVFilterOutput](https://www.microfocus.com/documentation/idol/IDOL_24_3/KeyviewFilterSDK_24.3_Documentation/Guides/html/c-programming/Content/C/filtering_structures/KVFilterOutput.htm) structure. You must also free this structure using [fpFreeFilterOutput](https://www.microfocus.com/documentation/idol/IDOL_24_3/KeyviewFilterSDK_24.3_Documentation/Guides/html/c-programming/Content/C/filtering_functions/fpFreeFilterOutput.htm).

The end of the stream is indicated by an empty KVFilterOutput structure. You do not need to free the empty structure.

If you want to keep track of how many bytes have been output, you can accumulate the cbText field of KVFilterOutput.

```c
uint64_t totalSize = 0;

while(1)
{
    KVFilterOutput output = {0};
        
    error = filter->fpFilter(document, &output);
    
    if(error != KVError_Success)
    {
        return error;
    }
    
    if(output.cbText == 0)
    {
        break;
    }
    
    totalSize += output.cbText;

    //Use filter output

    filter->fpFreeFilterOutput(session, &output);
}
```

You might find you want to stop processing before you have filtered the entire file - for example, because you have already found a search term, or because you have hit a resource threshhold. You can safely stop processing, as long as you still call [fpFreeFilterOutput()](https://www.microfocus.com/documentation/idol/IDOL_24_3/KeyviewFilterSDK_24.3_Documentation/Guides/html/c-programming/Content/C/filtering_functions/fpFreeFilterOutput.htm) and [fpCloseDocument()](https://www.microfocus.com/documentation/idol/IDOL_24_3/KeyviewFilterSDK_24.3_Documentation/Guides/html/c-programming/Content/C/filtering_functions/fpCloseDocument.htm).

## Build & Run

### Build 

1. Copy the `idol-oem-tutorials\resources\keyview_filter\sdk\tutorial` folder to `%KEYVIEW_HOME%\samples\tutorial`.  The provided makefile(s) leverage components of the samples' makefile where relative paths are used.
2. Use the provided makefile to build `*e.g.* nmake tutorial_stream_win_x86_64.mak`
3. The `%KEYVIEW_HOME%\samples\tutorial` folder will have bin folder containing 

### Run
1. Since `tutorial.h` specified the `YOUR_BIN_DIR` for KeyView, you can run the built exe from the `bin` folder as shown below:
```cmd
> set PATH=C:\OpenText\KeyViewFilterSDK_24.3.0_WINDOWS_X86_64\bin;%PATH
> cd bin
> tutorial_stream ..\..\..\..\idol-oem-tutorials\resources\keyview_filter\KeyViewFilterSDK_12.13.0_ReleaseNotes_en.pdf out
```
The `out` file will have the text from the input PDF file.

For extra credit, try with your own input file(s) and/or the others provided with this tutorial.

## Conclusion

You should now have a good understanding of the KeyView Filter SDK API, allowing you to automatically detect the file format and extract metadata, text and sub files.

Next, why not try more tutorials to explore some of the other features available in Filter SDK, linked from [here](../keyview_filter/README.md#capability-showcase).

## See also

- [KeyView Filter SDK C Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_3/KeyviewFilterSDK_24.3_Documentation/Guides/html/c-programming/index.html)
- [KeyView Filter SDK C++ Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_3/KeyviewFilterSDK_24.3_Documentation/Guides/html/cpp-programming/index.html)
- [KeyView Filter SDK Java Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_3/KeyviewFilterSDK_24.3_Documentation/Guides/html/java-programming/index.html)
- [KeyView Filter SDK .NET Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_3/KeyviewFilterSDK_24.3_Documentation/Guides/html/dotnet-programming/index.html)
- [KeyView Filter SDK Python Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_24_3/KeyviewFilterSDK_24.3_Documentation/Guides/html/python-programming/)
- [KeyView Release Notes](https://www.microfocus.com/documentation/idol/IDOL_24_3/IDOLReleaseNotes_24.3_Documentation/oem/Content/_KeyView.htm)
