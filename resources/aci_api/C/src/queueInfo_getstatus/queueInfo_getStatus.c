#include "client.h"
#include "client_defs.h"
#include "queueInfo_getStatus.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Prints program usage information to standard output
void displayusageinfo()
{
	printf("Usage: getStatus <HOSTNAME/IP> <ACI_PORT_#> <QUEUE_NAME> [<TOKEN>]\n");
	printf("Parameters:\n");
	printf("    <HOSTNAME/IP>	Hostname / IP address of ACI service.\n");
	printf("    <ACI_PORT_#>	ACI port number of ACI service.\n");
	printf("    <QUEUE_NAME>	Queue name - e.g. fetch.\n");
	printf("    [<TOKEN>]		Optional. Asynchronous action token.\n");
}

int main(int argc, char** argv)
{
	printf("Program loaded.\n");
	
	if (argc == EXPECTED_MIN_NUM_ARGS)
	{
		printf("ACI Host: %s\n", argv[1]);
		printf("ACI Port: %s\n", argv[2]);
		printf("Queue Name: %s\n", argv[3]);
	}
	else if (argc == EXPECTED_MAX_NUM_ARGS)
	{
		printf("ACI Host: %s\n", argv[1]);
		printf("ACI Port: %s\n", argv[2]);
		printf("Queue Name: %s\n", argv[3]);
		printf("Token: %s\n", argv[4]);
	}
	else
	{
		printf("Error: Program requires at least three arguments.\n");
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
	printf("Queue Name: %s\n", argv[3]);

	if (argc == EXPECTED_MAX_NUM_ARGS)
	{
		printf("Token: %s\n", argv[4]);
	}
	
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
	aciObjectParamSetString(pCommand, ACI_COM_COMMAND, "QUEUEINFO");
	
	// Set http method
	aciObjectParamSetBool(pCommand, ACI_COM_USE_POST,FALSE);

	// Set action parameters
	aciObjectParamSetString(pCommand, "queueName", argv[3]);
	aciObjectParamSetString(pCommand, "queueAction", "getStatus");
	if (argc == EXPECTED_MAX_NUM_ARGS)
	{
		aciObjectParamSetString(pCommand, "token", argv[4]);
	}
	aciObjectParamSetString(pCommand, "responseFormat", "xml");

	aciObjectToString(pCommand);

	printf("\nExecuting action...\n");

	aciError aci_status;
	
	// token is optional. if omitted then simply print entire response
	if (argc == EXPECTED_MAX_NUM_ARGS) 
	{		
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
			
			// Get status and print it
			t_aciObject* status = NULL;
			status = acioFindFirstOccurrence(pResult, "status");
			if (status)
			{
				char *szStatus = NULL;
				aci_status = acioParamGetString(status, ACI_DATA_NODE_VALUE, &szStatus);
				if (aci_status == ACICONTENT_SUCCESS) 
				{
					printf("Queue Name: %s.\nToken: %s.\nStatus: %s\n", argv[3], argv[4], szStatus);
				} else {
					printf("Error! ACI Status: %d\n", aci_status);
					exit(1);
				}
			}
		} else {
			printf("Error! ACI Status: %d\n", aci_status);
			exit(1);
		}

		// Remember to tidy up afterwards
		aciObjectDestroy(&pResult);
	} else {
		char *szResponse = NULL;
		int nResponseLen = 0;
		char *szContentType = NULL;
		aci_status = aciObjectExecuteToString(pConnection, pCommand, &szResponse, &nResponseLen, &szContentType);

		if (aci_status == ACICONTENT_SUCCESS)
		{
			printf("Success!\n");
			
			// For most actions, szResponse now holds the raw xml and szContentType will be "application/xml"
			// Process the xml in whatever way you wish now (e.g. third-party XML processing API)
			printf("Response length: %d, ContentType: %s\n", nResponseLen, szContentType);
			printf("Response: %s\n", szResponse);
		} else {
			printf("Error! ACI Status: %d\n", aci_status);
			exit(1);
		}

		// Remember to tidy up afterwards
		free(szResponse);
		free(szContentType);
	}
	
	exit(0);
}
