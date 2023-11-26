#include "../include/connection.h"
#include "../include/sungka.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
  // Define Client Connection Requirements and Make Client Connect to Server
  int client_socket;
  struct sockaddr_in server_address;
  init_client_connection(&server_address, &client_socket);
  //Initialize Board and Name
  bool player = false;
  Sungka board;
  printf("Waiting for Your Opponent...\n");
  recv_t(client_socket, &board);
  initPlayer(&board, false);
  send_t(client_socket, &board);
  clearScreen();
  printf("You are Against %s\n", board.A.name);
  //Set The Initial Move for Starting State
  recv_t(client_socket, &board);
  setUserMove(&board);
  switchPlayer(&board);
  send_t(client_socket, &board);
  
  while(!isEndCondition(&board)){
    if(board.isStartState)
      startState(&board, player, client_socket);
    else
      normalState(&board, player, client_socket);
    updateScreen(&board, player, 350000);
  }
  recv_t(client_socket, &board);
  whoWinner(&board, player);
  
  close(client_socket);
  return 0;
}