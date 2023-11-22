#include "../include/connection.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  // Define Server Connection Requirements and Make Server Listen to Incoming Client
  struct sockaddr_in server_address;
  int server_socket;
  int client_socket;
  init_server_connection(&server_address, &server_socket, &client_socket);
  //Define Message Buffers
  char client_message[256];
  char server_message[256];

  while (1) {
    // recieve message from client
    ssize_t bytesRead = recv(client_socket, client_message, sizeof(client_message), 0);
    
    if (bytesRead == 0)
      exit_with_error("Client Disconnected...");

    // print client message
    client_message[bytesRead] = '\0';
    printf("client > %s\n", client_message);

    // get input/message from user
    printf("server[USER] > ");
    fgets(server_message, sizeof(server_message), stdin);

    // send message/input to client
    fflush(stdin);
    send(client_socket, server_message, sizeof(server_message), 0);
  }

  // close the sockets
  close(server_socket);
  close(client_socket);

  return 0;
}