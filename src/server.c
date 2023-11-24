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
  //Define Message Buffers
  char client_message[256];
  char server_message[256];
  Sungka board;
  initSungka(&board);
  initPlayer(&board, true); // Server is the Player A
  send_t(client_socket, &board);
  printf("Waiting for Your Opponent...\n");
  recv_t(client_socket, &board);
  clearScreen();
  printf("You are Against %s\n", board.B.name);
  
  while(!isEndCondition(&board)){
    if(board.currentPlayer) {
      if(!isHasMoves(&board, board.currentPlayer)){
        switchPlayer(&board);
        toggleToMove(&board);
      }
      if(board.A.toMove){
        setUserMove(&board);
        toggleToMove(&board);
      }
      if(board.A.shells == 0){
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
  // close the sockets
  close(server_socket);
  close(client_socket);

  return 0;
}