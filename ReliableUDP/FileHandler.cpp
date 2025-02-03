/*
*   FILE           : FileHandler.cpp
*   PROJECT        : PROG1385 - Assignment A1
*   PROGRAMMERS    : Ray & Ahmed
*   FIRST VERSION  : 2/3/2025
*   DESCRIPTION    :
*     The functions in this file are for handling general file I/O operations such as opening, reading, closing, etc.
*/

// include files
#include "FileHandler.h"


// this function prompts the user for a filename and copies it to the 1st parameter
void getFilename(char fileName[])
{
	char userInput[kMaxFilenameLength] = "";
	char filename[kMaxFilenameLength] = "";

	/* get user filename */
	printf("Enter name of file to send: ");
	fgets(userInput, sizeof(userInput), stdin);

	/* check if a filename was provided */
	if (sscanf(userInput, "%s", &filename) != 1)
	{
		printf("Error: a filename was not provided.\n\n");
		getFilename(userInput);
	}

	/* remove newline character (\n) from filename */
	if (strchr(userInput, '\n') != NULL)
	{
		userInput[strlen(userInput) - 1] = '\0';
	}

	strcpy(fileName, userInput);
}