#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <map>
#include "functions.h"

using namespace std;

int main() {
   
   chunkFile("kimble2008.pdf", "chepiur", 256);
   joinFile("chepiur", "texto");
   //create_list_peers();
   //print_list_peers(); 
   return 0;
}