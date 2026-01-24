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
      printf("%s", buffer);
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
 char *name = NULL;
 size_t nameSize = 0;
 printf("Introduce your name..\n");
 ssize_t nameCount = getline(&name, &nameSize, stdin);
 name[nameCount -1] = 0;

 // petición
 char *line = NULL;
 size_t lineSize = 0;
 printf("Type your msg..\n");

 startListeningAndPrintMessagesOnNewThread(clientSocketFD);

 char buffer[1024];

 while (42)
 {
   ssize_t charCount = getline(&line, &lineSize, stdin);
   line[charCount -1] = 0;
   sprintf(buffer, "%s: %s", name, line);
   if (charCount > 0) {
     if (strcmp(line, "exit") == 0)
       break;
     ssize_t amountWasSent = send(clientSocketFD, buffer, strlen(buffer), 0);
   }
 }

 free(clientAddress);
 close(clientSocketFD);

  return 0;
}
