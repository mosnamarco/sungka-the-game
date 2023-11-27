#include "../include/connection.h"
#include "../include/sungka.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  // Initialize Game and Stablish the Connection
  struct sockaddr_in server_address;
  Sungka board;
  bool player = false;
  int client_socket;
  init_client_connection(&server_address, &client_socket, argc, argv[0], argv[1], atoi(argv[2]));
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
  recv_t(client_socket, &board);
  whoWinner(&board, player);
  
  close(client_socket);
  return 0;
}