#include "include/sungka.h"

void flushInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void initSungka(Sungka *board) {
	/* 
		Player A will be the first mover
		Flow of the Game is clockwise
		Player A and B score is set to 0
		# of shell in each pits is 0
	*/
    board->currentPlayer = true;
	board->flow = true;
	board->turns = 0;
    for (int i = 0; i < 16; i++) {
		board->pits[i] = 7;  // Start with 7 shells in each pit
    }
	//Set all scores to 0
	board->pits[7] = 0;
	board->pits[15] = 0;
}

void displayPit(const int a){
	if (a < 10)
		printf("[ %d]", a);
	else
		printf("[%d]", a);
}

void displayPits(const int* pits, const bool player){
	if(!player){
		for (int i = 0; i <= 6; i++) {
			printf("\t");
			displayPit(pits[i]);
		}
	}
	else{
		for (int i = 14; i >= 8; i--) {
			printf("\t");
			displayPit(pits[i]);
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

void displayBoard(const Sungka *board){
	//Display Player B's Pits
	displayPits(board->pits, false);
	
	//Display A's Home
	displayPit(board->pits[15]);
	for(int i = 0; i < 8; i++)
		printf("\t");
	//Display B's Home
	displayPit(board->pits[7]);
	printf("\n");
	//DisplayPlayer A's Pits
	displayPits(board->pits, true);
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

bool isPlayerPits(bool player, int pit){
	if((0 <= pit && pit <= 6 ) && !player){
		return true;
	}
	else if((8 <= pit && pit <= 14 ) && player){
		return true;
	}
	return false;
}

//Validate User Input
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
		// printf("Is Valid Input %d", isValid);
		// printf("Board Pit: [%d]\n", board->pits[actual]);
	}
	// else printf("Invalid Input\n");
	// printf("Len of String: %lx\n", len);
	// printf("Is Input a digit: %d\n", isdigit(buffer[0]));
	// printf("Is Within Range [0-6]: %d\n", (0 <= i && i <= 6));
	return isValid;
}

//Query Board: Boolean
bool isEmptyPit(Sungka *board, int pit){
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

bool isEndCondition(const Sungka* board){
	bool hasMoveA = isHasMoves(board, true);
	bool hasMoveB = isHasMoves(board, false);
	return (!hasMoveA && !hasMoveB)? true : false;
}

//Check Who's Winner
Winner whoWinner(const Sungka* board){
	int a = getScore(board, true);
	int b = getScore(board, false);
	if(a > b){
		printf("\nPlayer A Wins\n");
		return A;
	}
	else if(b > a){
		printf("\nPlayer B Wins\n");
		return B;
	}
	printf("\nDraw\n");
	return DRAW;
}

char getPlayer(const bool player){
	return (player) ? 'A' : 'B';
}

int getPitIndexAcross(int pit){
	return 14 - pit;
}

int getScore(const Sungka *board, const bool player){
	if(player){
		return board->pits[15];
	}
	return board->pits[7];
}

int getUserMove(Sungka *board){
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
	printf("Player %c [0-6]: ", getPlayer(board->currentPlayer));
	fgets(buffer, sizeof(buffer), stdin);

	//Validate User Input
	if(isValid(board, board->currentPlayer, buffer, &index)){
		if(board->currentPlayer){
			index = getPitIndexAcross(index);
		}
	}
	else{
		index = getUserMove(board);
	}
	return index;
}

void simulate(Sungka *board, int i){
	int shells = board->pits[i];
	board->pits[i] = 0;
	int j = 1; // incrementor
	if(!board->flow){
		j = -1;
	}
	while(shells){
		clearScreen();
		i = (i + j) % 16;
		if(shells == 1){
			// Check if the current pit is a home
			if(isAHome(i)){
				//increment score if is player's home
				if(isPlayerHome(board, i)){
					shells = 0;
					addScore(board, 1);
					int move = getUserMove(board);
					simulate(board, move);
					break;
				}
				//move to next pit if not player's Home
				else{
					continue;
				}
			}
			// Check if player is in Regular pit
			else{
				// pit is empty
				if(isEmptyPit(board, i)){
					//get all on the current and accross, then add to score
					int accross = getPitIndexAcross(i);
					if(isPlayerPits(board->currentPlayer, i) && !isEmptyPit(board, accross)){
						int incScore = board->pits[i] + board->pits[accross];
						addScore(board, incScore);
						board->pits[i] = 0;
						board->pits[accross] = 0;
						shells = 0;
					}
					// if not in player pits
					else{
						addPitShell(board, i, &shells);
					}
				}
				// pit is not empty, get all shells in the pit and continue
				else{
					shells += board->pits[i];
					board->pits[i] = 0;
				}
			}
		}
		else{
			if(isAHome(i)){
				//increment score if is player's home
				if(isPlayerHome(board, i)){
					addScore(board, 1);
					--shells;
				}
				//move to next pit if not player's Home
				else{
					continue;
				}
			}
			else{
				addPitShell(board, i, &shells);
			}
		}
		//Update Screen
		clearScreen();
		printf("Player %c's Turn\n", getPlayer(board->currentPlayer));
		printf("Shells: %d\n", shells);
		displayBoard(board);
		printf("\n");
		usleep(500000);
	}
	clearScreen();
	printf("\n\n");
}

int main() {
	Winner winner;
    Sungka sungkaBoard;
    initSungka(&sungkaBoard);
	while(true){
		if(isEndCondition(&sungkaBoard)) break;
		if(!isHasMoves(&sungkaBoard, sungkaBoard.currentPlayer)) switchPlayer(&sungkaBoard);
		int i = getUserMove(&sungkaBoard);
		simulate(&sungkaBoard, i);
		switchPlayer(&sungkaBoard);
	}
	displayBoard(&sungkaBoard);
	winner = whoWinner(&sungkaBoard);
    return 0;
}
