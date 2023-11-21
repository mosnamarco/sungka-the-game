# ifndef MY_HEADER_FILE_H
# define MY_HEADER_FILE_H
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

void exit_with_error(char*);
void init_server(struct sockaddr_in*);
void connect_client_to_server(int, struct sockaddr_in);
int listen_and_accept_connections(int);

# endif