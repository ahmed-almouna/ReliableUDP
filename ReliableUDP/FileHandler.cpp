/*
*   FILE           : FileHandler.cpp
*   PROJECT        : SENG2040 - Assignment A1
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

// this function opens the specified file, updates the parameters with its meta-data, and returns a pointer to it
FILE* openFile(char filename[], int* fileSize, char* fileType)
{
	FILE* fp = NULL;
	printf("Is this a Binary (B) or Text (T) file?");
	*fileType = getch();

	/* determine the type of the file & open it */
	if (*fileType == 'T' || *fileType == 't')
	{
		if ((fp = fopen(filename, "r")) == NULL)
		{
			printf("Error: can not open file.\n");
			exit(1);
		}
	}
	else if (*fileType == 'B' || *fileType == 'b')
	{
		if ((fp = fopen(filename, "rb")) == NULL)
		{
			printf("Error: can not open file.\n");
			exit(1);
		}
	}
	else
	{
		printf("Error: invalid choice.\n");
		exit(1);
	}

	*fileSize = file_size(filename);
	return fp;
}


//// this function opens the specified file, updates the parameters with its meta-data, and returns a pointer to it
//void readFile(FILE* fp, char fileType, int packetCounter, char packet[kPacketSize])
//{
//	char dataChunk[kPacketSize + 1] = "";
//
//	/* determine the type of the file & open it */
//	if (fileType == 'T' || fileType == 't')
//	{
//		while (fgets(dataChunk, kPacketSize, fp) != NULL)
//		{
//			/* check for file I/O errors */
//			if (ferror(fp))
//			{
//				printf("Error: file I/O error.\n");
//				exit(1);
//			}
//		}
//	}
//	else if (fileType == 'B' || fileType == 'b')
//	{
//
//	}
//	else
//	{
//		printf("Error: invalid file type.\n");
//		exit(1);
//	}
//
//	strcpy(packet, dataChunk);
//}

