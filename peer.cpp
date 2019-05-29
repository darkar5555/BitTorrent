#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{

   // chunkFile("kimble2008.pdf", "chepiur", 256);
   // joinFile("chepiur", "texto");
   // create_list_peers();
   // print_list_peers();

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
   stSockAddr.sin_port = htons(1100);
   Res = inet_pton(AF_INET, "127.0.0.1", &stSockAddr.sin_addr);

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
   while (true)
   {
      string mensaje;
      // cin >> mensaje;
      getline(cin, mensaje);
      n = write(SocketFD, mensaje.c_str(), mensaje.size());
   }
   
   //n = write(SocketFD, "Hi, this is Julio.", 18);
   /* perform read write operations ... */

   shutdown(SocketFD, SHUT_RDWR);

   close(SocketFD);
   return 0;
}

