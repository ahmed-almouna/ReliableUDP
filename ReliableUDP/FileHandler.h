/*
*   FILE           : FileHandler.h
*   PROJECT        : SENG2040 - Assignment A1
*   PROGRAMMERS    : Ray & Ahmed
*   FIRST VERSION  : 2/3/2025
*   DESCRIPTION    :
*     The header file for FileHandler.cpp where all the necessary libraries, prototypes, namespaces, etc. are found.
*/

// pragma statements
#pragma once
#pragma warning(disable: 4996)

// include statements
#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>

// namespaces
using namespace std;
using namespace filesystem;

// constants
const int kMaxFilenameLength = 100;
const int kGenericStringLength = 100;
const int kPacketSize = 256;
const char kMessageTypes[3][3] = {"FI", "FC", "AD"};

// File class
class File
{
	private:
		static FILE* fp;
		static char filename[kMaxFilenameLength];
		static char fileType;
		static int fileSize;
		static bool fileClosed;

		// class functions
		static void closeFile(FILE* fp);
		static void splitString(char packet[kPacketSize], int maxTokens, char tokens[4][kPacketSize]);
		static void createFile(void);

	public:
		// client-related
		static void getFilename(void);
		static void openFile(void);
		static void readFile(int packetCounter, char packet[kPacketSize]);

		// server-related
		static void receiveFile(char packet[kPacketSize]);
};