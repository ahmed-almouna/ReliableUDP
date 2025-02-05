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

using namespace std;

// Calculate the MD5 checksum of a file without strings. Maybe MD5?
void calculateMD5(const char* filename, unsigned char* MD5) {
	MD5_CTX mdContext; // store hash value
	File* file = fopen(filename, "rb"); // read in binary

	if (file == nullptr) {
		cerr << "Error: Could not open the file." << endl;
		exit(1);
	}

	MD5_Init(&mdContext); // initalize/reset mdContext

	char buffer[1024];
	int bytes;
	while ((bytes = fread(buffer, 1, 1024, file) != 0) {
		MD5_Update(&mdContext, buffer, bytes); // update the MD5 with the data in the buffer
	}

	MD5_Final(md5Digest, &mdContext); // finalize MD5 calculation and store result into md5Digest
	fclose(file);
}

// function to verify the integrity of the file
bool verifyFileIntegrity(const char* receivedFilename, const unsigned char* expectedChecksum) {
	unsigned char actualChecksum[MD5_DIGEST]; // array to hold checksum of file
	calculateMD5(receivedFilename, actualChecksum); // calculate checksum of received file, store in actualChecksum

	// Compare the byte arrays
	for (int i = 0, i < MD5_DIGEST; i++) {
		if (actualChecksum[i] != expectedChecksum[i]) {
			cerr << "Error: File integrity check failed." << endl;
			return false;
		}
	}

	cout << "File integrity verified successfully." << endl;
	return true;
}

// Entry
int main() {
	char receivedFilename[kMaxFilename];
	unsigned char expectedChecksum[MD5_DIGEST];

	cout << "Enter filename to verify: ";
	cin >> recievedFilename;

	// I think the sender calculates the checksum first, so put it here at assign it to expectedChecksum. Assume for now that the checksum is sent as sentChecksum.
	memcpy(expectedChecksum, sentChecksum, MD5_DIGEST);

	bool integrityPassed = verifyFileIntegrity(recievedFilename, expectedChecksum);

	if (!integrityPassed) {
		// This means the integrity check failed
	}
}