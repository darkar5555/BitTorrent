#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "functions.h"
#include <thread>

using namespace std;

string ip;
string port;


void serverPeer()
{
   struct sockaddr_in stSockAddr;
   int SocketFD = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);

   if(-1 == SocketFD)
   {
      perror("cannot create socket");
      exit(EXIT_FAILURE);
   }
   int n;
   memset(&stSockAddr,0,sizeof(struct sockaddr_in));
   stSockAddr.sin_family = AF_INET;
   stSockAddr.sin_port = htons(1100);
   stSockAddr.sin_addr.s_addr = INADDR_ANY;

   if(-1 == bind(SocketFD,(const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
    {
        perror("error bind failed");
        close(SocketFD);
        exit(EXIT_FAILURE);
    }

    if(-1 == listen(SocketFD, 10))
    {
        perror("error listen failed");
        close(SocketFD);
        exit(EXIT_FAILURE);
    }
    for(;;)
    {
        int ConnectFD = accept(SocketFD, NULL, NULL);

        if(0 > ConnectFD)
        {
            perror("error accept failed");
            close(SocketFD);
            exit(EXIT_FAILURE);
        }
        // one thread por client to check
        do
        {
           //cout<<"conectado";
        } while (true);
        
       shutdown(ConnectFD, SHUT_RDWR);

    close(ConnectFD);        

    }
}


void clientPeer(string ip, string port)
{
   struct sockaddr_in stSockAddr;
   int Res;
   int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
   int n;

   if (-1 == SocketFD)
   {
      perror("cannot create socket");
      exit(EXIT_FAILURE);
   }

   memset(&stSockAddr, 0, sizeof(struct sockaddr_in));

   stSockAddr.sin_family = AF_INET;
   stSockAddr.sin_port = htons(stoi(port));
   Res = inet_pton(AF_INET, ip.c_str(), &stSockAddr.sin_addr);

   if (0 > Res)
   {
      perror("error: first parameter is not a valid address family");
      close(SocketFD);
      exit(EXIT_FAILURE);
   }
   else if (0 == Res)
   {
      perror("char string (second parameter does not contain valid ipaddress");
      close(SocketFD);
      exit(EXIT_FAILURE);
   }

   if (-1 == connect(SocketFD, (const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
   {
      perror("connect failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
   }
   
   string to_send;
   string to_port;
   string to_ip;
   string input_message;
   string test;
   while (true)
   {
      cout<<"Ingrese una de las funciones"<<endl;
      cout<<"L : Login"<<endl;
      cout<<"D : Download"<<endl;
      getline(cin, input_message);
      
      if(input_message == "L")
      {
         to_send = "";
         //to_port = encode_message(port);
         //to_ip = encode_message(ip);
         //to_send = ip;
         //to_send += port;
         to_send +=ip;
         to_send += " ";
         to_send += port;
         to_send = encode_message(string("L")+to_send);
         
      }
      if(input_message == "D")
      {
         
      }
      n= write(SocketFD,to_send.c_str(),to_send.length());
      input_message = "";
      // Aqui se enviaba el mensaje manuealmente
      //getline(cin, mensaje);
      //n = write(SocketFD, mensaje.c_str(), mensaje.size());
   
   }
   
   //n = write(SocketFD, "Hi, this is Julio.", 18);
   /* perform read write operations ... */

   shutdown(SocketFD, SHUT_RDWR);

   close(SocketFD);
}

int main(int argc, char **argv)
{

   // chunkFile("kimble2008.pdf", "chepiur", 256);
   // joinFile("chepiur", "texto");
   // create_list_peers();
   // print_list_peers();
   thread(serverPeer).detach();
   ip = argv[1];
   port = argv[2];
   cout<< ip<< " "<<port<<endl;
   clientPeer(ip,port);
   return 0;
}

