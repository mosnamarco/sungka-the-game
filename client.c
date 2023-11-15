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
  printf("hello user");
  // create socket
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  
  // specify an address for the socket we want to connect to
  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(9888);
  server_address.sin_addr.s_addr = INADDR_ANY;

  connect_client_to_server(client_socket, server_address);

  // fork processess for listen and sending messages
  int pid;
  pid = fork();

  char buffer[256];
  int n;
  while(pid == 0) {
    bzero(buffer, sizeof(buffer));
    n = recv(client_socket, buffer, sizeof(buffer), 0);
    if (n <= 0) {
      close(client_socket);
      exit_with_error("Error: recv() Failed.");
    }
    printf("\033[1G\033[2K");
    printf("[server]: %s", buffer);
  }
  while(pid > 0) {
    bzero(buffer, sizeof(buffer)); 
    printf("[me]: ");
    fgets(buffer, sizeof(buffer), stdin);
    n = send(client_socket, buffer, sizeof(buffer), 0);
    if (n <= 0) {
      close(client_socket);
      exit_with_error("Error sending message...");
    }
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

