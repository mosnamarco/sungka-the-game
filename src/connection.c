#include "../include/connection.h"
#include "../include/sungka.h"

void init_server_connection(struct sockaddr_in* server_address, int* server_socket, int* client_socket){
  printf("Waiting for Your Opponent...\n");
  *server_socket = socket(AF_INET, SOCK_STREAM, 0);
  init_server(server_address);
  bind(*server_socket, (struct sockaddr*) server_address, sizeof(*server_address));
  *client_socket = listen_and_accept_connections(*server_socket);
}

void init_client_connection(struct sockaddr_in* server_address, int* client_socket){
  printf("Waiting for Your Opponent...\n");
  *client_socket = socket(AF_INET, SOCK_STREAM, 0);
  init_server(server_address);
  connect_client_to_server(client_socket, server_address);
}

void exit_with_error(char *message) {
  printf("%s", message);
  exit(-1);
}

void init_server(struct sockaddr_in* server_address){
    server_address->sin_family = AF_INET;
    server_address->sin_port = htons(PORT_ADDR);
    server_address->sin_addr.s_addr = INADDR_ANY;
}

void connect_client_to_server(int* client_socket, struct sockaddr_in* server_address) {
// connect client socket to server address specified above
  int connection_status = connect(*client_socket, (struct sockaddr *) server_address, sizeof(*server_address));

  if (connection_status < 0)
    exit_with_error("Failed to connect to server...");

  printf("Connection Successful!\n");
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

void send_t(int client_socket, Sungka* msg){
    send(client_socket, msg, sizeof(Sungka), 0);
}

void recv_t(int client_socket, Sungka* msg){
    int bytesRead = recv(client_socket, msg, sizeof(Sungka), 0);
    if (bytesRead == 0)
      exit_with_error("Client Disconnected...");
}