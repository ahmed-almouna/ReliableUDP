/*
*   FILE           : FileHandler.h
*   PROJECT        : SENG2040 - Assignment A1
*   PROGRAMMERS    : Ray & Ahmed
*   FIRST VERSION  : 2/3/2025
*   DESCRIPTION    :
*     The header file for FileHandler.cpp where all the necessary libraries, prototypes, and constants are.
*/

// pragma statements
#pragma once
#pragma warning(disable: 4996)

// include statements
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <conio.h>

// namespaces
using namespace std;
using namespace filesystem;

// constants
const int kMaxFilenameLength = 100;
const int kGenericStringLength = 100;
const int kPacketSize = 256;
const char kMessageTypes[3][3] = {"FI", "FC", "AD"};

// class
class File
{
	private:
		static FILE* fp;
		static char filename[kMaxFilenameLength];
		static char fileType;
		static int fileSize;

	public:
		// prototypes
		static void getFilename(void);
		static void openFile(void);
		static void readFile(int packetCounter, char packet[kPacketSize + 1]);
};
