#ifndef UTILS_H
# define UTILS_H

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>

struct AcceptedSocket* acceptIncomingConnection(int serverSocketFD);
struct sockaddr_in * sockaddr_in(char *ip, int port);
void recieveAndPrintIncomingDataOnSeparateThread(struct AcceptedSocket* clientSocket);
void *acceptNewConnectionAndRecieveAndPrintItsData(void *data);
void  *recieveAndPrintIncomingData(void *data);
void sendRecievedMessageToOtherClients(char *buffer, int socketFD);

struct AcceptedSocket {
  int acceptedSocketFD;
  struct sockaddr_in address;
  int error;
  bool acceptedSuccesfully;
};

#endif
