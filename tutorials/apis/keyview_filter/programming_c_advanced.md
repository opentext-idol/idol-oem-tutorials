# KeyView Filter SDK C API Advanced Topics

This lesson follows on from the [previous tutorial](./programming_c.md#keyview-filter-sdk-c-api)

In this lesson, you will:
- Familiarize yourself with more advanced Filter SDK functionality
- Adapt the previous sample program to work on streams, rather than files.

> NOTE: This guide assumes you have already completed the introductory KeyView Filter SDK [tutorial](../../keyview_filter/introduction.md#keyview-filter-sdk-introduction).

> NOTE: This lesson assumes you have also already completed the KeyView Filter SDK C API [tutorial](./programming_c.md).

---
- [Setup](#setup)
  - [Resources](#resources)
- [Using a custom stream](#using-a-custom-stream)
  - [Defining a custom stream](#defining-a-custom-stream)
  - [Using streams for detection and metadata](#using-streams-for-detection-and-metadata)
  - [Filtering text using streams](#filtering-text-using-streams)
  - [Extracting sub files using streams](#extracting-sub-files-using-streams)
- [Conclusion](#conclusion)
- [See also](#see-also)

---

## Setup

Before you continue with this lesson, refer to the [documentation links](#see-also) below.

> NOTE: This lesson assumes you have already completed the [KeyView Filter SDK introduction](../../keyview_filter/introduction.md#keyview-filter-sdk-introduction) lesson covering essential setup steps (*e.g.* required downloads and installation steps) and basic KeyView Filter concepts.

### Resources

Be sure to download the following resources before you continue:
- source code for this tutorial: [tutorial_stream.c](../../../resources/apis/keyview_filter/tutorial_stream.c)
- optional sample files for detection and various extraction options located [here](../../../resources/keyview_filter/)


## Using a custom stream

Until this point, we have been operating exclusively upon files on disk. However, there are many situations where the information is not stored in this way – perhaps it is being read from a network, or output by another operation. In these cases, you may want to use KeyView in stream mode.

### Defining a custom stream

A custom stream can be implemented by filling out a [KVInputStream](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#C/filtering_structures/KVInputStream.htm) structure with functions that perform the appropriate actions. Each of these are equivalent to the ANSI counterparts (fopen, fread, etc.), except several functions return a BOOL rather than an error code.

In order to illustrate how a custom stream is used, we will define a very simple stream that forwards to the file-based operations.

```c
typedef struct
{
    char* filename;
    FILE* fp;
} StreamInfo;

BOOL pascal streamOpen(KVInputStream* stream)
{
    if(!stream || !stream.pInputStreamPrivateData)
    {
        return FALSE;
    }
    
    StreamInfo* info = (StreamInfo*)stream.pInputStreamPrivateData;
    
    info.fp = fopen(info.filename);
    return info.fp != NULL;
}

UINT pascal streamRead(KVInputStream* stream, BYTE * buffer, UINT size)
{
    if(!stream || !stream.pInputStreamPrivateData)
    { 
        return 0;
    }
    StreamInfo* info = (StreamInfo*)stream.pInputStreamPrivateData;
    return fread(buffer, 1, size, info.fp);
}

BOOL pascal streamSeek (KVInputStream* stream, long offset, int whence)
{
    if(!stream || !stream.pInputStreamPrivateData)
    { 
        return FALSE;
    }
    
    StreamInfo* info = (StreamInfo*)stream.pInputStreamPrivateData;

    return fseek(info.fp, offset, whence);
}

long pascal streamTell(KVInputStream* stream)
{
    if(!stream || !stream.pInputStreamPrivateData)
    { 
        return FALSE;
    }
    
    StreamInfo* info = (StreamInfo*)stream.pInputStreamPrivateData;

    return ftell(info.fp); 
}

BOOL pascal fpClose(struct tag_InputStream *)
{
    if(!stream || !stream.pInputStreamPrivateData)
    { 
        return FALSE;
    }
    
    StreamInfo* info = (StreamInfo*)stream.pInputStreamPrivateData;

    return f
    close(info.fp) == 0;
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

If you already know the size of the document when creating a stream, you can use this information to fill out the lcbFilesize member. This can reduce the number of seeks required, since KeyView does not need to seek to the end of the file to determine the size.

If the size is not known, this member **must** be set to zero. Failure to set this member will result in undefined behavior.

> **Files As Streams:** The above code has been written as an illustration, but there may be situations where you want do actually want to operate on files on disk, but using the stream API. Rather than needing to redefine the above, you can use the interface function [fpFileToInputStreamCreate()](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#C/filtering_functions/fpFiletoInputStreamCreate.htm).

### Using streams for detection and metadata

Once a stream is defined, we can adapt our existing code to use streams fairly easily. Several KeyView operations have equivalent functions for taking a stream, and work in the same way as they’re file-based counterparts.

```c
success = filter.fpGetDocInfoStream(context, &stream, &adInfo);
error = filter.fpGetOLESummaryInfo(context, &stream, &summaryInfo);
error = filter.fpGetXmpInfo(context, &stream, &xmpInfo, 1);
```

Filtering text and extracting sub files, on the other hand, have a slightly different interface, which offers more flexibility and can improve performance.

### Filtering text using streams

Before filtering a stream, we must first open the stream. It must also be closed after use.

```c
void* streamContext = NULL;
streamContext = filter.fpOpenStream(context, &stream);
if(!streamContext)
{
    //handle error
}

//Use stream

filter.fpCloseStream(context, streamContext);
```

This can then be passed to [fpCanFilterStream](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#C/filtering_functions/fpCanFilterStream.htm), the equivalent of fpCanFilterFile.

```c
error = filter.fpCanFilterStream(context, streamContext);
```

Filtering text occurs slightly differently. Rather than filtering all the text in one go, we output text in chunks, by filling out a [KVFilterOutput](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#C/filtering_structures/KVFilterOutput.htm) structure. This structure must also be freed.

```c
KVFilterOutput output = {0};

do
{
    error = filter.fpFilterStream(context, streamContext, &output, NULL);
    
    if(error != KVERR_Success)
    {
            //Handle extended error as above
    }

    //Use Filter Output

    filter.fpFreeFilterOutput(context, &output);
} while(output.cbText != 0);
```

> **Partial Filtering:** Because filter stream output is returned in chunks, you may find you have received all the information you need before you’ve filtered the entire file. In this case, you may be able to increase throughput by stopping filtering early. This is safe to do, as long as [fpFreeFilterOutput()](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#C/filtering_functions/fpFreeFilterOutput.htm) and [fpCloseStream()](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#C/filtering_functions/fpCloseStream.htm) are still called.

### Extracting sub files using streams

The main file can be opened using a stream rather than a file, by filling out the stream member of [KVOpenFileArgRec](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#kv_xtract_structures/_KV_XTRACT_struct_KVOpenFileArg.htm), rather than the filePath member.

```c
openArg.stream = &stream;
```

KeyView also lets you access the sub files as streams, rather than needing to extract them to disk. Since some KeyView operations do not require reading the entire file, you may get a performance benefit by avoiding the need to extract all the data from the file.

To access a sub file as a stream, we use the [fpOpenSubFile()](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#kv_xtract_functions/_KV_XTRACT_funct_fpOpenSubFile.htm) function, rather than using `fpExtractSubFile()`. The [KVExtractSubFileArgRec](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#kv_xtract_structures/_KV_XTRACT_struct_KVExtractSubFileArg.htm) is the same as before.

```c
KVInputStream substream = NULL;
error = extract.fpOpenSubFile(fileContext, &extractArg, &substream);

//Use sub file stream

extract.fpCloseSubFile(substream);
```

You can use the [fpGetExtractInfo](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#kv_xtract_functions/_KV_XTRACT_funct_fpGetExtractInfo.htm) function to retrieve the KVSubFileExtractInfo structure associated with the subfile, and the [fpGetExtractStatus()](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html#kv_xtract_functions/_KV_XTRACT_funct_fpGetExtractStatus.htm) function to return more information about any errors encountered when using the sub file stream.

When parsing this stream back into the KeyView Filter interface, it must be on a different context to the one that started the Extract session. Because initializing a new context can incur a performance cost, this should be done once, and then this context can be reused for each sub file.

## Conclusion

You should now have a good understanding of the KeyView Filter SDK API allowing to automatically detect the file format and extract metadata, text and sub files.

If you haven't already done so, why not try more tutorials to explore some of the other features available in KeyView Filter SDK, linked from the [main page](../../README.md#keyview-filter-sdk-showcase).

## See also

- [KeyView Filter SDK C Programming Guide](https://www.microfocus.com/documentation/idol/IDOL_12_12/KeyviewFilterSDK_12.12_Documentation/Guides/html/c-programming/index.html)
