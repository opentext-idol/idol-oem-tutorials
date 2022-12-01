/*

§ Building the sample program

Edit tutorial.h to modify:
- your license key information: YOUR_LICENSE_ORGANIZATION and YOUR_LICENSE_KEY, and
- the location of the KeyView bin directory: YOUR_BIN_DIR.

§ Linking Against KeyView Filter SDK

Example compilation commands. Be sure you set KEYVIEW_HOME environment variable with the installation location (e.g. C:\MicroFocus\KeyviewFilterSDK-12.13.0):

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
#ifndef WIN32
#include <dlfcn.h>
#include <sys/stat.h>
#endif

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

/* § Handling Extended Errors */
int errorCode(KVFltInterfaceEx* filter, void* context, KVErrorCode error)
{
    if(error == KVERR_General)
	{
		return filter->fpGetKvErrorCodeEx(context);
    }

    return error;
}

/* § Filter A File */
int filterText(KVFltInterfaceEx* filter, void* context, const char* const pathToInputFile, const char* const pathToOutputFile)
{
    /* § Checking A File Is Supported */
    KVErrorCode error = filter->fpCanFilterFile(context, (char*)pathToInputFile);
    
    if(error != KVERR_Success)
    {
        return errorCode(filter, context, error);
    }
    
    /* § Filtering A File */
    error = filter->fpFilterFile(context, (char*)pathToInputFile, (char*)pathToOutputFile, NULL);

    return errorCode(filter, context, error);
}

/* § Extracting Subfiles */
int filterSubfileAsFile(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, void* context, void* fileContext, const char* const extractDir, int index, KVSubFileInfo subFileInfo)
{
    //Extract the subfile to disk
    KVExtractSubFileArgRec extractArg;
    KVStructInit(&extractArg);
    extractArg.index = index;
    extractArg.extractionFlag = KVExtractionFlag_CreateDir | KVExtractionFlag_Overwrite;
    extractArg.filePath = subFileInfo->subFileName;

    KVSubFileExtractInfo extractInfo = NULL;
    KVErrorCode error = extract->fpExtractSubFile(fileContext, &extractArg, &extractInfo);

    if(error != KVERR_Success)
    {
        return errorCode(filter, context, error);
    }
    
    //Work out the output file name for the subfile
    char outputFile[1024];
    if(!createPathForFile(extractDir, extractInfo->fileName, outputFile, 1024))
    {
        return KVERR_CreateOutputFileFailed;
    }
    
    //Send the subfile back to our top-level processing function.
    //(Recursion is used here for simplicity. You may wish to consider using a queue structure in your actual application)
    int returnValue = recursivelyFilterFile(filter, extract, context, extractInfo->filePath, outputFile);

    extract->fpFreeStruct(fileContext, extractInfo);
    
    return returnValue;
}

/* § Extracting Subfiles */
int filterSubfile(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, void* context, void* fileContext, const char* const extractDir, int index)
{
    int returnValue = 0;
    KVSubFileInfo subFileInfo = NULL;
    KVErrorCode error = extract->fpGetSubFileInfo(fileContext, index, &subFileInfo);

    if(error != KVERR_Success)
    {
        return errorCode(filter, context, error);
    }

    //Folder don't contain any text, so no point processing them.
    if(subFileInfo->subFileType != KVSubFileType_Folder)
    {
        returnValue = filterSubfileAsFile(filter, extract, context, fileContext, extractDir, index, subFileInfo);
    }
    
    extract->fpFreeStruct(fileContext, subFileInfo);
    
    return returnValue;
}

/* § Opening A Container */
int filterOpenedContainer(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, void* context, void* fileContext, const char* const extractDir)
{
    KVMainFileInfo fileInfo = NULL;
    KVErrorCode error = extract->fpGetMainFileInfo(fileContext, &fileInfo);

    if(error != KVERR_Success)
    {
        return errorCode(filter, context, error);
    }

    for(int ii = 0; ii < fileInfo->numSubFiles; ++ii)
    {
        int returnValue = filterSubfile(filter, extract, context, fileContext, extractDir, ii);
        
        if(returnValue != KVERR_Success)
        {
            printf("Subfile %d failed with error %d\n", ii, returnValue);
        }
    }
    
    extract->fpFreeStruct(fileContext, fileInfo);
    
    return KVERR_Success;
}

/* § Extracting Subfiles */
int filterContainerSubfiles(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, void* context, const char* const pathToInputFile, const char* const pathToOutputFile)
{
    char extractDir[1024];
    
    if(!createSubdirForFile(pathToOutputFile, extractDir, 1024))
    {
        printf("Could not create extract dir\n");
        return KVERR_CreateOutputFileFailed;
    }
    
    /* § Opening A Container */
    KVOpenFileArgRec        openArg;
    KVStructInit(&openArg);
    openArg.extractDir = extractDir;
    openArg.filePath = (char*)pathToInputFile;

    void* fileContext = NULL;
    KVErrorCode error = extract->fpOpenFile(context, &openArg, &fileContext);

    if(error != KVERR_Success)
    {
        return errorCode(filter, context, error);
    }
    
    //Extract each subfile and filter it.
    int returnValue = filterOpenedContainer(filter, extract, context, fileContext, extractDir);
    
    extract->fpCloseFile(fileContext);

    return returnValue;
}

int recursivelyFilterFile(KVFltInterfaceEx* filter, KVExtractInterfaceRec* extract, void* context, const char* const pathToInputFile, const char* const pathToOutputFile)
{
    //Filter the text from the current file
    int filterReturn = filterText(filter, context, pathToInputFile, pathToOutputFile);
    
    //Extract each subfiles, and recursively process each one.
    int extractReturn = filterContainerSubfiles(filter, extract, context, pathToInputFile, pathToOutputFile);
    
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
    KVFltInterfaceEx filter = {0};
    KVExtractInterfaceRec extract = {0};
    void* context = NULL;

    int returnValue = setupFilterSession(&filter, &extract, &context);
    
    if(returnValue == KVERR_Success)
    {
        returnValue = recursivelyFilterFile(&filter, &extract, context, pathToInputFile, pathToOutputFile);
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
        printf("Usage: tutorial_file pathToInput pathToOutput\n");
        printf("Must be run from the KeyView Filter bin directory\n");
        return KVERR_General;
    }
    
    const char* const pathToInputFile = argv[1];
    const char* const pathToOutputFile = argv[2];
    
    printf("tutorial_file: sample program - not for production use\n\n");
    printf("Filtering %s to %s\n", pathToInputFile, pathToOutputFile);
    
    int returnValue = filterTutorial(pathToInputFile, pathToOutputFile);

    printf("Return code %d\n", returnValue);
    
    return returnValue;
}