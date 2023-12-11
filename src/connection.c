#include "../include/connection.h"
#include "../include/sungka.h"

void init_server_connection(struct sockaddr_in* server_address, int* server_socket, int* client_socket, const int argc, const char* file, const int port_no){
  if(argc < 2){
    printf("Usage: %s port_no\n", file);
    exit(1);
  }
  printf("Server starting ...\n");
  *server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (*server_socket < 0) 
       exit_with_error("Error: socket() Failed.");
  init_server(server_address, port_no);
  if (bind(*server_socket, (struct sockaddr *) server_address, sizeof(*server_address)) < 0) 
       exit_with_error("Error: bind() Failed.");
  *client_socket = listen_and_accept_connections(*server_socket, port_no);
}

void init_client_connection(struct sockaddr_in* server_address, int* client_socket, int argc, char* file, char* host_name, int port_no){
  if (argc < 3) {
        printf("Usage: %s hostname port_no\n",  file);
        exit(1);
  }
  printf("Client starting ...\n");
  *client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (*client_socket < 0) 
        exit_with_error("Error: socket() Failed.");
  printf("Looking for host '%s'...\n", host_name);
  struct hostent* server = gethostbyname(host_name);
  if (server == NULL) {
    exit_with_error("Error: No such host.");
  }
  printf("Host found!\n");
  connect_client_to_server(server, server_address, port_no, client_socket);
}

void exit_with_error(char *message) {
  printf("%s", message);
  exit(-1);
}

void init_server(struct sockaddr_in* server_address, const int port_no){
    bzero((char *) server_address, sizeof(*server_address));
    server_address->sin_family = AF_INET;
    server_address->sin_port = htons(port_no);
    server_address->sin_addr.s_addr = INADDR_ANY;
}

void connect_client_to_server(struct hostent* server, struct sockaddr_in* server_address, int port_no, int* client_socket) {
  bzero((char *) server_address,  sizeof(*server_address));
  server_address->sin_family = AF_INET;
  if (server->h_addr_list[0] != NULL) {
  bcopy((char *)server->h_addr_list[0],  
        (char *)&server_address->sin_addr.s_addr, 
        server->h_length);
  } else {
      exit_with_error("Error: No address found for the host.");
  }
  server_address->sin_port = htons(port_no);
  
// connect client socket to server address specified above
  printf("Connecting to server at port %d...\n", port_no);
  int connection_status = connect(*client_socket, (struct sockaddr *) server_address, sizeof(*server_address));
  if (connection_status < 0)
    exit_with_error("Failed to connect to server...");
  printf("Connection Successful!\n");
}

int listen_and_accept_connections(int server_socket, int port_no) {
  // listen for connections
  listen(server_socket, 5);
  printf("Server listening to port %d ...\n", port_no);
  printf("Waiting for connection(s) ...\n");
  // accept client socket connection requested on server_socket
  struct sockaddr_in client_addr;
  int client_socket;
  socklen_t client_size = sizeof(client_addr);
  client_socket = accept(server_socket, (struct sockaddr *) &client_addr, &client_size);
    if (client_socket < 0) 
        exit_with_error("Error: accept() Failed.");
    printf("Client succesfully connected ...\n");  
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