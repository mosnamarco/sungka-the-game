#include "../include/connection.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  // create socket
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  
  // specify an address for the socket we want to connect to
  struct sockaddr_in server_address;
  init_server(&server_address);

  connect_client_to_server(client_socket, server_address);

  while (1) {
    char client_message[256];
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
    char server_message[256];
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