#include "../include/sungka.h"
#include "../include/connection.h"

void initSungka(Sungka *board) {
    board->currentPlayer = true;
	board->isStartState = true;
	board->winner = -1;
	board->flow = true;
	board->turns = 0;
    for (int i = 0; i < 16; i++) {
		board->pits[i] = 7;  // Start with 7 shells in each pit
    }
	//Set all scores to 0
	board->pits[7] = 0;
	board->pits[15] = 0;
}

void initPlayer(Sungka* board, char* name, bool player){
	if(player){
		printf("Hi %s, You are Player A\n", name);
		board->A.who = true;
		board->A.toMove = true;
		board->A.shells = 0;
		board->A.currentIndex = -1;
		strcpy(board->A.name, name);
		return;
	}
	printf("Hi %s, You are Player B\n", name);
	board->B.who = false;
	board->B.toMove = false;
	board->B.shells = 0;
	board->B.currentIndex = -1;
	strcpy(board->B.name, name);
}

void initGame(Sungka* board, const int client_socket, const bool player){
	char name[256];
	printf("Enter Your Name: ");
	fgets(name, sizeof(name), stdin);
	name[strlen(name) - 1] = '\0';
	if(player){
		initSungka(board);
		initPlayer(board, name,player); // Server is the Player A
		send_t(client_socket, board);
		printf("Waiting for Your Opponent...\n");
		recv_t(client_socket, board);
		clearScreen();
		printf("You are Against %s\n", board->B.name);
		//Set The Initial Move for Starting State
		setUserMove(board);
		switchPlayer(board);
		toggleToMove(board);
		printf("Waiting for %s to Move", board->B.name);
		send_t(client_socket, board);
		recv_t(client_socket, board);
	}
	else{
		recv_t(client_socket, board);
		initPlayer(board, name, player);
		send_t(client_socket, board);
		clearScreen();
		printf("You are Against %s\n", board->A.name);
		printf("Waiting for %s to Move\n", board->A.name);
		// Set The Initial Move for Starting State
		recv_t(client_socket, board);
		setUserMove(board);
		switchPlayer(board);
		send_t(client_socket, board);
	}
}

void flushInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void displayPit(Sungka* board, const int i){
	int aIndex = board->A.currentIndex, bIndex = board->B.currentIndex;
	int val = board->pits[i];
	char c = ' ';
	if(board->isStartState){
		if(aIndex == i)
			c = 'A';
		else if (bIndex == i)
			c = 'B';
	}
	else{
		Player* thisPlayer = getPlayer(board, board->currentPlayer);
		if(thisPlayer->currentIndex == i){
			c = (thisPlayer->who) ? 'A' : 'B';
		}
	}
	if (val < 10)
		printf("[%c %d]", c, val);
	else
		printf("[%c%d]", c, val);
}

void displayPits(Sungka* board, const bool player){
	if(!player){
		for (int i = 0; i <= 6; i++) {
			printf("\t");
			displayPit(board, i);
		}
	}
	else{
		for (int i = 14; i >= 8; i--) {
			printf("\t");
			displayPit(board, i);
		}
	}
    printf("\n");
}

void displayGuide(){
	for (int i = 0; i <= 6; i++) {
		printf("\t  %d ", i);
	}
	printf("\n");
}

void displayBoard(Sungka *board){
	//Display Player B's Pits
	displayPits(board, false);
	
	//Display A's Home
	displayPit(board, 15);
	for(int i = 0; i < 8; i++)
		printf("\t");
	displayPit(board, 7);
	//Display B's Home
	printf("\n");
	//DisplayPlayer A's Pits
	displayPits(board, true);
}

void updateScreen(Sungka* board, const bool caller, int updateSpeed){
	Player* current;
	Player* A = getPlayer(board, true);
	Player* B = getPlayer(board, false);
	clearScreen();
	if(!board->isStartState){
		if(caller == board->currentPlayer){
			printf("Your Turn\n");
		}
		else{
			current = getPlayer(board, board->currentPlayer);
			printf("%s's Turn\n", current->name);
		}
	}
	printf("A: %s's Shells: %d\n", A->name, A->shells);
	printf("B: %s's Shells: %d\n", B->name, B->shells);
	displayBoard(board);
	printf("\n");
	usleep(updateSpeed);
}

void clearScreen(){
	printf("\x1b[H\x1b[J");
}

void switchPlayer(Sungka *board){
	board->currentPlayer = !board->currentPlayer;
}

void addScore(Sungka *board, int score){
	if(board->currentPlayer){
		board->pits[15] += score;
	}
	else{
		board->pits[7] += score;
	}
}

void addPitShell(Sungka *board, int i, int *shells){
	board->pits[i]++;
	--(*shells);
}

bool isPlayerHome(Sungka *board, int pit){
	if(pit == 7 && !board->currentPlayer){
		return true;
	}
	else if(pit == 15 && board->currentPlayer){
		return true;
	}
	return false;
}

bool isAHome(int pit){
	return (pit == 7 || pit == 15) ? true : false;
}

bool isPlayerPits(const bool player, const int pit){
	if((0 <= pit && pit <= 6 ) && !player){
		return true;
	}
	else if((8 <= pit && pit <= 14 ) && player){
		return true;
	}
	return false;
}

bool isValid(const Sungka* board, const bool player , char* buffer, int* index){
	bool isValid = false;
	int i;
	// Remove the newline character if it exists in the buffer
		size_t raw_len = strlen(buffer);
		size_t len = raw_len - 1;
		if (len > 0 && buffer[len] == '\n') {
			buffer[len] = '\0';
		} else {
			// If no newline character was found, flush the input buffer
			flushInputBuffer();
		}
		*index = atoi(buffer);
		i = *index;
		int actual = i;

	if( ((len) == 1) && (isdigit(buffer[0])) && (0 <= i && i <= 6)){
		if(player)
			actual = getPitIndexAcross(i);
		else
			actual = i;
		if( (board->pits[actual] > 0))
			isValid = true;
	}
	return isValid;
}

bool isEmptyPit(const Sungka *board, const int pit){
	if(board->pits[pit] == 0){
		return true;
	}
	return false;
}

bool isHasMoves(const Sungka* board,  const bool player){
	int start, end;
	if(player){
		start = 8, end = 14;
	}
	else{
		start = 0, end = 6;
	}
	for(int i = start; i <= end; ++i){
		if(board->pits[i] > 0){
			return true;
		}
	}
	return false;	
}

bool isHasShells(Sungka* board, const bool player){
	Player* thisPlayer = getPlayer(board, player);
	if(thisPlayer->shells > 0 )
		return true;
	return false;
}

bool isEndCondition(Sungka* board){
	bool hasMoves = isHasMoves(board, true) || isHasMoves(board, false);
	bool hasShells = isHasShells(board, true) || isHasShells(board, false);
	return (!hasMoves && !hasShells) ? true : false;
}

Player* getPlayer(Sungka* board, const bool player){
	return (player) ? &(board->A) : &(board->B);
}

int getPitIndexAcross(const int pit){
	return (14 - pit) % 16;
}

int getScore(const Sungka *board, const bool player){
	if(player){
		return board->pits[15];
	}
	return board->pits[7];
}

void getShellsFromPit(Sungka* board, int* shells, const int i){
	*shells += board->pits[i];
	board->pits[i] = 0;
}

void setUserMove(Sungka* board){
	//Display Board
	clearScreen();
	if(!board->currentPlayer){
		displayGuide();
	}
	displayBoard(board);
	if(board->currentPlayer){
		displayGuide();
	}

	//Get User Input
	char buffer[100];
	int index;
	Player* thisPlayer = getPlayer(board, board->currentPlayer);
	printf("%c: Make Move[0-6]: ", (thisPlayer->who)? 'A' : 'B');
	fgets(buffer, sizeof(buffer), stdin);

	//Validate User Input
	if(isValid(board, board->currentPlayer, buffer, &index)){
		if(board->currentPlayer){
			index = getPitIndexAcross(index);
			getShellsFromPit(board, &(board->A.shells), index);
			board->A.currentIndex = index;
		}else{
			getShellsFromPit(board, &(board->B.shells), index);
			board->B.currentIndex = index;
		}
	}
	else{
		setUserMove(board);
	}
}

void toggleToMove(Sungka* board){
	board->A.toMove = !(board->A.toMove);
	board->B.toMove = !(board->B.toMove);
}

void toggleToMovePlayer(Sungka* board, const bool player, const bool toggle){
	if(player){
		board->A.toMove = toggle;
		board->B.toMove = !toggle;
	}
	else{
		board->B.toMove = toggle;
		board->A.toMove = !toggle;
	}
}

void lastShellAtHome(Sungka* board, int* shells){
	*shells = 0;
	addScore(board, 1);
	toggleToMovePlayer(board, board->currentPlayer, on);
}

void lastShellLogic(Sungka* board, int* shells, int i){
	// Check if the current pit is a home
	if(isAHome(i)){
		//move to next pit if not player's Home
		if(!isPlayerHome(board, i)){
			simulateStep(board);
		}
		//increment score if is player's home, and user gets another turn
		else{
			lastShellAtHome(board, shells);
			return;
		}
	}
	// Check if player is in Regular pit
	else{
		//if the pit is not empty get the contents and continue
		if(!isEmptyPit(board, i)){
			getShellsFromPit(board, shells, i);
			return;
		}
		else{
			int across = getPitIndexAcross(i);
			//if it is in the player pits and empty and across is not empty, add all pits to score
			if(isPlayerPits(board->currentPlayer, i) && !isEmptyPit(board, across)){
				int incScore = *shells + board->pits[across];
				addScore(board, incScore);
				*shells = 0;
				board->pits[i] = 0;
				board->pits[across] = 0;
			}
			else{
				addPitShell(board, i, shells);
			}
		}
	}
	
}

void notLastShellLogic(Sungka* board, int* shells, int i){
	if(isAHome(i)){
		//move to next pit if not player's Home
		if(!isPlayerHome(board, i))
			simulateStep(board);
		//increment score if is player's home
		else{
			addScore(board, 1);
			--(*shells);
		}
	}
	else{
		//increment a pit if it is not player's Home
		addPitShell(board, i, shells);
	}
}

void simulateStep(Sungka* board){
	int* shells = (board->currentPlayer) ? &(board->A.shells) : &(board->B.shells);
	int* i = (board->currentPlayer) ? &(board->A.currentIndex) : &(board->B.currentIndex);
	int j = 1; // incrementor
	if(!board->flow)
		j = -1;
	*i = (*i + j) % 16;

	//Game Logic
	if(*shells > 1){
		notLastShellLogic(board, shells, *i);
	}
	else if(*shells == 1){
		lastShellLogic(board, shells, *i);
	}
	else if(*shells == 0){
		return;
	}
	else{
		fprintf(stderr, "Number of Shells is below 0\n");
		exit(EXIT_FAILURE);
	}
}

void startState(Sungka* board, const bool player, const int client_socket){
	Player* thisPlayer = getPlayer(board, player);
	if(board->currentPlayer == player){
		if(isHasShells(board, player)){
			simulateStep(board);
			switchPlayer(board);
			send_t(client_socket, board);
		}
		else{
			if(thisPlayer->toMove){
				setUserMove(board);
				toggleToMovePlayer(board, player, off);
				simulateStep(board);
				switchPlayer(board);
				board->turns++;
				send_t(client_socket, board);
			}
			else{
				board->isStartState = false;
				switchPlayer(board);
				send_t(client_socket, board);
			}
		}
    }
	else{
      recv_t(client_socket, board);
    }
}

void normalState(Sungka* board, const bool player, const int client_socket){
	Player* thisPlayer = getPlayer(board, player);
	if(board->currentPlayer == player){
      if(!isHasMoves(board, player) && !isHasShells(board, player)){
        switchPlayer(board);
        toggleToMovePlayer(board, player, off);
		thisPlayer->currentIndex = -2;
		board->turns++;
		send_t(client_socket, board);
		return;
      }
      if(thisPlayer->toMove){
        setUserMove(board);
        toggleToMovePlayer(board, player, off);
		board->turns++;
		send_t(client_socket, board);
		return;
      }
	  if(isHasShells(board, player)){
     	simulateStep(board);
      	send_t(client_socket, board);
	  }
	  if(thisPlayer->shells == 0 && !thisPlayer->toMove){
		switchPlayer(board);
		toggleToMovePlayer(board, player, off);
		thisPlayer->currentIndex = -2;
		board->turns++;
		send_t(client_socket, board);
		return;
	  }
    }else{
      recv_t(client_socket, board);
    }
}

void setWinner(Sungka* board){
	Player* A = getPlayer(board, true);
	Player* B = getPlayer(board, false);
	if(board->pits[15] > board->pits[7]){
		A->score.win += 1;
		B->score.lost += 1;
		board->winner = 1;
	}
	else if(board->pits[15] < board->pits[7]){
		B->score.win += 1;
		A->score.lost += 1;
		board->winner = 0;
	}
	else{
		A->score.draw += 1;
		B->score.draw += 1;
		board->winner = -1;
	}
}

void whoWinner(Sungka* board, const bool player){
	if(board->winner == -1){
		printf("Draw\n");
		
	}
	else if(board->winner == 1){
		if(player)
			printf("You Won\n");
		else
			printf("You Lost\n");
	}
	else{
		if(!player)
			printf("You Won\n");
		else
			printf("You Lost\n");
	}
	printf("Your Score: %d\n", getScore(board, player));
	printf("%s Score: %d\n", getPlayer(board, !player)->name  ,getScore(board, !player));
}