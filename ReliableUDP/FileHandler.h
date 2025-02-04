/*
*   FILE           : FileHandler.h
*   PROJECT        : SENG2040 - Assignment A1
*   PROGRAMMERS    : Ray & Ahmed
*   FIRST VERSION  : 2/3/2025
*   DESCRIPTION    :
*     The header file for FileHandler.cpp where all the necessary libraries, prototypes, and constants are.
*/

//pragma statments
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
const int kPacketSize = 256;

// prototypes
void getFilename(char fileName[]);
FILE* openFile(char filename[], int* fileSize, char* fileType);
void readFile(FILE* fp, char fileType, int packetCounter, char packet[kPacketSize]);