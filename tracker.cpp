#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "protocol_tracker.h"

using namespace std;

Protocol protocol_track;

int main(void)
{
  struct sockaddr_in stSockAddr;
  int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  char buffer[256];
  int n;

  if (-1 == SocketFD)
  {
    perror("can not create socket");
    exit(EXIT_FAILURE);
  }

  memset(&stSockAddr, 0, sizeof(struct sockaddr_in));

  stSockAddr.sin_family = AF_INET;
  stSockAddr.sin_port = htons(1200);
  stSockAddr.sin_addr.s_addr = INADDR_ANY;

  if (-1 == ::bind(SocketFD, (const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
  {
    perror("error bind failed");
    close(SocketFD);
    exit(EXIT_FAILURE);
  }

  if (-1 == listen(SocketFD, 10))
  {
    perror("error listen failed");
    close(SocketFD);
    exit(EXIT_FAILURE);
  }

  for (;;)
  {
    int ConnectFD = accept(SocketFD, NULL, NULL);

    if (0 > ConnectFD)
    {
      perror("error accept failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }

    //bzero(buffer,256);
    //n = read(ConnectFD,buffer,255);
    char *message_buffer;
    char buffer[4];
    bzero(buffer, 4);
    int n = read(ConnectFD, buffer, 4);
    do
    {
      if (n > 0)
      {
        int size_message = atoi(buffer);
        char buffer_op[1];
        //now read operation
        n = read(ConnectFD, buffer_op, 1);
        cout<<buffer<<endl;
        Messsage msg = protocol_track.read_s(buffer_op[0], size_message, ConnectFD);
      }
      bzero(buffer, 4);
      n = read(ConnectFD, buffer, 4);
      //cout<<buffer<<endl;
      //lee de manera ingenua cada mensaje
      /*bzero(buffer,256);
        n = read(ConnectFD,buffer, 255);
        cout  << buffer << endl;*/
      // n = write(ConnectFD,"I got your message",18);

    } while (true);

    //  if (n < 0) perror("ERROR reading from socket");
    //  printf("Here is the message: [%s]\n",buffer);
    //  n = write(ConnectFD,"I got your message",18);
    //  if (n < 0) perror("ERROR writing to socket");

    /* perform read write operations ... */

    shutdown(ConnectFD, SHUT_RDWR);

    close(ConnectFD);
  }

  //close(SocketFD);
  cout << "Disconnected..." << endl;
  return 0;
}
