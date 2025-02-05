/*
*   FILE           : FileTransfer.cpp
*   PROJECT        : SENG2040 - Assignment A1
*   PROGRAMMERS    : Ray & Ahmed
*   FIRST VERSION  : 2/3/2025
*   DESCRIPTION    : All the necessary functions to handle the receiving and reassembly of the files from the sender.
*					 Receives packets, processes the metadata and writes to the file.
*/

#include "FileHandler.h"
#include "ReliableUDP.h"
#include <iostream>
#include <ftsream>

using namespace std;

void receiveFile(const char* outputFileName) 
	FILE* receivedFile = nullptr;
	char packet[kPacketSize]; // initialize packet buffer
	int packetCounter = 0;

	// Set up some sort of receiver here to listen for incoming packets

	// Open file to store the data in binary mode? safer this way
	receivedFile = fopen(outputFilename, 'wb');

	// just theoretical for now
	if (receivedFile == NULL) {
		cerr << "Error: Could not open file." << endl;
		exit(1);
	}

	// Loop for receiving and writing file data in the packets
	while (true) {
		// count the bytes

		// if the bytes received is less than or = 0, EoF error
	}

	// Write packets to file (in binary)

	// Close the file
	fclose(receivedFile);

	cout << "File received successfully." << endl; 
}

// Entry for receiving a file
int main() {
	charOutputFilename[kMaxFileLength];
	cout << "Enter the name of the file: ";
	cin >> outputFileName;

	return 0;
}