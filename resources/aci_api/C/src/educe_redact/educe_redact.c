#include "client.h"
#include "client_defs.h"
#include "educe_redact.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Prints program usage information to standard output
void displayusageinfo()
{
	printf("Usage: educe_redact e|r <HOSTNAME/IP> <ACI_PORT_#> <ENTITIES_CSV> <TEXT>\n");
	printf("Parameters:\n");
	printf("	e|r		Select  mode - e(duce) or r(edaction");
	printf("    <HOSTNAME/IP>		Hostname / IP address of ACI service.\n");
	printf("    <ACI_PORT_#>		ACI port number of ACI service.\n");
	printf("    <ENTITIES_CSV>		CSV of entities to use.\n");
	printf("    <TEXT>	Text to process.\n");
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
	aciObjectParamSetString(pConnection, ACI_HOSTNAME, argv[2]);
	aciObjectParamSetInt(pConnection, ACI_PORTNUMBER, atoi(argv[3]));
	aciObjectParamSetInt(pConnection, ACI_CONN_RETRIES, 3);

	aciObjectToString(pConnection);
	printf("Mode: %s\n", argv[1]);
	printf("Entities: %s\n", argv[4]);
	printf("Text: %s\n", argv[5]);

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
	const char* command;
	if (!strcmp(argv[1], "e")) {
		command = "EDUCEFROMTEXT";
	} else if (!strcmp(argv[1], "r")) {
		command = "REDACTFROMTEXT";
	} else {
		printf("Invalid mode: %s\n", argv[1]);
		exit(1);		
	}

	aciObjectParamSetString(pCommand, ACI_COM_COMMAND, command);
	
	// Set http method
	aciObjectParamSetBool(pCommand, ACI_COM_USE_POST, FALSE);

	// Set action parameters
	aciObjectParamSetString(pCommand, "entities", argv[4]);
	aciObjectParamSetString(pCommand, "text", argv[5]);
	aciObjectParamSetString(pCommand, "responseFormat", "xml");

	aciObjectToString(pCommand);

	printf("\nExecuting action...\n");

	aciError aci_status;
	char *szResponse = NULL;
	int nResponseLen = 0;
	char *szContentType = NULL;
	aci_status = aciObjectExecuteToString(pConnection, pCommand, &szResponse, &nResponseLen, &szContentType);

	printf("Handling response...\n");
	
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
	exit(0);
}
