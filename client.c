#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 5500

int Socket(int domain, int type, int protocol) {
   int res = socket(domain, type, protocol);

   if (res < 0) {
      perror("socket failed");
      exit(EXIT_FAILURE);
   }

   return res;
}

int main() {
   struct sockaddr_in serverAddress;
   char* message = "Message from client";

   int socket = Socket(AF_INET, SOCK_STREAM, 0);

   serverAddress.sin_family = AF_INET;
   serverAddress.sin_port = htons(PORT);

   if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0) {
      printf("Error: Address not supported \n");
      exit(EXIT_FAILURE);
   }

   if (connect(socket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
      printf("Connection failed \n");
      exit(EXIT_FAILURE);
   }

   send(socket, message, strlen(message), 0);
   printf("Message sent \n");

   close(socket);

   return 0;
}