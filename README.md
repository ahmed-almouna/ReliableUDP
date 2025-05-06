# ReliableUDP

User Datagram Protocol (UDP) made reliable for the purpose of sending and receiving files.

## Features:
- Ensures complete and correct file delivery.
- Built using C with custom reliability mechanisms.
- Supports sending and receiving any file type including binary and text files.
  
## Getting Started
* Running the program using Visual Studio is not required but is recommended.

### Installation

* Download and extract the zip folder, or clone the repository `git clone https://github.com/ahmed-almouna/ReliableUDP.git`.
* Open the installed folder.
* Run the program by executing ReliableUDP.exe in a terminal or running the solution in Visual Studio.

## Usage
Running the program with no arguments; you will assume the role of the receiver i.e. you'll be open for anyone sending files to your IP address on port ***30000***.

Running the program with an IP address argument; you will assume the role of a sender and be able to send files.

For example:

Assuming a receiver is running on 172.2.16.10; run the following
   ```
   ReliableUDP.exe 172.2.16.10
   ```
You will be asked to enter the name of the file to send (must be in your *current directory*). And whether the file is a binary [e.g jpg] or a text [e.g .txt] file.

File transfer will begin!
