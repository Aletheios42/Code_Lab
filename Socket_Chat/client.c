#include "utils.h"

void *listenAndPrint(void *data)
{
  char buffer[1024];
  int socketFD = (int)(long)data;

  while (42)
  {
    ssize_t amountRecieved = recv(socketFD, buffer, 1024, 0);
    if (amountRecieved > 0) {
      buffer[amountRecieved] = 0;
      printf("Response was: %s", buffer);
    }
    if (amountRecieved == 0)
      break;
  }
  close(socketFD);
  return NULL;
}

void  startListeningAndPrintMessagesOnNewThread(int clientSocketFD)
{
  pthread_t id;

  pthread_create(&id, NULL, listenAndPrint, (void*)(long)clientSocketFD);
}

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

 startListeningAndPrintMessagesOnNewThread(clientSocketFD);

 while (42) {

   ssize_t charCount = getline(&line, &lineSize, stdin);
   if (charCount > 0) {

     if (strcmp(line, "exit\n") == 0)
       break;
     ssize_t amountWasSent = send(clientSocketFD, line, charCount, 0);
   }
 }

 free(clientAddress);
 close(clientSocketFD);

  return 0;
}
