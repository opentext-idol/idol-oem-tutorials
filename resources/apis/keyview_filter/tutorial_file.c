/*

§1.1. Environment and Compilers

Edit tutorial.h to modify:
- your license key information: YOUR_LICENSE_ORGANIZATION and YOUR_LICENSE_KEY, and
- the location of the KeyView bin directory: YOUR_BIN_DIR.

Example compilation commands. Be sure you set KEYVIEW_HOME environment variable with the installation location (e.g. C:\MicroFocus\KeyviewFilterSDK-12.12.0):

§1.2. Linking Against KeyView Filter SDK

Example compilation commands. Be sure you set KEYVIEW_HOME environment variable with the installation location (e.g. C:\MicroFocus\KeyviewFilterSDK-12.12.0):

    gcc -I$KEYVIEW_HOME/include -o tutorial_file tutorial_file.c -ldl %KEYVIEW_HOME/LINUX_X86_64/bin/kvfilter.so -Wl,-rpath,'$ORIGIN'
    
    clang -I$KEYVIEW_HOME/include -o tutorial_file tutorial_file.c -ldl %KEYVIEW_HOME/MACOS_X86_64/bin/kvfilter.so -Wl,-rpath,@loader_path
    
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
#include <sys/stat.h>
#endif

/* §2.2. Handling Extended Errors */
int errorCode(KVFltInterfaceEx* filter, void* context, KVErrorCode error)
{
    if(error == KVERR_General)
	{
		return filter->fpGetKvErrorCodeEx(context);
    }

    return error;
}

/* §2. Filter A File */
int filterText(KVFltInterfaceEx* filter, void* context, const char* const pathToInputFile, const char* const pathToOutputFile)
{
    KVErrorCode error = KVERR_Success;
    
    /* §3.3. Checking A File Is Supported */
    error = filter->fpCanFilterFile(context, (char*)pathToInputFile);
    
    if(error != KVERR_Success)
    {
        return errorCode(filter, context, error);
    }
    
    /* §2.1. Filtering A File */
    filter->fpFilterFile(context, (char*)pathToInputFile, (char*)pathToOutputFile, NULL);

    if(error != KVERR_Success)
    {
        return errorCode(filter, context, error);
    }
    
    return KVERR_Success;
}

/* §4.1 Retrieving Summary Information */
int summaryInfo(KVFltInterfaceEx* filter, void* context, const char* const pathToInputFile, FILE* fpOut)
{
    KVSummaryInfoEx summaryInfo;
    KVErrorCode error = filter->fpGetOLESummaryInfoFile(context, (char*)pathToInputFile, &summaryInfo);

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
int xmpMetadata(KVFltInterfaceEx* filter, void* context, const char* const pathToInputFile, FILE* fpOut)
{
    KVXmpInfo xmpInfo;
    KVErrorCode error = filter->fpGetXmpInfoFile(context, (char*)pathToInputFile, &xmpInfo, 1);

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
int retrieveMetadata(KVFltInterfaceEx* filter, void* context, const char* const pathToInputFile, const char* const pathToOutputFile)
{
    int returnValue = 0;
    FILE* fpOut = fopen(pathToOutputFile, "a");
    
    if(!fpOut)
    {
        return KVERR_CreateOutputFileFailed;
    }

    returnValue = summaryInfo(filter, context, pathToInputFile, fpOut);
    
    if(returnValue)
    {
        printf("Summary Info for %s returned %d\n", pathToInputFile, returnValue);
    }
    
    returnValue = xmpMetadata(filter, context, pathToInputFile, fpOut);
    
    if(returnValue)
    {
        printf("XMP Metadata for %s returned %d\n", pathToInputFile, returnValue);
    }

    fclose(fpOut);
    
    return KVERR_Success;
}

/* §5. Extracting Subfiles */
int filterSubfiles(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, void* context, const char* const pathToInputFile, const char* const pathToOutputFile)
{
    void* fileContext = NULL;
    KVMainFileInfo fileInfo = NULL;
    KVOpenFileArgRec        openArg;
    KVErrorCode error = KVERR_Success;
    int returnValue = 0;
    char extractDir[260];
    
    /* §5.2 Opening A Container */
    KVStructInit(&openArg);
    openArg.extractDir = extractDir;
    openArg.filePath = (char*)pathToInputFile;

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

    memset(extractDir, 0, 260);
    strcat(extractDir, pathToOutputFile);
    strcat(extractDir, ".dir");
#ifdef WIN32
    CreateDirectory(extractDir, NULL);
#else
    mkdir(extractDir, 0777);
#endif

    /* §5.3 Extracting Subfiles */
    for(int ii = 0; ii < fileInfo->numSubFiles; ++ii)
    {
        char outputFile[260];
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

        error = extract->fpExtractSubFile(fileContext, &extractArg, &extractInfo);

        if(error != KVERR_Success)
        {
            returnValue = errorCode(filter, context, error);
            printf("Subfile %s returned error %d\n", subFileInfo->subFileName, returnValue);
            goto skipfile;
        }
        
        memset(outputFile, 0, 260);
        strcat(outputFile, extractDir);
        strcat(outputFile, "/");
        strcat(outputFile, extractInfo->fileName);
        strcat(outputFile, ".txt");
        returnValue = processFile(filter, extract, context, extractInfo->filePath, outputFile);

        if(returnValue)
        {
            printf("Subfile %s returned error %d\n", subFileInfo->subFileName, returnValue);
            goto skipfile;
        }
skipfile:
        extract->fpFreeStruct(fileContext, extractInfo);
        extract->fpFreeStruct(fileContext, subFileInfo);
    }
    
exit:
    extract->fpFreeStruct(fileContext, fileInfo);
    extract->fpCloseFile(fileContext);

    return returnValue;
}

int processFile(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, void* context, const char* const pathToInputFile, const char* const pathToOutputFile)
{
    int returnValue = filterText(filter, context, pathToInputFile, pathToOutputFile);
    
    //If it isn't supported for filtering, it might still be supported for extraction.
    if(returnValue && returnValue != KVERR_FormatNotSupported)
    {
        goto exit;
    }
    
    //Don't fail the entire run just because metadata failed.
    returnValue = retrieveMetadata(filter, context, pathToInputFile, pathToOutputFile);
    
    if(returnValue)
    {
        goto exit;
    }
    
    returnValue = filterSubfiles(filter, extract, context, pathToInputFile, pathToOutputFile);
    
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
    
    
    /* §1.2. Loading The Filter Interface */
    error = KV_GetFilterInterfaceEx(&filter, KVFLTINTERFACE_REVISION);

    if(error != KVERR_Success)
    {
        return error;
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
        returnValue = error;
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

    returnValue = processFile(&filter, &extract, context, pathToInputFile, pathToOutputFile);

exit:
    if(context)
    {
        filter.fpShutdown(context);
    }
    
    return returnValue;
}


int main (int argc, char *argv[])
{
    int returnValue = 0;
    const char* pathToInputFile = NULL;
    const char* pathToOutputFile = NULL;
    
    if(argc != 3 || !argv[1] || !argv[2])
    {
        printf("Usage: tutorial pathToInput pathToOutput\n");
        printf("Must be run from the KeyView Filter bin directory\n");
        return KVERR_General;
    }
    
    pathToInputFile = argv[1];
    pathToOutputFile = argv[2];
    
    printf("Filtering %s to %s\n", pathToInputFile, pathToOutputFile);
    
    returnValue = filterTutorial(pathToInputFile, pathToOutputFile);

    printf("Return code %d\n", returnValue);
    
    return returnValue;
}