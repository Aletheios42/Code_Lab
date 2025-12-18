#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <arpa/inet.h>

struct AcceptedSocket* acceptIncomingConnection(int serverSocketFD);

struct sockaddr_in * sockaddr_in(char *ip, int port);

struct AcceptedSocket {
  int acceptedSocketFD;
  struct sockaddr_in address;
  int error;
  bool acceptedSuccesfully;
};

struct AcceptedSocket* acceptIncomingConnection(int serverSocketFD)
{
  struct sockaddr_in clientAddress;
  int clientAddressSize = sizeof(struct sockaddr_in);
  int clientSocketFD = accept(serverSocketFD, (struct sockaddr *)&clientAddress, (unsigned int * restrict)&clientAddressSize);
  struct AcceptedSocket *acceptedSocket = malloc(sizeof(struct AcceptedSocket));
  acceptedSocket->address = clientAddress;
  acceptedSocket->acceptedSocketFD = clientSocketFD;
  acceptedSocket->acceptedSuccesfully = clientSocketFD>0;
  if (!acceptedSocket->acceptedSuccesfully)
    acceptedSocket->error = clientSocketFD;
  return acceptedSocket;
}

void  recieveAndPrintIncomingData(int socketFD)
{
  char buffer[1024];
  while (42) {
    ssize_t amountRecieved = recv(socketFD, buffer, 1024, 0);
    if (amountRecieved > 0) {
      buffer[amountRecieved] = 0;
      printf("Response was: %s", buffer);
    }
    if (amountRecieved == 0)
      break;
  }
}

int main(int ac, char **av) {

  int serverSocketFD = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in* serverAddress = sockaddr_in("", 2000);

  int result =  bind(serverSocketFD,(struct sockaddr *)serverAddress, sizeof(*serverAddress));
  
  if (result == 0)
    printf("Socket was succesfully binded\n");
  
  int listenResult = listen(serverSocketFD, 10);

  struct AcceptedSocket* clientSocket = acceptIncomingConnection(serverSocketFD);

  recieveAndPrintIncomingData(clientSocket->acceptedSocketFD);

 close(clientSocket->acceptedSocketFD);
 shutdown(serverSocketFD, SHUT_RDWR);
 free(serverAddress);

  return 0;
}
 
