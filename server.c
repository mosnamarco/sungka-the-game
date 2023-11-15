/*
  Todo (server.c, client.c):

  Fix Race Condition type bug
*/
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <netdb.h>

#include <unistd.h>

void exit_with_error(char *);
int listen_and_accept_connections(int);

int main(int argc, char *argv[])
{
  // create server socket
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);

  // define the server address
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9888);
  server_address.sin_addr.s_addr = INADDR_ANY;
  
  // bind the socket to our specified IP and PORT
  bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));

  int client_socket = listen_and_accept_connections(server_socket);

  // fork process for listening and sending message
  int pid;
  pid = fork();

  char buffer[256];
  int n;
  while(pid == 0) {
    n = recv(client_socket, buffer, sizeof(buffer), 0);
    if (n <= 0) {
      close(server_socket);
      close(client_socket);
      exit_with_error("Something went wrong recieving the message...");
    }
    printf("[client]: %s", buffer);
  }
  while(pid > 0) {
    printf("[me]: ");
    fgets(buffer, sizeof(buffer), stdin);
    n = send(client_socket, buffer, sizeof(buffer), 0);
    if (n <= 0) {
      close(server_socket);
      close(client_socket);
      exit_with_error("Something went wrong sending the message...");
    }
  }

  // close the sockets
  close(server_socket);
  close(client_socket);

  return 0;
}

int listen_and_accept_connections(int server_socket) {
  // listen for connections
  listen(server_socket, 5);
  
  // accept client socket connection requested on server_socket
  int client_socket;
  client_socket = accept(server_socket, NULL, NULL);

  if (client_socket < 0)
    exit_with_error("Client connection failed");
  else
    printf("Connection successful!\n");
  
  return client_socket;
}

void exit_with_error(char *message) {
  printf("%s", message);
  exit(-1);
}
