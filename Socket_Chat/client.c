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
 char *line = NULL;
 size_t lineSize = 0;
 printf("Type your msg..\n");

 while (42) {

   ssize_t charCount = getline(&line, &lineSize, stdin);
   if (charCount > 0) {

     if (strcmp(line, "exit\n") == 0)
       break;
     ssize_t amountWasSent = send(clientSocketFD, line, charCount, 0);
   }
 }

 close(clientSocketFD);
 free(clientAddress);

  return 0;
}
