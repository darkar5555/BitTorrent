#include <iostream>
#include <map>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sstream>
#include <vector>
#include <chrono> 

using namespace std;


void savePeers(string message, map<string ,string>& peers)
{
    int pos=0;
    string delimiter = " ";
    string token;
    while((pos = message.find(delimiter)) !=std::string::npos)
    {
        token = message.substr(0,pos);
        
        message.erase(0,pos+delimiter.length());
    }    
    peers.insert({token,message});
    //return peers;
    //cout<<message<<endl;
}

void printPeers(map <string,string > peers)
{
    for(auto it = peers.begin(); it != peers.end(); ++it)
    {
        cout<<it->first<< " -> "<<it->second<<endl;
    }
}