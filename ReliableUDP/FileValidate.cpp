/*
*   FILE           : FileValidate.cpp
*   PROJECT        : SENG2040 - Assignment A1
*   PROGRAMMERS    : Ray & Ahmed
*   FIRST VERSION  : 2/3/2025
*   DESCRIPTION    : Verify the integrity of the file using checksums and ensure the file is not corrupted during transfer.
*/

#include "FileHandler.h"
#include <iostream>
#include <fstream>
#include  <openssl/md5.h>

// Calculate the MD5 checksum of a file without strings. Maybe MD5?
void calculateMD5(const char* filename, unsigned char* MD5) {
	MD5_CTX mdContext; // store hash value

}

// function to verify the integrity of the file. Are we using 

