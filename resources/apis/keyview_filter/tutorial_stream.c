/*

§1.1. Environment and Compilers

Edit tutorial.h to modify:
- your license key information: YOUR_LICENSE_ORGANIZATION and YOUR_LICENSE_KEY, and
- the location of the KeyView bin directory: YOUR_BIN_DIR.

Example compilation commands. Be sure you set KEYVIEW_HOME environment variable with the installation location (e.g. C:\MicroFocus\KeyviewFilterSDK-12.12.0):

§1.2. Linking Against KeyView Filter SDK

Example compilation commands. Be sure you set KEYVIEW_HOME environment variable with the installation location (e.g. C:\MicroFocus\KeyviewFilterSDK-12.12.0):

    gcc -I$KEYVIEW_HOME/include -o tutorial_file tutorial_file.c -ldl $KEYVIEW_HOME/LINUX_X86_64/bin/kvfilter.so -Wl,-rpath,'$ORIGIN'
    
    clang -I$KEYVIEW_HOME/include -o tutorial_file tutorial_file.c -ldl $KEYVIEW_HOME/MACOS_X86_64/bin/kvfilter.so -Wl,-rpath,@loader_path
    
    cl.exe /I%KEYVIEW_HOME%/include tutorial.c %KEYVIEW_HOME%/WINDOWS_X86_64/bin/kvfilter.so

*/


#include "kvtypes.h"
#include "kvfilt.h"
#include "kvxtract.h"
#include "tutorial.h"

#include <stdio.h>
#include <time.h>
#ifndef WIN32
#include <dlfcn.h>
#endif

/* § 6.1. Defining A Custom Stream */
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


/* §2.2. Handling Extended Errors */
int errorCode(KVFltInterfaceEx* filter, void* context, KVErrorCode error)
{
    if(error == KVERR_General)
	{
		return filter->fpGetKvErrorCodeEx(context);
    }

    return error;
}

/* §6.3. Filtering Text Using Streams */
int filterText(KVFltInterfaceEx* filter, void* context, KVInputStream* stream, FILE* fpOut)
{
    int returnValue = 0;
    KVErrorCode error = KVERR_Success;
    void* streamContext = NULL;
    KVFilterOutput output = {0};
    
    streamContext = filter->fpOpenStream(context, stream);
    
    if(!streamContext)
    {
        returnValue = KVERR_badInputStream;
        goto exit;
    }
    
    error = filter->fpCanFilterStream(context, streamContext);
    
    if(error != KVERR_Success)
    {
        return errorCode(filter, context, error);
    }
    
    do
    {
        error = filter->fpFilterStream(context, streamContext, &output, NULL);
        
        if(error != KVERR_Success)
        {
            returnValue = errorCode(filter, context, error);
            goto exit;
        }

        fprintf(fpOut, "%.*s", output.cbText, output.pcText);

        filter->fpFreeFilterOutput(context, &output);
    } while(output.cbText != 0);

    if(error != KVERR_Success)
    {
        return errorCode(filter, context, error);
    }
    
exit:
    filter->fpCloseStream(context, streamContext);
    
    return KVERR_Success;
}

/* §4.1 Retrieving Summary Information */
int summaryInfo(KVFltInterfaceEx* filter, void* context, KVInputStream* stream, FILE* fpOut)
{
    KVSummaryInfoEx summaryInfo;
    KVErrorCode error = filter->fpGetOLESummaryInfo(context, stream, &summaryInfo);

    if(error != KVERR_Success)
    {
        return errorCode(filter, context, error);
    }
    
    fprintf(fpOut, "\n\n====== Summary Information ======\n\n");

    for(int ii=0; ii < summaryInfo.nElem; ++ii)
    {
        KVSumInfoElemEx* element = &summaryInfo.pElem[ii];
        
        if(!element->isValid)
        {
            continue;
        }

        fprintf(fpOut, "%s: ", element->pcType);

        switch(element->type)
        {
        case KV_Int4:
            //data contains an actual int, not a pointer
            fprintf(fpOut, "%d", (int)element->data); 
            break;
        case KV_Bool:
            //NULL pointer is false, true otherwise
            fprintf(fpOut, "%s", element->data ? "true" : "false");
            break;
        case KV_IEEE8:
            //Pointer to double
            fprintf(fpOut, "%lf", *(double*)element->data);
            break;
        case KV_DateTime:
        {
            //Pointer to Windows file time
            //That is, 64-bit value representing 100-nanosecond intervals since 1601-01-01T00:00 UTC
            const long long intervalsPerSecond = 10000000LL;
            const long long windowsToUnixSeconds = 11644473600LL;
            time_t unixTime = (*(long long*)element->data / intervalsPerSecond) - windowsToUnixSeconds;
            fprintf(fpOut, "%s", asctime(localtime(&unixTime)));
            break;
        }
        case KV_String:
            //Null-terminated C-string
            fprintf(fpOut, "%s", (char*)element->data);
            break;
        case KV_Unicode:
            //Null-terminated wide C-string
            fprintf(fpOut, "%ls", (unsigned short*)element->data);
            break;
        case KV_ClipBoard:
        case KV_Other:
        default:
            fprintf(fpOut, "Value could not be interpreted");
            break;
        }

        fprintf(fpOut, "\n");
    }

    filter->fpFreeOLESummaryInfo(context, &summaryInfo);
    
    return KVERR_Success;
}

/* §4.2. Retrieving XMP Metadata */
int xmpMetadata(KVFltInterfaceEx* filter, void* context, KVInputStream* stream, FILE* fpOut)
{
    KVXmpInfo xmpInfo;
    KVErrorCode error = filter->fpGetXmpInfo(context, stream, &xmpInfo, 1);

    if(error != KVERR_Success)
    {
        return errorCode(filter, context, error);
    }
    
    fprintf(fpOut, "\n\n====== XMP Metadata ======\n\n");
    
    if(xmpInfo.nNoOfElements == 0)
    {
        fprintf(fpOut, "No XMP metadata\n");
    }

    for(int ii = 0; ii < xmpInfo.nNoOfElements; ++ii)
    {
        KVXmpInfoElem* element = &xmpInfo.pXmpInfoElems[ii];

        fprintf(fpOut, "%.*s %.*s\n", 
           element->usXPathToElement.cbSize, element->usXPathToElement.pcString,
           element->usValue.cbSize, element->usValue.pcString);
    }

    filter->fpFreeXmpInfo(context, &xmpInfo);

    return KVERR_Success;
}

/* §4. Retrieving Metadata */
int retrieveMetadata(KVFltInterfaceEx* filter, void* context, KVInputStream* stream, FILE* fpOut)
{
    int returnValue = summaryInfo(filter, context, stream, fpOut);
    
    if(returnValue)
    {
        fprintf(fpOut, "Summary Info returned %d\n", returnValue);
    }
    
    returnValue = xmpMetadata(filter, context, stream, fpOut);
    
    if(returnValue)
    {
        fprintf(fpOut, "XMP Metadata returned %d\n", returnValue);
    }
    
    return KVERR_Success;
}

/* §5. Extracting Subfiles */
int filterSubfiles(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, void* context, KVInputStream* stream, FILE* fpOut)
{
    void* fileContext = NULL;
    void* subContext = NULL;
    KVMainFileInfo fileInfo = NULL;
    KVOpenFileArgRec        openArg;
    KVErrorCode error = KVERR_Success;
    int returnValue = 0;
    
    /* §5.2 Opening A Container */
    KVStructInit(&openArg);
    openArg.stream = stream;

    error = extract->fpOpenFile(context, &openArg, &fileContext);

    if(error != KVERR_Success)
    {
        returnValue = errorCode(filter, context, error);
        goto exit;
    }
    
    error = extract->fpGetMainFileInfo(fileContext, &fileInfo);

    if(error != KVERR_Success)
    {
        returnValue = errorCode(filter, context, error);
        goto exit;
    }

    if (fileInfo->numSubFiles == 0)
    {
        goto exit;
    }
    
    //Subfiles as streams must be opened with a different context to the main file,
    //but can be shared between subfiles.
    subContext = filter->fpInitWithLicenseData(NULL, NULL,
        "./",
        YOUR_LICENSE_ORGANIZATION, YOUR_LICENSE_KEY,
         KVCS_UTF8, KVF_HEADERFOOTER);

    if(!subContext) 
    {
         returnValue = KVERR_General; 
         goto exit;
    }

    /* §5.2 Extracting Subfiles */
    for(int ii = 0; ii < fileInfo->numSubFiles; ++ii)
    {
        KVInputStream* substream = NULL;
        KVSubFileInfo subFileInfo = NULL;
        KVSubFileExtractInfo extractInfo = NULL;
        KVExtractSubFileArgRec extractArg;
        KVStructInit(&extractArg);

        error = extract->fpGetSubFileInfo(fileContext, ii, &subFileInfo);

        if(error != KVERR_Success)
        {
            returnValue = errorCode(filter, context, error);
            printf("Subfile %d returned error %d\n", ii, returnValue);
            goto skipfile;
        }

        if(subFileInfo->subFileType == KVSubFileType_Folder)
        {
            goto skipfile;
        }
        
        extractArg.index = ii;
        extractArg.extractionFlag = KVExtractionFlag_CreateDir | KVExtractionFlag_Overwrite;
        extractArg.filePath = subFileInfo->subFileName;

        error = extract->fpOpenSubFile(fileContext, &extractArg, &substream);

        if(error != KVERR_Success)
        {
            returnValue = errorCode(filter, context, error);
            printf("Subfile %s returned error %d\n", subFileInfo->subFileName, returnValue);
            goto skipfile;
        }
        
        fprintf(fpOut, "\n\n===== %s =====\n\n", subFileInfo->subFileName);
        
        returnValue = processFile(filter, extract, subContext, substream, fpOut);

        if(returnValue)
        {
            printf("Subfile %s returned error %d\n", subFileInfo->subFileName, returnValue);
            goto skipfile;
        }
skipfile:
        extract->fpFreeStruct(fileContext, extractInfo);
        extract->fpFreeStruct(fileContext, subFileInfo);
        extract->fpCloseSubFile(substream);
    }
    
exit:
    filter->fpShutdown(subContext);
    extract->fpFreeStruct(fileContext, fileInfo);
    extract->fpCloseFile(fileContext);

    return returnValue;
}

int processFile(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, void* context, KVInputStream* stream, FILE* fpOut)
{
    int returnValue = filterText(filter, context, stream, fpOut);
    
    //If it isn't supported for filtering, it might still be supported for extraction.
    if(returnValue && returnValue != KVERR_FormatNotSupported)
    {
        goto exit;
    }
    
    //Don't fail the entire run just because metadata failed.
    returnValue = retrieveMetadata(filter, context, stream, fpOut);
    
    if(returnValue)
    {
        goto exit;
    }
    
    returnValue = filterSubfiles(filter, extract, context, stream, fpOut);
    
    if(returnValue)
    {
        goto exit;
    }

exit:
    return returnValue;
}

/* §1. Inital Setup */
int filterTutorial(const char* const pathToInputFile, const char* const pathToOutputFile)
{
    KVFltInterfaceEx filter;
    KVExtractInterfaceRec extract;
    KVErrorCode error = KVERR_Success;
    void* context = NULL;
    int returnValue = 0;
    
    StreamInfo info = {pathToInputFile, NULL, 0};
    KVInputStream stream;
    void* fpOut = NULL;
    
    
    /* §1.2. Loading The Filter Interface */
    error = KV_GetFilterInterfaceEx(&filter, KVFLTINTERFACE_REVISION);

    if(error != KVERR_Success)
    {
        goto exit;
    }

    /* §1.3. Creating A Filter Context */
    context = filter.fpInitWithLicenseData(NULL, NULL,
        YOUR_BIN_DIR,
        YOUR_LICENSE_ORGANIZATION, YOUR_LICENSE_KEY,
        KVCS_UTF8, KVF_HEADERFOOTER);

    if(!context) 
    {
         returnValue = KVERR_General; 
         goto exit;
    }
    
    /* §5.1. Loading The Extract Interface */
    KVStructInit(&extract);
    error = KVGetExtractInterface(context, &extract);

    if(error != KVERR_Success)
    {
        goto exit;
    }
    
    /* §2.3. Filtering Hidden Information */
    if(!filter.fpFilterConfig(context, KVFLT_SHOWHIDDENTEXT, TRUE, NULL))
    {
        KVErrorCodeEx extError = filter.fpGetKvErrorCodeEx(context);
        
        return extError ? extError : KVERR_General;
    }
    
    /* §5.3. Extracting Subfiles */
    if(!filter.fpFilterConfig(context, KVFLT_EXTRACTIMAGES, TRUE, NULL))
    {
        KVErrorCodeEx extError = filter.fpGetKvErrorCodeEx(context);
        
        return extError ? extError : KVERR_General;
    }
    
    /* We've now set up everything needed for the session.
       If we were processing multiple files in one session, we could call processFile() repeatedly. */
    
    /* §6.1. Defining A Custom Stream */
    stream.pInputStreamPrivateData = &info;
    stream.lcbFilesize = 0;
    stream.fpOpen = streamOpen;
    stream.fpRead = streamRead;
    stream.fpSeek = streamSeek;
    stream.fpTell = streamTell;
    stream.fpClose = streamClose;
    
    fpOut = fopen(pathToOutputFile, "w");
    
    if(!fpOut)
    {
        returnValue = KVERR_CreateOutputFileFailed;
        goto exit;
    }

    returnValue = processFile(&filter, &extract, context, &stream, fpOut);

exit:
    if(context)
    {
        filter.fpShutdown(context);
    }
    
    return returnValue;
}


int main (int argc, char *argv[])
{
    if(argc != 3 || !argv[1] || !argv[2])
    {
        printf("Usage: tutorial pathToInput pathToOutput\n");
        printf("Must be run from the KeyView Filter bin directory\n");
        return KVERR_General;
    }
    
    const char* pathToInputFile = argv[1];
    const char* pathToOutputFile = argv[2];
    
    printf("Filtering %s to %s\n", pathToInputFile, pathToOutputFile);
    
    int returnValue = filterTutorial(pathToInputFile, pathToOutputFile);

    printf("Return code %d\n", returnValue);
    
    return returnValue;
}