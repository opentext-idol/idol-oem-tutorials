/*

§ Building the sample program

Edit tutorial.h to modify:
- your license key information: YOUR_LICENSE_ORGANIZATION and YOUR_LICENSE_KEY, and
- the location of the KeyView bin directory: YOUR_BIN_DIR.

§ Linking Against KeyView Filter SDK

Example compilation commands. Be sure you set KEYVIEW_HOME environment variable with the installation location (e.g. C:\MicroFocus\KeyviewFilterSDK-12.13.0):

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
#ifndef WIN32
#include <dlfcn.h>
#include <sys/stat.h>
#endif

/* § Defining A Custom Stream */
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


/* § Handling Extended Errors */
int errorCode(KVFltInterfaceEx* filter, void* context, KVErrorCode error)
{
    if(error == KVERR_General)
	{
		return filter->fpGetKvErrorCodeEx(context);
    }

    return error;
}

/* § Filter text using streams */
int filterText(KVFltInterfaceEx* filter, void* context, void* streamContext, void* fOut)
{
    KVErrorCode error = filter->fpCanFilterStream(context, streamContext);
    
    if(error != KVERR_Success)
    {
        return errorCode(filter, context, error);
    }
    
    while(1)
    {
        KVFilterOutput output = {0};
            
        error = filter->fpFilterStream(context, streamContext, &output, NULL);
        
        if(error != KVERR_Success)
        {
            return errorCode(filter, context, error);
        }
        
        if(output.cbText == 0)
        {
            //An empty KVFilterOutput indicates the end of the stream,
            //and does not need to be freed.
            break;
        }

        fprintf(fOut, "%.*s", output.cbText, output.pcText);

        filter->fpFreeFilterOutput(context, &output);
    }
    
    fprintf(fOut, "\n");

    return KVERR_Success;
}

/* § Extracting Subfiles */
int filterSubfileAsStream(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, void* context, void* fileContext, void* subContext, int index, void* fOut)
{
    KVInputStream* substream = NULL;
    
    KVExtractSubFileArgRec extractArg;
    KVStructInit(&extractArg);
    extractArg.index = index;
    extractArg.extractionFlag = KVExtractionFlag_CreateDir | KVExtractionFlag_Overwrite;
        
    KVErrorCode error = extract->fpOpenSubFile(fileContext, &extractArg, &substream);
    
    if(error != KVERR_Success)
    {
        return errorCode(filter, context, error);
    }
    
    //Send the subfile back to our top-level processing function.
    //(Recursion is used here for simplicity. You may wish to consider using a queue structure in your actual application)
    int returnValue = recursivelyFilterStream(filter, extract, subContext, substream, fOut);
    
    extract->fpCloseSubFile(substream);
    
    return returnValue;
}

/* § Extracting Subfiles */
int filterSubfile(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, void* context, void* fileContext, void* subContext, int index, void* fOut)
{
    int returnValue = 0;
    KVSubFileInfo subFileInfo = NULL;
    KVErrorCode error = extract->fpGetSubFileInfo(fileContext, index, &subFileInfo);

    if(error != KVERR_Success)
    {
        return errorCode(filter, context, error);
    }

    //Folders don't contain any text, so no point processing them.
    if(subFileInfo->subFileType != KVSubFileType_Folder)
    {
        returnValue = filterSubfileAsStream(filter, extract, context, fileContext, subContext, index, fOut);
    }
    
    extract->fpFreeStruct(fileContext, subFileInfo);
    
    return returnValue;
}

int filterOpenedContainer(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, void* context, void* fileContext, void* subContext, void* fOut)
{
    KVMainFileInfo fileInfo = NULL;
    KVErrorCode error = extract->fpGetMainFileInfo(fileContext, &fileInfo);

    if(error != KVERR_Success)
    {
        return errorCode(filter, context, error);
    }

    for(int ii = 0; ii < fileInfo->numSubFiles; ++ii)
    {
        int returnValue = filterSubfile(filter, extract, context, fileContext, subContext, ii, fOut);
        
        if(returnValue != KVERR_Success)
        {
            printf("Subfile %d failed with error %d\n", ii, returnValue);
        }
    }
    
    extract->fpFreeStruct(fileContext, fileInfo);
    
    return KVERR_Success;
}
/* § Extracting Subfiles */
int filterContainerSubfiles(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, void* context, KVInputStream* stream, void* fOut)
{
    int returnValue = KVERR_Success;
    
    /* § Extracting subfiles using streams */
    
    //Subfiles as streams must be opened with a different context to the main file,
    //but it can be shared between subfiles, so create one here that all the subfiles will use.
    void* subContext = filter->fpInitWithLicenseData(NULL, NULL,
        YOUR_BIN_DIR,
        YOUR_LICENSE_ORGANIZATION, YOUR_LICENSE_KEY,
        KVCS_UTF8, KVF_HEADERFOOTER);

    if(!subContext) 
    {
        return KVERR_General; 
    }
    
    KVOpenFileArgRec        openArg;
    KVStructInit(&openArg);
    openArg.stream = stream;

    void* fileContext = NULL;
    KVErrorCode error = extract->fpOpenFile(context, &openArg, &fileContext);
    
    if(error == KVERR_Success)
    {
        //Recursively filter subfiles
        returnValue = filterOpenedContainer(filter, extract, context, fileContext, subContext, fOut);
        extract->fpCloseFile(fileContext);
    }
    else
    {
        returnValue = errorCode(filter, context, error);
    }

    filter->fpShutdown(subContext);

    return returnValue;
}

int recursivelyFilterStream(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, void* context, KVInputStream* stream, void* fOut)
{
    void* streamContext = filter->fpOpenStream(context, stream);
    
    if(!streamContext)
    {
        return KVERR_badInputStream;
    }
    
    //Filter the text from the current file
    int filterReturn = filterText(filter, context, streamContext, fOut);
    
    //Extract each subfiles, and recursively process each one.
    int extractReturn = filterContainerSubfiles(filter, extract, context, stream, fOut);
    
    filter->fpCloseStream(context, streamContext);
    
    return (filterReturn == KVERR_Success || extractReturn == KVERR_Success) ? KVERR_Success : filterReturn;
}

//Initialise everything not related to the specific file we're processing
int setupFilterSession(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, void** context)
{
    /* § Loading The Filter Interface */
    KVErrorCode error = KV_GetFilterInterfaceEx(filter, KVFLTINTERFACE_REVISION);

    if(error != KVERR_Success)
    {
        return error;
    }

    /* § Creating A Filter Context */
    *context = filter->fpInitWithLicenseData(NULL, NULL,
        YOUR_BIN_DIR,
        YOUR_LICENSE_ORGANIZATION, YOUR_LICENSE_KEY,
        KVCS_UTF8, KVF_HEADERFOOTER);

    if(!*context) 
    {
         return KVERR_General; 
    }
    
    /* § Loading The Extract Interface */
    KVStructInit(extract);
    error = KVGetExtractInterface(*context, extract);

    if(error != KVERR_Success)
    {
        return errorCode(filter, *context, error);
    }
    
    /* § Filtering Hidden Information */
    if(!filter->fpFilterConfig(*context, KVFLT_SHOWHIDDENTEXT, TRUE, NULL))
    {
        return errorCode(filter, *context, error);
    }
    
    /* § Extracting Subfiles */
    if(!filter->fpFilterConfig(*context, KVFLT_EXTRACTIMAGES, TRUE, NULL))
    {
        return errorCode(filter, *context, error);
    }
    
    return KVERR_Success;
}

/* § Inital Setup */
int filterTutorial(const char* const pathToInputFile, const char* const pathToOutputFile)
{
    /* § Defining A Custom Stream */
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
    void* context = NULL;

    int returnValue = setupFilterSession(&filter, &extract, &context);
    
    
    if(returnValue == KVERR_Success)
    {
        returnValue = recursivelyFilterStream(&filter, &extract, context, &stream, fOut);
    }

    if(filter.fpShutdown)
    {
        filter.fpShutdown(context);
    }
    
    return returnValue;
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
    
    int returnValue = filterTutorial(pathToInputFile, pathToOutputFile);

    printf("Return code %d\n", returnValue);
    
    return returnValue;
}