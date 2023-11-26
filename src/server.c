#include "../include/connection.h"
#include "../include/sungka.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  // Define Server Connection Requirements and Make Server Listen to Incoming Client
  struct sockaddr_in server_address;
  int server_socket;
  int client_socket;
  init_server_connection(&server_address, &server_socket, &client_socket);
  //Initialize Board and Name
  bool player = true;
  Sungka board;
  initSungka(&board);
  initPlayer(&board, true); // Server is the Player A
  send_t(client_socket, &board);
  printf("Waiting for Your Opponent...\n");
  recv_t(client_socket, &board);
  clearScreen();
  printf("You are Against %s\n", board.B.name);
  //Set The Initial Move for Starting State
  setUserMove(&board);
  switchPlayer(&board);
  toggleToMove(&board);
  send_t(client_socket, &board);
  recv_t(client_socket, &board);
  
  while(!isEndCondition(&board)){
    if(board.isStartState)
      startState(&board, player, client_socket);
    else
      normalState(&board, player, client_socket);
    updateScreen(&board, player, 350000);
  }
  setWinner(&board);
  whoWinner(&board, player);
  send_t(client_socket, &board);

  // close the sockets
  close(server_socket);
  close(client_socket);
  return 0;
}