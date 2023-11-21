#include "../include/connection.h"

void exit_with_error(char *message) {
  printf("%s", message);
  exit(-1);
}

void init_server(struct sockaddr_in* server_address){
    server_address->sin_family = AF_INET;
    server_address->sin_port = htons(9888);
    server_address->sin_addr.s_addr = INADDR_ANY;
}

void connect_client_to_server(int client_socket, struct sockaddr_in server_address) {
// connect client socket to server address specified above
  int connection_status = connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address));

  if (connection_status < 0)
    exit_with_error("Failed to connect to server...");
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