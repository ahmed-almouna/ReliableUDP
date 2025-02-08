///*
//*   FILE           : FileTransfer.cpp
//*   PROJECT        : SENG2040 - Assignment A1
//*   PROGRAMMERS    : Ray & Ahmed
//*   FIRST VERSION  : 2/3/2025
//*   DESCRIPTION    : All the necessary functions to handle the receiving and reassembly of the files from the sender.
//*					 Receives packets, processes the metadata and writes to the file.
//*/
//
//#include "FileHandler.h"
//#include "ReliableUDP.h"
//#include <iostream>
//#include <fstream>
//#include <chrono> // Timing speed calculation
//
//using namespace std;
//
//// Open file for writing in binary mode
//void receiveFile(FILE* receivedFile, ReliableConnection& connection) {
//    if (!receivedFile) {
//        cerr << "Error: File pointer is NULL!" << endl;
//        return;
//    }
//
//    unsigned char packet[kPacketSize];  // Packet buffer
//    int bytesReceived;
//    auto startTime = chrono::high_resolution_clock::now();  // Start timing transfer
//
//    long totalBytesReceived = 0; // Track total bytes received
//
//    while (true) {
//        // Receive packets 
//        bytesReceived = connection.ReceivePacket(packet, sizeof(packet));
//
//        if (bytesReceived <= 0) {
//            break;  // Exit when no more data is received
//        }
//
//        // Write packet data to the file
//        fwrite(packet, 1, bytesReceived, receivedFile);
//        totalBytesReceived += bytesReceived;
//    }
//
//    auto endTime = chrono::high_resolution_clock::now();  // End time
//
//    // Calculate transfer time
//    auto duration = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
//    double transferTimeInSeconds = duration.count() / 1000.0;
//
//    // Calculate transfer speed in megabits per second
//    double transferSpeed = (totalBytesReceived * 8.0) / (1024 * 1024 * transferTimeInSeconds);
//
//    cout << "File received successfully in " << transferTimeInSeconds << " seconds." << endl;
//    cout << "Transfer speed: " << transferSpeed << " Mbps" << endl;
//
//    fclose(receivedFile);
//}