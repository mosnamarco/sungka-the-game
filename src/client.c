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
  int bytesRead;
  //Define Message Buffers
  char client_message[256];
  char server_message[256];
  Sungka board;
  printf("Waiting for Your Opponent...\n");
  recv_t(client_socket, &board);
  initPlayer(&board, false);
  send_t(client_socket, &board);
  clearScreen();
  printf("You are Against %s\n", board.A.name);
  
  while(!isEndCondition(&board)){
    if(!board.currentPlayer) {
      if(!isHasMoves(&board, !board.currentPlayer)){
        switchPlayer(&board);
        toggleToMove(&board);
      }
      if(board.B.toMove){
        setUserMove(&board);
        toggleToMove(&board);
      }
      if(board.B.shells == 0){
        switchPlayer(&board);
        toggleToMove(&board);
      }
      simulateStep(&board);
      send_t(client_socket, &board);
      updateScreen(&board, 500000);
    }else{
      recv_t(client_socket, &board);
      updateScreen(&board, 500000);
    }
  }
  close(client_socket);
  
  return 0;
}