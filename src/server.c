/*
  Todo (server.c, client.c):

  Fix Race Condition type bug
*/
#include "../include/connection.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  // create server socket
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);

  // define the server address
  struct sockaddr_in server_address;
  init_server(&server_address);
  
  // bind the socket to our specified IP and PORT
  bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));
  int client_socket = listen_and_accept_connections(server_socket);

  while (1) {
    // recieve message from client
    char client_message[256];
    ssize_t bytesRead = recv(client_socket, client_message, sizeof(client_message), 0);
    
    if (bytesRead == 0)
      exit_with_error("Client Disconnected...");

    // print client message
    client_message[bytesRead] = '\0';
    printf("client > %s\n", client_message);

    // get input/message from user
    char server_message[256];
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