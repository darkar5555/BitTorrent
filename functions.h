#include <fstream>
#include <iostream>

using namespace std;

void create_list_peers()
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
}
