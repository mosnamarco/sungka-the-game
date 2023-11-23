#include "../include/sungka.h"

void initSungka(Sungka *board) {
    board->currentPlayer = true;
	board->isStartState = true;
	board->flow = true;
	board->turns = 0;
    for (int i = 0; i < 16; i++) {
		board->pits[i] = 7;  // Start with 7 shells in each pit
    }
	//Set all scores to 0
	board->pits[7] = 0;
	board->pits[15] = 0;
}

void initPlayer(Sungka* board, bool player){
	char name[256];
	printf("Enter Your Name: ");
	fgets(name, sizeof(name), stdin);
	name[strlen(name) - 1] = '\0';
	if(player){
		printf("Hi %s, You are Player A\n", name);
		board->A.isPlayerA = true;
		board->A.shells = 0;
		board->A.currentIndex = 15;
		strcpy(board->A.name, name);
		return;
	}
	printf("Hi %s, You are Player B\n", name);
	board->B.isPlayerA = false;
	board->B.shells = 0;
	board->B.currentIndex = 7;
	strcpy(board->B.name, name);
}

void flushInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

void displayPit(const int a){
	if (a < 10)
		printf("[ :%d]", a);
	else
		printf("[:%d]", a);
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

void updateScreen(Sungka* board, int updateSpeed){
	clearScreen();
	if(board->isStartState){
		printf("Player %c's Shells: %d\n", getPlayer(true), board->A.shells);
		printf("Player %c's Shells: %d\n", getPlayer(false), board->B.shells);
		displayBoard(board);
	}
	else{
		printf("Player %c's Turn\n", getPlayer(board->currentPlayer));
		if(board->currentPlayer){
			printf("Shells: %d\n", board->A.shells);
		}
		else{
			printf("Shells: %d\n", board->B.shells);
		}
		displayBoard(board);
	}
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

bool isEndCondition(const Sungka* board){
	bool hasMoveA = isHasMoves(board, true);
	bool hasMoveB = isHasMoves(board, false);
	return (!hasMoveA && !hasMoveB)? true : false;
}

Winner whoWinner(const Sungka* board){
	int a = getScore(board, true);
	int b = getScore(board, false);
	if(a > b){
		return A;
	}
	else if(b > a){
		return B;
	}
	return DRAW;
}

char getPlayer(const bool player){
	return (player) ? 'A' : 'B';
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
	printf("Player %c [0-6]: ", getPlayer(board->currentPlayer));
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

void lastShellAtHome(Sungka* board, int* shells){
	*shells = 0;
	addScore(board, 1);
	toggleToMove(board);
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
		// pit is not empty, get all shells in the pit and continue
		if(!isEmptyPit(board, i)){
			getShellsFromPit(board, shells, i);
			return;
		}
		// pit is empty
		// if not in player pits
		int accross = getPitIndexAcross(i);
		if(!isPlayerPits(board->currentPlayer, i)){
			addPitShell(board, i, shells);
		}
		//get all on the current and accross, then add to score
		else if(!isEmptyPit(board, accross)){
			int incScore = board->pits[i] + board->pits[accross];
			addScore(board, incScore);
			board->pits[i] = 0;
			board->pits[accross] = 0;
			*shells = 0;
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

bool startState(Sungka* board){
	//Get Input A and B
	bool whoFinish, isSet = false;
	setUserMove(board);
	switchPlayer(board);
	setUserMove(board);
	switchPlayer(board);
	int* AShells = &(board->A.shells);
	int* BShells = &(board->B.shells);
	while( *AShells >= 0 || *BShells >= 0){
		//Check if Somone has exhaust their shells on hand
		if(*AShells == 0 && *BShells == 0)
			break;
		if(!isSet){
			if(*AShells == 0){
				whoFinish = true;
				isSet = true;
			}
			else if(*BShells == 0){
				whoFinish = false;
				isSet = true;
			}
		}
		if( *AShells >= 0 ){
			updateScreen(board, 500000);
			simulateStep(board);
			switchPlayer(board);
		}
		if (*BShells >=0){
			updateScreen(board, 500000);
			simulateStep(board);
			switchPlayer(board);
		}
	}
	board->isStartState = false;
	return whoFinish;
}