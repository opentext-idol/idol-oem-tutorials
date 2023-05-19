/*

§ Building the sample program

Edit tutorial.h to modify YOUR_LICENSE_KEY and YOUR_BIN_DIR.

§ Linking against KeyView Filter SDK

Example compilation commands. Be sure you set KEYVIEW_HOME environment variable with the installation location (e.g. C:\OpenText\KeyviewFilterSDK-23.2.0):

    gcc -I$KEYVIEW_HOME/include -o tutorial_file tutorial_file.c -ldl $KEYVIEW_HOME/LINUX_X86_64/bin/kvfilter.so -Wl,-rpath,'$ORIGIN'
    
    clang -I$KEYVIEW_HOME/include -o tutorial_file tutorial_file.c -ldl $KEYVIEW_HOME/MACOS_X86_64/bin/kvfilter.so -Wl,-rpath,@loader_path
    
    cl.exe /I%KEYVIEW_HOME%/include tutorial_file.c %KEYVIEW_HOME%/WINDOWS_X86_64/lib/kvfilter.lib

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

KVErrorCode recursivelyFilterFile(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, KVFilterSession session, const char* const pathToInputFile, const char* const pathToOutputFile);

BOOL createSubdirForFile(const char* const pathToOutputFile, char* extractDir, int extractDirLen)
{
    if(strlen(pathToOutputFile) + 4 >= extractDirLen)
    {
        return FALSE;
    }
    
    memset(extractDir, 0, extractDirLen);
    strcat(extractDir, pathToOutputFile);
    strcat(extractDir, ".dir");
#ifdef WIN32
    CreateDirectory(extractDir, NULL);
#else
    mkdir(extractDir, 0777);
#endif

    return TRUE;
}

BOOL createPathForFile(const char* extractDir, const char* fileName, char* outputFile, int outnameLen)
{
    if(strlen(extractDir) + strlen(fileName) + 5 >= outnameLen)
    {
        return FALSE;
    }
    memset(outputFile, 0, outnameLen);
    strcat(outputFile, extractDir);
    strcat(outputFile, "/");
    strcat(outputFile, fileName);
    strcat(outputFile, ".txt");
    
    return TRUE;
}

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

// § Filter a file
KVErrorCode filterText(KVFltInterfaceEx* filter, KVDocument document, const char* const pathToOutputFile)
{
    // § Checking if a file is supported
    KVErrorCode error = filter->fpCanFilter(document);
    
    if(error != KVError_Success)
    {
        return errorCode(filter, context, error);
    }
    
    // § Filtering a file
    return filter->fpFilterToFile(document, pathToOutputFile);
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
        //In this tutorial, we convert to char* in case the binary data contains human-readable portions.
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
                //gmtime can't handle as large a range as WinFileTime,
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
    int error = KVError_Success;
    while(1)
    {
        const KVMetadataElement* element = NULL;
        error = metadataList->fpGetNext(metadataList, &element);

        if(error != KVError_Success)
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

KVErrorCode outputMetadata(const KVMetadataList* metadataList, const char* const pathToOutputFile, const char* const title)
{
    void* fOut = fopen(pathToOutputFile, "a");

    if(!fOut)
    {
        return KVError_ErrorWritingToOutputFile;
    }

    KVErrorCode error = iterateMetadata(metadataList, fOut, title);

    fclose(fOut);

    return error;
}

// § Getting the metadata list
KVErrorCode retreiveMetadata(KVFltInterfaceEx* filter, KVDocument document, const char* const pathToOutputFile)
{
    const KVMetadataList* metadataList = NULL;
    KVErrorCode error = filter->fpGetMetadataList(document, &metadataList);

    if(error != KVError_Success)
    {
        return error;
    }

    error = outputMetadata(metadataList, pathToOutputFile, "Metadata");

    metadataList->fpFree(metadataList);

    return error;
}

// § Retrieving mail metadata
KVErrorCode retreiveSubfileMetadata(KVExtractInterfaceRec* extract, void* fileSession, int index, const char* const outputFile)
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

    error = outputMetadata(metadataList, outputFile, "Subfile metadata");

    metadataList->fpFree(metadataList);
    
    return error;
}

// § Extracting sub files
KVErrorCode filterSubfileAsFile(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, KVFilterSession session, void* fileSession, const char* const extractDir, int index, KVSubFileInfo subFileInfo)
{
    //Extract the subfile to disk
    KVExtractSubFileArgRec extractArg;
    KVStructInit(&extractArg);
    extractArg.index = index;
    extractArg.filePath = subFileInfo->subFileName;
    extractArg.extractionFlag = 
        KVExtractionFlag_CreateDir | 
        KVExtractionFlag_Overwrite | 
        KVExtractionFlag_GetFormattedBody | 
        KVExtractionFlag_SanitizeAbsolutePaths;

    KVSubFileExtractInfo extractInfo = NULL;
    KVErrorCode error = extract->fpExtractSubFile(fileSession, &extractArg, &extractInfo);

    if(error != KVError_Success)
    {
        return errorCode(filter, context, error);
    }
    
    //Work out the output file name for the subfile
    char outputFile[1024];
    if(createPathForFile(extractDir, extractInfo->fileName, outputFile, 1024))
    {
        //Send the subfile back to our top-level processing function.
        //(Recursion is used here for simplicity. You may wish to consider using a queue structure in your actual application)
        error = recursivelyFilterFile(filter, extract, session, extractInfo->filePath, outputFile);
    }
    else
    {
        error = KVError_CreateOutputFileFailed;
    }

    extract->fpFreeStruct(fileSession, extractInfo);
    
    if(error != KVError_Success)
    {
        return error;
    }
    
    return retreiveSubfileMetadata(extract, fileSession, index, outputFile);
}

// § Extracting sub files
KVErrorCode filterSubfile(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, KVFilterSession session, void* fileSession, const char* const extractDir, int index)
{
    int returnValue = 0;
    KVSubFileInfo subFileInfo = NULL;
    KVErrorCode error = extract->fpGetSubFileInfo(fileSession, index, &subFileInfo);

    if(error != KVError_Success)
    {
        return errorCode(filter, context, error);
    }

    //Folder don't contain any text, so no point processing them.
    if(subFileInfo->subFileType != KVSubFileType_Folder)
    {
        error = filterSubfileAsFile(filter, extract, session, fileSession, extractDir, index, subFileInfo);
    }
    
    extract->fpFreeStruct(fileSession, subFileInfo);
    
    return returnValue;
}

// § Opening a container
KVErrorCode filterOpenedContainer(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, KVFilterSession session, void* fileSession, const char* const extractDir)
{
    KVMainFileInfo fileInfo = NULL;
    KVErrorCode error = extract->fpGetMainFileInfo(fileSession, &fileInfo);

    if(error != KVError_Success)
    {
        return errorCode(filter, context, error);
    }

    for(int ii = 0; ii < fileInfo->numSubFiles; ++ii)
    {
        error = filterSubfile(filter, extract, session, fileSession, extractDir, ii);
        
        if(error != KVError_Success)
        {
            printf("Subfile %d failed with error %d\n", ii, returnValue);
        }
    }
    
    extract->fpFreeStruct(fileSession, fileInfo);
    
    return KVError_Success;
}

// § Extracting sub files
KVErrorCode filterContainerSubfiles(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, KVFilterSession session, KVDocument document, const char* const pathToOutputFile)
{
    char extractDir[1024];
    
    if(!createSubdirForFile(pathToOutputFile, extractDir, 1024))
    {
        printf("Could not create extract dir\n");
        return KVError_CreateOutputFileFailed;
    }
    
    // § Opening a container
    KVOpenFileArgRec openArg;
    KVStructInit(&openArg);
    openArg.extractDir = extractDir;
    openArg.document = document;

    void* fileSession = NULL;
    KVErrorCode error = extract->fpOpenFileFromFilterSession(session, &openArg, &fileSession);

    if(error != KVError_Success)
    {
        return errorCode(filter, context, error);
    }
    
    //Extract each subfile and filter it.
    error = filterOpenedContainer(filter, extract, session, fileSession, extractDir);
    
    extract->fpCloseFile(fileSession);

    return returnValue;
}


KVErrorCode recursivelyFilterFile(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, KVFilterSession session, const char* const pathToInputFile, const char* const pathToOutputFile)
{
    // § Opening a document
    KVDocument document = NULL;
    
    KVErrorCode error = filter->fpOpenDocumentFromFile(session, pathToInputFile, &document);
    
    if(error != KVError_Success)
    {
        return error;
    }
    
    //Filter the text from the current file
    KVErrorCode filterError = filterText(filter, document, pathToOutputFile);
    
    //Output metadata from the current file
    KVErrorCode metadataError = retreiveMetadata(filter, document, pathToOutputFile);
    
    //Extract each subfiles, and recursively process each one.
    KVErrorCode extractError = filterContainerSubfiles(filter, extract, session, document, pathToOutputFile);
    
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

    if(error != KVError_Success)
    {
        return error;
    }

    // § Creating a Filter session
    KVFilterInitOptions options;
    KVStructInit(&options);
    options.outputCharSet = KVCS_UTF8;
    
    error = filter->fpInit(
        YOUR_BIN_DIR,
        YOUR_LICENSE_KEY,
        &options,
        pSession);
        
    if(error != KVError_Success)
    {
         return KVERR_General; 
    }
    
    // § Loading the Extract interface
    KVStructInit(extract);
    error = filter->fpGetExtractInterface(*pSession, extract);

    if(error != KVError_Success)
    {
        return errorCode(filter, *context, error);
    }
    
    // § Filtering hidden information
    error = filter->fpSetConfig(*pSession, KVFLT_SHOWHIDDENTEXT, TRUE, NULL);
    
    if(error != KVError_Success)
    {
        return error;
    }
    
    // § Extracting sub files
    error = filter->fpSetConfig(*pSession, KVFLT_EXTRACTIMAGES, TRUE, NULL);
    
    if(error != KVError_Success)
    {
        return error;
    }
    
    return KVError_Success;
}

// § API Setup
KVErrorCode filterTutorial(const char* const pathToInputFile, const char* const pathToOutputFile)
{
    KVFltInterfaceEx filter = {0};
    KVExtractInterfaceRec extract = {0};
    KVFilterSession session = NULL;

    KVErrorCode error = setupFilterSession(&filter, &extract, &session);
    
    if(error == KVError_Success)
    {
        error = recursivelyFilterFile(&filter, &extract, session, pathToInputFile, pathToOutputFile);
    }

    if(filter.fpShutdown)
    {
        filter.fpShutdown(session);
    }
    
    return returnValue;
}


int main (int argc, char *argv[])
{
    if(argc != 3 || !argv[1] || !argv[2])
    {
        printf("Usage: tutorial_file pathToInput pathToOutput\n");
        printf("Must be run from the KeyView Filter bin directory\n");
        return KVError_General;
    }
    
    const char* const pathToInputFile = argv[1];
    const char* const pathToOutputFile = argv[2];
    
    printf("tutorial_file: sample program - not for production use\n\n");
    printf("Filtering %s to %s\n", pathToInputFile, pathToOutputFile);
    
    int returnValue = filterTutorial(pathToInputFile, pathToOutputFile);

    printf("Return code %d\n", returnValue);
    
    return returnValue;
}