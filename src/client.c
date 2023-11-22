#include "../include/connection.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  // Define Client Connection Requirements and Make Client Connect to Server
  int client_socket;
  struct sockaddr_in server_address;
  init_client_connection(&server_address, &client_socket);
  //Define Message Buffers
  char client_message[256];
  char server_message[256];

  while (1) {
    printf("client[USER] > ");
    fgets(client_message, sizeof(client_message), stdin);
    
    // exit game if user wills
    if (strcmp(client_message, ":q\n") == 0) {
      close(client_socket);
      return 0;
    }

    // send message to server
    fflush(stdin);
    send(client_socket, client_message, sizeof(client_message), 0);

    // get message from server
    int bytesRead = recv(client_socket, server_message, sizeof(server_message), 0);

    if (bytesRead == 0)
      exit_with_error("Server disconnected...");

    // print server message
    server_message[bytesRead] = '\0';
    printf("server > %s\n", server_message);
  } 

  close(client_socket);
  
  return 0;
}