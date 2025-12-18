#include <unistd.h>
#include <stdio.h>
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

struct AcceptedSocket {
  int acceptedSocketFD;
  struct sockaddr_in address;
  int error;
  bool acceptedSuccesfully;
};

struct AcceptedSocket* acceptIncomingConnection(int serverSocketFD)
{
  struct sockaddr_in clientAddress;
  int clientAddressSize;
  int clientSocketFD;

  clientAddressSize = sizeof(struct sockaddr_in);
  clientSocketFD = accept(serverSocketFD, (struct sockaddr *)&clientAddress, (unsigned int * restrict)&clientAddressSize);
  struct AcceptedSocket *acceptedSocket = malloc(sizeof(struct AcceptedSocket));
  acceptedSocket->address = clientAddress;
  acceptedSocket->acceptedSocketFD = clientSocketFD;
  acceptedSocket->acceptedSuccesfully = clientSocketFD>0;
  if (!acceptedSocket->acceptedSuccesfully)
    acceptedSocket->error = clientSocketFD;
  return acceptedSocket;
}

void  *recieveAndPrintIncomingData(void *data)
{
  char buffer[1024];
  int *socketFD;

  socketFD = data;
  while (42)
  {
    ssize_t amountRecieved = recv(*socketFD, buffer, 1024, 0);
    if (amountRecieved > 0) {
      buffer[amountRecieved] = 0;
      printf("Response was: %s", buffer);
    }
    if (amountRecieved == 0)
      break;
  }
  close(*socketFD);
  return NULL;
}

void startAccepttingIncomingConnections(int serverSocketFD)
{
  struct AcceptedSocket* clientSocket;

  while (42)
  {
    clientSocket = acceptIncomingConnection(serverSocketFD);
    recieveAndPrintIncomingDataOnSeparateThread(clientSocket);
  }
}


void recieveAndPrintIncomingDataOnSeparateThread(struct AcceptedSocket* pSocket)
{
  pthread_t id;
  void *data = &pSocket->acceptedSocketFD;

  pthread_create(&id, NULL, recieveAndPrintIncomingData, data);

}

int main(int ac, char **av) {

  int serverSocketFD = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in* serverAddress = sockaddr_in("", 2000);

  int result =  bind(serverSocketFD,(struct sockaddr *)serverAddress, sizeof(*serverAddress));
  
  if (result == 0)
    printf("Socket was succesfully binded\n");
  
  int listenResult = listen(serverSocketFD, 10);

  startAccepttingIncomingConnections(serverSocketFD);

 shutdown(serverSocketFD, SHUT_RDWR);
 free(serverAddress);

  return 0;
}
 
