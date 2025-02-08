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

// File class variables
FILE* File::fp = NULL;
char File::filename[kMaxFilenameLength] = "";
char File::fileType = NULL;
int File::fileSize = -1;
bool File::fileClosed = false;


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

// this function opens the specified file to obtain its meta-data and
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
		printf("Error: invalid file type.\n");
		exit(1);
	}

	fileSize = file_size(filename);
}


// this function reads the file content into packets
void File::readFile(int packetCounter, char packet[kPacketSize])
{
	/* 1st packet is file info packet */
	if (packetCounter == 1)
	{
		sprintf(packet, "%s|%s|%d|%c||", kMessageTypes[0], filename, fileSize, fileType);
		return;
	}

	/* file content packets */
	char dataChunk[kPacketSize] = "";
	char counterAsString[kGenericStringLength] = "";
	sprintf(counterAsString, "%d", packetCounter);
	int headerLength = strlen(kMessageTypes[1]) + strlen(counterAsString) + 6; // 6 is the 3 pipes + 3 digit placeholder for content length.

	if (fileType == 'T' || fileType == 't')
	{
		if (fgets(dataChunk, kPacketSize - headerLength, fp) != NULL)
		{
			sprintf(packet, "%s|%d|%zu|%s", kMessageTypes[1], packetCounter, strlen(dataChunk), dataChunk);
		}
		else // all done packet
		{
			//sprintf(packet, "%s|%d||", kMessageTypes[2], ); //needs checksum
			if (!fileClosed)
				closeFile(fp);
		}
	}
	else if (fileType == 'B' || fileType == 'b')
	{
		int bytesRead = -1;
		if ((bytesRead = fread(dataChunk, sizeof(byte), kPacketSize - headerLength, fp)) > 0)
		{
			sprintf(packet, "%s|%d|%d|", kMessageTypes[1], packetCounter, bytesRead);
			memcpy(packet + strlen(packet), dataChunk, bytesRead);
		}
		else
		{
			//sprintf(packet, "%s|%d||", kMessageTypes[2], ); //needs checksum
			if (!fileClosed)
				closeFile(fp);
		}
	}
	else
	{
		printf("Error: invalid file type.\n");
		exit(1);
	}
}

// this function is called to receive the packets and create the file on the server
void File::receiveFile(char packet[kPacketSize])
{
	char tokens[4][kPacketSize] = { "" };

	/* 1st packet is file info message */
	if (strncmp(packet, kMessageTypes[0], strlen(kMessageTypes[0])) == 0)
	{
		splitString(packet, 4, tokens);
		strcpy(filename, tokens[1]);
		fileSize = atoi(tokens[2]);
		fileType = *tokens[3];
		createFile();
	}

	/* file content packets */
	else if (strncmp(packet, kMessageTypes[1], strlen(kMessageTypes[1])) == 0)
	{
		if (fileType == 'T' || fileType == 't')
		{
			splitString(packet, 4, tokens);

			if (fprintf(fp, "%s", tokens[3]) < 0)
			{
				printf("Error: unable to write to file.\n");
				exit(1);
			}
		}
		else if (fileType == 'B' || fileType == 'b')
		{
			splitString(packet, 3, tokens);
			int headerLength = strlen(kMessageTypes[1]) + strlen(tokens[1]) + strlen(tokens[2]) + 3;
			if (fwrite(packet + headerLength, sizeof(byte), atoi(tokens[2]), fp) < 0)
			{
				printf("Error: unable to write to file.\n");
				exit(1);
			}
		}
		else
		{
			printf("Error: invalid file type.\n");
			exit(1);
		}
	}

	/* all done packet */
	else if (strncmp(packet, kMessageTypes[2], strlen(kMessageTypes[2])) == 0)
	{
		// check if checksum matches
		closeFile(fp);
	}
}

// this function splits a packet into the inidifual tokens that make it up
void File::splitString(char packet[kPacketSize], int maxTokens, char tokens[4][kPacketSize])
{
	char packetCopy[kPacketSize] = "";
	memcpy(packetCopy, packet, strlen(packet));

	char* token = strtok(packetCopy, "|");
	int i = 0;

	while (token != NULL)
	{
		if (i >= maxTokens)
		{
			break;
		}

		memcpy(tokens[i], token, strlen(token));
		token = strtok(NULL, "|");
		i++;
	}
}

// this function creates the file on the server
void File::createFile(void)
{
	/* determine file type & create it */
	if (fileType == 'T' || fileType == 't')
	{
		if ((fp = fopen(filename, "w")) == NULL)
		{
			printf("Error: can not open file.\n");
			exit(1);
		}
	}
	else if (fileType == 'B' || fileType == 'b')
	{
		if ((fp = fopen(filename, "wb")) == NULL)
		{
			printf("Error: can not open file.\n");
			exit(1);
		}
	}
	else
	{
		printf("Error: invalid file type.\n");
		exit(1);
	}
}

// this function closes a file
void File::closeFile(FILE* fp)
{
	if (fclose(fp) != 0)
	{
		printf("Error: Unable to close file.\n");
		exit(1);
	}
	fileClosed = true;
}