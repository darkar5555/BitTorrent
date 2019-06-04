#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void chunkFile(char *fullFilePath, char *chunkName, unsigned long chunkSize) {
    ifstream fileStream;
    fileStream.open(fullFilePath, ios::in | ios::binary);
    // File open a success
    if (fileStream.is_open()) {
        ofstream output;
        int counter = 1;
        string fullChunkName;
        // Create a buffer to hold each chunk
        char *buffer = new char[chunkSize];
        // Keep reading until end of file
        while (!fileStream.eof()) {
            // Build the chunk file name. Usually drive:\\chunkName.ext.N
            // N represents the Nth chunk
            fullChunkName.clear();
            fullChunkName.append(chunkName);
            fullChunkName.append(".");
            // Convert counter integer into string and append to name.
            char intBuf[10];
            stringstream ss;
            ss << counter;
            string str = ss.str();
            //intBuf = str.c_str();
            strcpy(intBuf, str.c_str());
            //itoa(counter,intBuf,10);
            fullChunkName.append(intBuf);
            // Open new chunk file name for output
            output.open(fullChunkName.c_str(),ios::out | ios::trunc | ios::binary);
            // If chunk file opened successfully, read from input and 
            // write to output chunk. Then close.
            if (output.is_open()) { 
                fileStream.read(buffer,chunkSize);
                // gcount() returns number of bytes read from stream.
                output.write(buffer,fileStream.gcount());
                output.close();
                counter++;
            }
        }
        // Cleanup buffer
        delete(buffer);
        // Close input file stream.
        fileStream.close();
        cout << "Chunking complete! " << counter - 1 << " files created." << endl;
    }
    else { cout << "Error opening file!" << endl; }
}

// Simply gets the file size of file.
int getFileSize(ifstream *file) {
	file->seekg(0,ios::end);
	int filesize = file->tellg();
	file->seekg(ios::beg);
	return filesize;
}

// Finds chunks by "chunkName" and creates file specified in fileOutput
void joinFile(char *chunkName, char *fileOutput) {
	string fileName;

	// Create our output file
	ofstream outputfile;
	outputfile.open(fileOutput, ios::out | ios::binary);

	// If successful, loop through chunks matching chunkName
	if (outputfile.is_open()) {
		bool filefound = true;
		int counter = 1;
		int fileSize = 0;

		while (filefound) {
			filefound = false;

			// Build the filename
			fileName.clear();
			fileName.append(chunkName);
			fileName.append(".");

			char intBuf[10];
         stringstream ss;
         ss << counter;
         string str = ss.str();
         //intBuf = str.c_str();
         strcpy(intBuf, str.c_str());
			//itoa(counter,intBuf,10);
			fileName.append(intBuf);

			// Open chunk to read
			ifstream fileInput;
			fileInput.open(fileName.c_str(), ios::in | ios::binary);

			// If chunk opened successfully, read it and write it to 
			// output file.
			if (fileInput.is_open()) {
				filefound = true;
				fileSize = getFileSize(&fileInput);
				char *inputBuffer = new char[fileSize];

				fileInput.read(inputBuffer,fileSize);
				outputfile.write(inputBuffer,fileSize);
				delete(inputBuffer);

				fileInput.close();
			}
			counter++;
		}

		// Close output file.
		outputfile.close();

		cout << "File assembly complete!" << endl;
	}
	else { cout << "Error: Unable to open file for output." << endl; }

}

/*void create_list_peers()
{
   ofstream fs("list_peers.txt");
   fs<< "127.0.0.1 file_1.txt" ;
   fs.close();
}

void print_list_peers()
{
    string ip,file_chunk;
    ifstream infile("list_peers.txt");
    string line;
    while (infile >> ip >> file_chunk)
    {
        cout<<ip<<"->"<<file_chunk<<endl;
    }
}*/


string FirstNumberToString(int n)
{
     ostringstream ss;
     ss << n;
     return ss.str();
}

string encode_message(string message)
{
    char tmp = message[0];
    message.erase(0,1);
    int size_message = message.length();
    string size_str = FirstNumberToString(size_message);
    size_str = string(4-size_str.length(),'0').append(size_str);
    size_str += tmp;
    size_str += message;
    return size_str;
}