#include "client.h"
#include "client_defs.h"
#include "fetch_insert.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Prints program usage information to standard output
void displayusageinfo()
{
	printf("Usage: fetch_insert <HOSTNAME/IP> <ACI_PORT_#> <TASK_NAME> <INSERT_XML_FILE>\n");
	printf("Parameters:\n");
	printf("    <HOSTNAME/IP>		Hostname / IP address of ACI service.\n");
	printf("    <ACI_PORT_#>		ACI port number of ACI service.\n");
	printf("    <TASK_NAME>		Fetch task name.\n");
	printf("    <INSERT_XML_FILE>	Insert XML file.\n");
}

int main(int argc, char** argv)
{
	printf("Program loaded.\n");
	if (argc != EXPECTED_NUM_ARGS)
	{
		printf("Error: Program requires four arguments.\n");
		displayusageinfo();
		exit(1);
	}

	aciInit();

	// Create the connection object
	t_aciObject* pConnection = NULL;
	aciObjectCreate(&pConnection, ACI_CONNECTION);

	// Set host details
	aciObjectParamSetString(pConnection, ACI_HOSTNAME, argv[1]);
	aciObjectParamSetInt(pConnection, ACI_PORTNUMBER, atoi(argv[2]));
	aciObjectParamSetInt(pConnection, ACI_CONN_RETRIES, 3);

	aciObjectToString(pConnection);
	printf("Task Name: %s\n", argv[3]);
	printf("InsertXML file: %s\n", argv[4]);

	// Initialize OEM licensing
	if (USE_IDOL_OEM_ENCRYPTION)
	{
		/* TODO: Look at using Windows only _dupenv_s() and then turn-off _CRT_SECURE_NO_WARNINGS */
		char *key = getenv(IDOL_OEM_ENCRYPTION_KEY_ENV_VAR);

		if (key != NULL)
		{
			printf("\nUsing OEM encryption key from environment variable: %s\n", IDOL_OEM_ENCRYPTION_KEY_ENV_VAR);
			if (!strcmp(key, IDOL_OEM_ENCRYPTION_KEY_STUB_VALUE))
			{
				printf("Don't forget to correctly set %s\n", IDOL_OEM_ENCRYPTION_KEY_ENV_VAR);
				printf("Invalid OEM encryption key\n");
				exit(1);
			} else {
				aciInitEncryption(TRUE, "TEA", key);
			}
		} else {
			printf("\nUsing OEM encryption key from getStatus.h\n");
			if (!strcmp(IDOL_OEM_ENCRYPTION_KEY, IDOL_OEM_ENCRYPTION_KEY_STUB_VALUE)) {
				printf("Don't forget to correctly set constant: IDOL_OEM_ENCRYPTION_KEY\n");
				printf("Invalid OEM encryption key\n");
				exit(1);
			} else {
				aciInitEncryption(TRUE, "TEA", IDOL_OEM_ENCRYPTION_KEY);
			}
		}
	}

	// Create the command object
	t_aciObject* pCommand = NULL;
	aciObjectCreate(&pCommand, ACI_COMMAND);

	// Set command to execute
	aciObjectParamSetString(pCommand, ACI_COM_COMMAND, "FETCH");
	
	// Set http method
	aciObjectParamSetBool(pCommand, ACI_COM_USE_POST, FALSE);

	// get insertXML data
	// errors handled in get_insertXML_file(). all are fatal and exit();
	char * insertXML;
	size_t f_size;
	insertXML = get_insertXML_file(argv[4], &f_size);

	// Set action parameters
	aciObjectParamSetString(pCommand, "fetchAction", "insert");
	aciObjectParamSetString(pCommand, "configSection", argv[3]);
	aciObjectParamSetString(pCommand, "insertXML", insertXML);
	aciObjectParamSetString(pCommand, "responseFormat", "xml");

	aciObjectToString(pCommand);

	printf("\nExecuting action...\n");

	aciError aci_status;
	t_aciObject *pResult = NULL;
	aci_status = aciObjectExecute(pConnection, pCommand, &pResult);

	printf("Handling response...\n");

	if (aci_status == ACICONTENT_SUCCESS)
	{
		printf("Got response!\n");

		// Get <response> and print it
		t_aciObject* response = NULL;
		response = acioFindFirstOccurrence(pResult, "response");
		if (response)
		{
			char *szResponse = NULL;
			aci_status = acioParamGetString(response, ACI_DATA_NODE_VALUE, &szResponse);
			if (aci_status == ACICONTENT_SUCCESS) 
			{
				printf("response: %s\n", szResponse);
				
				// A successful communications response occurred.
				// Now need to need if the action response is ok.
				if (strcmp(szResponse, "SUCCESS")) 
				{
					// Get <errorstring> and print it
					t_aciObject* errorString = NULL;
					errorString = acioFindFirstOccurrence(pResult, "errorstring");
					if (errorString)
					{
						char *szErrorString = NULL;
						aci_status = acioParamGetString(errorString, ACI_DATA_NODE_VALUE, &szErrorString);
						if (aci_status == ACICONTENT_SUCCESS) 
						{
							printf("Error string: %s\n", szErrorString);
							exit(1);
						}
					}
				}
			} else {
				printf("Error! ACI Status: %d\n", aci_status);
				exit(1);
			}
		}
		
		// Get token and print it
		t_aciObject* token = NULL;
		token = acioFindFirstOccurrence(pResult, "token");
		if (token)
		{
			char *szToken = NULL;
			aci_status = acioParamGetString(token, ACI_DATA_NODE_VALUE, &szToken);
			if (aci_status == ACICONTENT_SUCCESS) 
			{
				printf("Token: %s\n", szToken);
			} else {
				printf("Error! ACI Status: %d\n", aci_status);
				exit(1);
			}
		}
	} else {
		printf("Error! ACI Status: %d\n", aci_status);
	}

	// Remember to tidy up afterwards
	free(insertXML);
	aciObjectDestroy(&pResult);
	exit(0);
}

char* get_insertXML_file(const char* path, size_t* f_size)
{
	char* insertXML;
	size_t length;
	FILE* f = fopen(path, "rb");
	size_t read_length;

	if (f) {
		fseek(f, 0, SEEK_END);	
		length = ftell(f);
		fseek(f, 0, SEEK_SET);	

		if (length > MAX_INSERT_XML_SIZE_BYTES)
		{
			printf("Error! insert XML file is too large: %d\n", MAX_INSERT_XML_SIZE_BYTES);
			exit(1);
		}

		insertXML = (char *)malloc(length + 1);
		if (length)
		{
			read_length = fread(insertXML, 1, length, f);
			if (length != read_length)
			{
				free(insertXML);
				printf("Error! Problem reading insert XML file\n");
				exit(1);
			}
		}

		fclose(f);
		insertXML[length] = '\0';

	} else {
		printf("Error! insert XML path is invalid\n");
		exit(1);
	}


	return insertXML;
}
