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

// static variables
FILE* File::fp = NULL;
char File::filename[kMaxFilenameLength] = "";
char File::fileType = NULL;
int File::fileSize = -1;



// this function prompts the user for the file they want to send
void File::getFilename(void)
{
	char userInput[kMaxFilenameLength] = "";

	/* get filename from user */
	printf("Enter name of file to send: ");
	fgets(userInput, sizeof(userInput), stdin);

	/* check if a filename was provided */
	if (sscanf(userInput, "%s", &filename) != 1)
	{
		printf("Error: a filename was not provided.\n\n");
		exit(1);
	}

	/* remove newline character (\n) from filename */
	if (strchr(filename, '\n') != NULL)
	{
		filename[strlen(filename) - 1] = '\0';
	}
}

// this function opens the specified file to obtain its meta-data
void File::openFile(void)
{
	printf("Is this a Binary (B) or Text (T) file?");
	fileType = getch();

	/* determine file type & open it */
	if (fileType == 'T' || fileType == 't')
	{
		if ((fp = fopen(filename, "r")) == NULL)
		{
			printf("Error: can not open file.\n");
			exit(1);
		}
	}
	else if (fileType == 'B' || fileType == 'b')
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

	fileSize = file_size(filename);
}


// this function 
void File::readFile(int packetCounter, char packet[kPacketSize + 1])
{
	/* 1st packet is file info message */
	if (packetCounter == 1)
	{
		sprintf(packet, "%s|%s|%d||", kMessageTypes[0], filename, fileSize);
		return;
	}

	/* rest of the packets is for file content */
	char dataChunk[kPacketSize + 1] = "";
	char counterAsString[kGenericStringLength] = "";
	sprintf(counterAsString, "%d", packetCounter);
	int headerLength = strlen(kMessageTypes[1]) + strlen(counterAsString) + 6; // 6 is the 3 pipes + 3 digit number for content length.

	if (fileType == 'T' || fileType == 't')
	{
		if (fgets(dataChunk, kPacketSize - headerLength, fp) != NULL)
		{
			if (ferror(fp))
			{
				printf("Error: file I/O error.\n");
				exit(1);
			}

			sprintf(packet, "%s|%d|%ulld|%s", kMessageTypes[1], packetCounter, strlen(dataChunk), dataChunk); //note try ulld instead of %d
		}
		else // last packet (All done packet)
		{
			//sprintf(packet, "%s|%d||", kMessageTypes[2], ); //needs checksum
		}
	}
	else if (fileType == 'B' || fileType == 'b')
	{
		if (fread(dataChunk, sizeof(byte), kPacketSize - headerLength, fp) > 0)
		{
			sprintf(packet, "%s|%d|%d|%s", kMessageTypes[1], packetCounter, strlen(dataChunk), dataChunk); //treating binary data as a string might be an issue
		}
		else
		{
			//sprintf(packet, "%s|%d||", kMessageTypes[2], ); //needs checksum
		}
	}
	else
	{
		printf("Error: invalid file type.\n");
		exit(1);
	}
}

