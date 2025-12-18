#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

struct sockaddr_in * sockaddr_in(char *ip, int port);

int main(int ac, char **av) {

 int clientSocketFD = socket(AF_INET, SOCK_STREAM, 0);

 struct sockaddr_in* clientAddress = sockaddr_in("127.0.0.1", 2000);

 int result =  connect(clientSocketFD, (struct sockaddr *)clientAddress, sizeof(*clientAddress));

 if (result == 0)
   printf("Conection was succesful\n");

 // petición
 char *msg;
 msg = "GET / HTTP/1.1\r\nHost:google.com\r\n\r\n";
 send(clientSocketFD, msg, strlen(msg), 0);
// respuesta
 char buffer[1024];
 recv(clientSocketFD, buffer, 1024, 0);
 printf("Response was: %s\n", buffer);

 //free(clientAddress);
 //close(clientSocketFD);

  return 0;
}
