#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <netdb.h>

#include <unistd.h>

void exit_with_error(char *);
void connect_client_to_server(int, struct sockaddr_in);

int main(int argc, char *argv[])
{
  // create socket
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  
  // specify an address for the socket we want to connect to
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9888);
  server_address.sin_addr.s_addr = INADDR_ANY;

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

void exit_with_error(char *message) {
  printf("%s", message);
  exit(-1);
}

void connect_client_to_server(int client_socket, struct sockaddr_in server_address) {
// connect client socket to server address specified above
  int connection_status = connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address));

  if (connection_status < 0)
    exit_with_error("Failed to connect to server...");
}
