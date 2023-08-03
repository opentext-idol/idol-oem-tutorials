/*

§ Building the sample program

Edit tutorial.h to modify YOUR_LICENSE_KEY and YOUR_BIN_DIR.

§ Linking against KeyView Filter SDK

Example compilation commands. Be sure you set KEYVIEW_HOME environment variable with the installation location (e.g. C:\OpenText\KeyviewFilterSDK_23.3.0_WINDOWS_X86_64):

    gcc -I$KEYVIEW_HOME/include -o tutorial_stream tutorial_stream.c -ldl $KEYVIEW_HOME/LINUX_X86_64/bin/kvfilter.so -Wl,-rpath,'$ORIGIN'
    
    clang -I$KEYVIEW_HOME/include -o tutorial_stream tutorial_stream.c -ldl $KEYVIEW_HOME/MACOS_X86_64/bin/kvfilter.so -Wl,-rpath,@loader_path
    
    cl.exe /I%KEYVIEW_HOME%/include tutorial_stream.c %KEYVIEW_HOME%/WINDOWS_X86_64/lib/kvfilter.lib

*/


#include "kvtypes.h"
#include "kvfilt.h"
#include "kvxtract.h"
#include "tutorial.h"

#include <stdio.h>
#include <time.h>
#include <limits.h>
#ifndef WIN32
#include <dlfcn.h>
#include <sys/stat.h>
#endif

KVErrorCode recursivelyFilterStream(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, KVFilterSession session, KVInputStream* stream, void* fOut);

struct tm* winFileTimeToUnixTime(int64_t winFileTime)
{
    const int64_t intervalsPerSecond = 10000000LL;
    const int64_t windowsToUnixSeconds = 11644473600LL;
    int64_t unixTime = (winFileTime / intervalsPerSecond) - windowsToUnixSeconds;
    //time_t is only 32-bit on some platforms
    if(sizeof(time_t) == 4 && (unixTime < INT_MIN || unixTime > INT_MAX))
    {
        return NULL;
    }
    return gmtime(&unixTime);
}

// § Defining A Custom Stream 
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


KVErrorCode filterText(KVFltInterfaceEx* filter, KVFilterSession session, KVDocument document, void* fOut)
{
    // § Checking if a file is supported
    KVErrorCode error = filter->fpCanFilter(document);
    
    if(error != KVERR_Success)
    {
        return error;
    }
    
    // § Partial filtering
    
    uint64_t totalSize = 0;
    
    while(1)
    {
        KVFilterOutput output = {0};
            
        error = filter->fpFilter(document, &output);
        
        if(error != KVERR_Success)
        {
            return error;
        }
        
        if(output.cbText == 0)
        {
            //An empty KVFilterOutput indicates the end of the stream,
            //and does not need to be freed.
            break;
        }
        
        //In this tutorial, we don't use the size for anything.
        //But this could be checked to stop processing after a certain limit, for example.
        totalSize += output.cbText;

        //In this tutorial, we're outputting to UTF-8, so we don't expect any embedded null bytes in strings.
        //Other character sets may need different handling.
        fprintf(fOut, "%.*s", output.cbText, output.pcText);

        filter->fpFreeFilterOutput(session, &output);
    }
    
    fprintf(fOut, "\n");

    return KVERR_Success;
}

// § Interpretting a metadata element
void printMetadatum(void* fOut, const KVMetadataElement* element)
{
    if(!element->pKey || !element->pKey->pcString || !element->pValue)
    {
        return;
    }
    
    //In this tutorial, we're outputting to UTF-8, so we don't expect any embedded null bytes in strings.
    //Other character sets may need different handling.
    fprintf(fOut, "%-5d \"%*s\": ", element->eKey, element->pKey->cbSize, element->pKey->pcString);

    switch (element->eType)
    {
    case KVMetadataValue_Bool:
    {
        BOOL value = *(BOOL*)element->pValue;
        fprintf(fOut, "(Bool) %s\n", value ? "true" : "false");
        break;
    }
    case KVMetadataValue_Int64:
    {
        int64_t value = *(int64_t*)element->pValue;
        fprintf(fOut, "(Int64) %lld\n", value);
        break;
    }
    case KVMetadataValue_Double:
    {
        double value = *(double*)element->pValue;
        fprintf(fOut, "(Double) %f\n", value);
        break;
    }
    case KVMetadataValue_WinFileTime:
    {
        int64_t value = *(int64_t*)element->pValue;
        struct tm* unixTime = winFileTimeToUnixTime(value);
        if (unixTime)
        {
            char buffer[40] = { 0 };
            strftime(&buffer[0], sizeof(buffer), "%FT%TZ", unixTime);
            fprintf(fOut, "(WinFileTime) \"%s\"\n", &buffer);
        }
        else
        {
            //gmtime can't handle as large a range as WinFileTime,
            //so fallback to printing the raw value
            fprintf(fOut, "(WinFileTime) %lld00ns\n", value);
        }
        break;
    }
    case KVMetadataValue_String:
    {
        KVString value = *(KVString*)element->pValue;
        if (!value.pcString)
        {
            fprintf(fOut, "Invalid String value");
            break;
        }
        //In this tutorial, we're outputting to UTF-8, so we don't expect any embedded null bytes in strings.
        //Other character sets may need different handling.
        fprintf(fOut, "(String) \"%*s\"\n", value.cbSize, value.pcString);
        break;
    }
    case KVMetadataValue_Binary:
    {
        KVBinaryData value = *(KVBinaryData*)element->pValue;
        if(!value.pucData)
        {
            fprintf(fOut, "Invalid binary value");
        }
        //Convert to char* in case the binary data contains human-readable portions.
        //Binary data may contain embedded null bytes, so use fwrite instead of fprintf.
        fprintf(fOut, "(Binary) \"");
        fwrite((char*)value.pucData, 1, value.cbSize, fOut);
        fprintf(fOut, "\"\n");
        break;
    }
    case KVMetadataValue_MIPLabel:
    {
        KVMIPLabel value = *(KVMIPLabel*)element->pValue;
        if (!value.labelId || !value.labelId->pcString || !value.siteId || !value.siteId->pcString)
        {
            fprintf(fOut, "Invalid MIPLabel value");
            break;
        }
        fprintf(fOut, "\"(MIPLabel) [LabelId=%*s", value.labelId->cbSize, value.labelId->pcString);
        fprintf(fOut, ", Enabled=%s", value.enabled ? "true" : "false");
        fprintf(fOut, ", SiteId=%*s", value.siteId->cbSize, value.siteId->pcString);
        if (value.actionId && value.actionId->pcString != NULL)
        {
            fprintf(fOut, ", ActionId=%*s", value.actionId->cbSize, value.actionId->pcString);
        }
        if (value.method && value.method->pcString != NULL)
        {
            fprintf(fOut, ", Method=%*s", value.method->cbSize, value.method->pcString);
        }
        if (value.setDate)
        {
            struct tm* unixTime = winFileTimeToUnixTime(*value.setDate);
            if (unixTime)
            {
                char buffer[40] = { 0 };
                strftime(&buffer[0], sizeof(buffer), "%FT%TZ", unixTime);
                fprintf(fOut, ", SetDate=\"%s\"", &buffer);
            }
            else
            {
                //gmtime can't handle as big a range as WinFileTime,
                //so fallback to printing the raw value
                fprintf(fOut, ", SetDate=%lld00ns", *value.setDate);
            }
        }
        if (value.name && value.name->pcString != NULL)
        {
            fprintf(fOut, ", Name=%*s", value.name->cbSize, value.name->pcString);
        }
        if (value.contentBits)
        {
            fprintf(fOut, ", ContentBits=%lld", *value.contentBits);
        }
        fprintf(fOut, "]\"\n");
    }
    default:
        break;
    }
}

// § Iterating through the metadata list
KVErrorCode iterateMetadata(const KVMetadataList* metadataList, void* fOut, const char* const title)
{
    fprintf(fOut, "\n%s:\n", title);
    int error = KVERR_Success;
    while(1)
    {
        const KVMetadataElement* element = NULL;
        error = metadataList->fpGetNext(metadataList, &element);

        if(error != KVERR_Success)
        {
            return error;
        }

        if(!element)
        {
            //End of metadata
            break;
        }

        printMetadatum(fOut, element);
    }

    fprintf(fOut, "\n\n");

    return error;
}

// § Getting the metadata list
KVErrorCode retreiveMetadata(KVFltInterfaceEx* filter, KVDocument document, void* fOut)
{
    const KVMetadataList* metadataList = NULL;
    KVErrorCode error = filter->fpGetMetadataList(document, &metadataList);

    if(error != KVERR_Success)
    {
        return error;
    }

    error = iterateMetadata(metadataList, fOut, "Metadata");

    metadataList->fpFree(metadataList);

    return error;
}

// § Retrieving mail metadata
KVErrorCode retreiveSubfileMetadata(KVExtractInterfaceRec* extract, void* fileSession, int index, void* fOut)
{
    const KVMetadataList* metadataList = NULL;

    KVGetSubFileMetadataListArgRec metaArgs;
    KVStructInit(&metaArgs);
    metaArgs.index = index;
    metaArgs.trgCharset = KVCS_UTF8;

    KVErrorCode error = extract->fpGetSubFileMetadataList(fileSession, &metaArgs, &metadataList);

    if(error != KVError_Success)
    {
        return error;
    }

    error = iterateMetadata(metadataList, fOut, "Subfile metadata");

    metadataList->fpFree(metadataList);
    
    return error;
}

// § Extracting sub files
KVErrorCode filterSubfileAsStream(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, void* fileContext, KVFilterSession subSession, int index, void* fOut)
{
    // § Extracting sub files using streams
    KVInputStream* substream = NULL;
    
    KVExtractSubFileArgRec extractArg;
    KVStructInit(&extractArg);
    extractArg.index = index;
    extractArg.extractionFlag = 
        KVExtractionFlag_CreateDir | 
        KVExtractionFlag_Overwrite | 
        KVExtractionFlag_GetFormattedBody | 
        KVExtractionFlag_SanitizeAbsolutePaths;
        
    KVErrorCode error = extract->fpOpenSubFile(fileContext, &extractArg, &substream);
    
    if(error != KVERR_Success)
    {
        return error;
    }
    
    //Send the subfile back to our top-level processing function.
    //(Recursion is used here for simplicity. You may wish to consider using a queue structure in your actual application)
    error = recursivelyFilterStream(filter, extract, subSession, substream, fOut);
    
    extract->fpCloseSubFile(substream);
    
    if(error != KVERR_Success)
    {
        return error;
    }
    
    return retreiveSubfileMetadata(extract, fileContext, index, fOut);
}

// § Extracting sub files
KVErrorCode filterSubfile(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, void* fileContext, KVFilterSession subSession, int index, void* fOut)
{
    KVSubFileInfo subFileInfo = NULL;
    KVErrorCode error = extract->fpGetSubFileInfo(fileContext, index, &subFileInfo);

    if(error != KVERR_Success)
    {
        return error;
    }

    //Folders and external links don't contain any text, so no point processing them.
    if(subFileInfo->subFileType != KVSubFileType_Folder && !(subFileInfo->infoFlag & KVSubFileInfoFlag_External))
    {
        error = filterSubfileAsStream(filter, extract, fileContext, subSession, index, fOut);
    }
    
    extract->fpFreeStruct(fileContext, subFileInfo);
    
    return error;
}

// § Opening a container
KVErrorCode filterOpenedContainer(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, void* fileContext, KVFilterSession subSession, void* fOut)
{
    KVMainFileInfo fileInfo = NULL;
    KVErrorCode error = extract->fpGetMainFileInfo(fileContext, &fileInfo);

    if(error != KVERR_Success)
    {
        return error;
    }

    for(int ii = 0; ii < fileInfo->numSubFiles; ++ii)
    {
        error = filterSubfile(filter, extract, fileContext, subSession, ii, fOut);
        
        if(error != KVERR_Success)
        {
            printf("Subfile %d failed with error %d\n", ii, error);
        }
    }
    
    extract->fpFreeStruct(fileContext, fileInfo);
    
    return KVERR_Success;
}
// § Extracting sub files
KVErrorCode filterContainerSubfiles(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, 
KVFilterSession session, KVDocument document, void* fOut)
{
    // § Extracting sub files using streams
    
    //Subfiles as streams must be opened with a different session to the main file,
    //but it can be shared between subfiles, so create one here that all the subfiles will use.
    KVFilterSession subSession = NULL;
    
    KVFilterInitOptions options;
    KVStructInit(&options);
    options.outputCharSet = KVCS_UTF8;
    
    KVErrorCode error = filter->fpInit(
        YOUR_BIN_DIR,
        YOUR_LICENSE_KEY,
        &options,
        &subSession);
        
    if(error != KVERR_Success)
    {
         return error; 
    }
    
    KVOpenFileArgRec        openArg;
    KVStructInit(&openArg);
    openArg.document = document;

    void* fileContext = NULL;
    error = extract->fpOpenFile(session, &openArg, &fileContext);
    
    if(error == KVERR_Success)
    {
        //Recursively filter subfiles
        error = filterOpenedContainer(filter, extract, fileContext, subSession, fOut);
        extract->fpCloseFile(fileContext);
    }

    filter->fpShutdown(subSession);

    return error;
}

KVErrorCode recursivelyFilterStream(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, KVFilterSession session, KVInputStream* stream, void* fOut)
{
    KVDocument document = NULL;
    KVErrorCode error = filter->fpOpenDocumentFromStream(session, stream, &document);
    
    if(error != KVERR_Success)
    {
        return error;
    }
    
    //Filter the text from the current file
    KVErrorCode filterError = filterText(filter, session, document, fOut);
    
    //Output metadata from the current file
    KVErrorCode metadataError = retreiveMetadata(filter, document, fOut);
    
    //Extract each subfiles, and recursively process each one.
    KVErrorCode extractError = filterContainerSubfiles(filter, extract, session, document, fOut);
    
    filter->fpCloseDocument(document);
    
    //For simplicity in the tutorial, we return success if any KeyView functionality succeeded.
    //You may wish to handle errors differently in your application.
    if(filterError == KVError_Success || metadataError == KVError_Success || extractError == KVError_Success)
    {
        return KVError_Success;
    }
    else
    {
        //All three functions failed, so choose to return the first error
        return filterError;
    }
}

KVErrorCode setupFilterSession(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, KVFilterSession* pSession)
{
    // § Loading the Filter interface
    KVErrorCode error = KV_GetFilterInterfaceEx(filter, KVFLTINTERFACE_REVISION);

    if(error != KVERR_Success)
    {
        return error;
    }

    // § Creating a Filter context
    KVFilterInitOptions options;
    KVStructInit(&options);
    options.outputCharSet = KVCS_UTF8;
    
    error = filter->fpInit(
        YOUR_BIN_DIR,
        YOUR_LICENSE_KEY,
        &options,
        pSession);
        
    if(error != KVERR_Success)
    {
         return error; 
    }
    
    // § Loading the Extract interface
    KVStructInit(extract);
    error = KVGetExtractInterface(*pSession, extract);

    if(error != KVERR_Success)
    {
        return error;
    }
    
    // § Filtering hidden information
    error = filter->fpSetConfig(*pSession, KVFLT_SHOWHIDDENTEXT, TRUE, NULL);
    
    if(error != KVERR_Success)
    {
        return error;
    }
    
    // § Extracting sub files
    error = filter->fpSetConfig(*pSession, KVFLT_EXTRACTIMAGES, TRUE, NULL);
    
    if(error != KVERR_Success)
    {
        return error;
    }
    
    return KVERR_Success;
}

// § API Setup
KVErrorCode filterTutorial(const char* const pathToInputFile, const char* const pathToOutputFile)
{
    // § Defining a custom stream
    StreamInfo info = {pathToInputFile, NULL, 0};
    KVInputStream stream;
    stream.pInputStreamPrivateData = &info;
    stream.lcbFilesize = 0;
    stream.fpOpen = streamOpen;
    stream.fpRead = streamRead;
    stream.fpSeek = streamSeek;
    stream.fpTell = streamTell;
    stream.fpClose = streamClose;
    
    void* fOut = fopen(pathToOutputFile, "w");
    
    if(!fOut)
    {
        return KVERR_ErrorWritingToOutputFile;
    }
    
    KVFltInterfaceEx filter = {0};
    KVExtractInterfaceRec extract = {0};
    KVFilterSession session = NULL;

    KVErrorCode error = setupFilterSession(&filter, &extract, &session);
    
    if(error == KVERR_Success)
    {
        error = recursivelyFilterStream(&filter, &extract, session, &stream, fOut);
    }

    if(filter.fpShutdown)
    {
        filter.fpShutdown(session);
    }
    
    return error;
}


int main (int argc, char *argv[])
{
    if(argc != 3 || !argv[1] || !argv[2])
    {
        printf("Usage: tutorial_stream pathToInput pathToOutput\n");
        printf("Must be run from the KeyView Filter bin directory\n");
        return KVERR_General;
    }
    
    const char* const pathToInputFile = argv[1];
    const char* const pathToOutputFile = argv[2];
    
    printf("tutorial_stream: sample program - not for production use\n\n");
    printf("Filtering %s to %s\n", pathToInputFile, pathToOutputFile);
    
    KVErrorCode error = filterTutorial(pathToInputFile, pathToOutputFile);

    printf("Return code %d\n", error);
    
    return error;
}
