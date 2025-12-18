#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>

struct sockaddr_in * sockaddr_in(char *ip, int port);

int main(int ac, char **av) {

  int serverSocketFD = socket(AF_INET, SOCK_STREAM, 0);
  struct sockaddr_in* serverAddress = sockaddr_in("", 2000);

  int result =  bind(serverSocketFD,(struct sockaddr *)serverAddress, sizeof(*serverAddress));
  
  if (result == 0)
    printf("Socket was succesfully binded\n");
  
  int listenResult = listen(serverSocketFD, 10);

  struct sockaddr_in clientAddress;
  int clientAddressSize = sizeof(struct sockaddr_in);
  int clientSocketFD = accept(serverSocketFD, (struct sockaddr *)&clientAddress, (unsigned int * restrict)&clientAddressSize);

// respuesta
 char buffer[1024];
 recv(clientSocketFD, buffer, 1024, 0);
 printf("Response was: %s\n", buffer);

 free(serverAddress);

  return 0;
}
 
