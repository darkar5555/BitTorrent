#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
// void create_list_peeers()
// {
//    ofstream fs("list_peers.txt"); 
// }

// void print_list_peers()
// {
//     ifstream 
// }


// char cadena[128];
//    // Crea un fichero de salida
//    ofstream fs(".txt"); 

//    // Enviamos una cadena al fichero de salida:
//    fs << "Hola, mundo" << endl;
//    // Cerrar el fichero, 
//    // para luego poder abrirlo para lectura:
//    fs.close();

//    // Abre un fichero de entrada
//    ifstream fe("nombre.txt"); 

//    // Leeremos mediante getline, si lo hiciéramos 
//    // mediante el operador << sólo leeríamos 
//    // parte de la cadena:
//    fe.getline(cadena, 128);

//    cout << cadena << endl;




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

