#include "../include/connection.h"
#include "../include/sungka.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  // Initialize Game and Stablish the Connection
  struct sockaddr_in server_address;
  int server_socket, client_socket;
  Sungka board;
  bool player = true;
  init_server_connection(&server_address, &server_socket, &client_socket, argc, argv[0], atoi(argv[1]));
  initGame(&board, client_socket, player);
  //Game Loop
  while(!isEndCondition(&board)){
    if(board.isStartState)
      startState(&board, player, client_socket);
    else
      normalState(&board, player, client_socket);
    updateScreen(&board, player, 350000);
  }
  //Determine Winner
  setWinner(&board);
  whoWinner(&board, player);
  send_t(client_socket, &board);
  // close the sockets
  close(server_socket);
  close(client_socket);
  return 0;
}