#include "utils.h"

struct AcceptedSocket acceptedSockets[10];
int acceptedSocketsCount = 0;

void   sendRecievedMessageToOtherClients(char *buffer, int socketFD)
{
  for (int i = 0; i < acceptedSocketsCount; i++)
  {
    if (acceptedSockets[i].acceptedSocketFD != socketFD)
    {
      send(acceptedSockets[i].acceptedSocketFD, buffer, strlen(buffer), 0);
    }
  }

}

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
  int socketFD = (int)(long)data; // Cast directo del valor

  while (42)
  {
    ssize_t amountRecieved = recv(socketFD, buffer, 1024, 0);
    if (amountRecieved > 0) {
      buffer[amountRecieved] = 0;
      printf("Response was: %s", buffer);
      sendRecievedMessageToOtherClients(buffer, socketFD);
    }
    if (amountRecieved == 0)
      break;
  }
  close(socketFD);
  return NULL;
}

void startAccepttingIncomingConnections(int serverSocketFD)
{
  struct AcceptedSocket* clientSocket;

  while (42)
  {
    clientSocket = acceptIncomingConnection(serverSocketFD);
    acceptedSockets[acceptedSocketsCount++] = *clientSocket;
    recieveAndPrintIncomingDataOnSeparateThread(clientSocket);
  }
}


void recieveAndPrintIncomingDataOnSeparateThread(struct AcceptedSocket* pSocket)
{
  pthread_t id;

  pthread_create(&id, NULL, recieveAndPrintIncomingData, (void*)(long)pSocket->acceptedSocketFD);

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
 
