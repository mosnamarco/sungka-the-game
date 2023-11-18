#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>

// Typedefs
typedef struct Sungka Sungka;
typedef enum Winner Winner;

enum Winner{
	A,
	DRAW,
	B
};

struct Sungka {
    int pits[16]; // 0 to 6: Player B's pits; 7: B's Home; 8 to 14: A's Pits; 15: A's Home
	bool currentPlayer;  // true for Player A, false for Player B
	bool flow; // true: clockwise, false counter clockwise;
	int turns; // number of turns in the game
};

//Flush input buffer
void flushInputBuffer();

void initSungka(Sungka*);

//Format Print a Representation of a pit
void displayPit(const int);

//Display the pits on a side of the board
void displayPits(const int*, const bool);

// Display Which Pits are Playable
void displayGuide();

//Display the Whole Board
void displayBoard(const Sungka*);

//Clear the Screen
void clearScreen();

//Switch Player's Turn
void switchPlayer(Sungka*);

//Add Score to a Player
void addScore(Sungka*, int);

//Add shell to a Pit
void addPitShell(Sungka*, int, int*);

//Check Whether a Pit is a player's home
bool isPlayerHome(Sungka*, int);

//Check Whether a Pit is a Player's Pit
bool isPlayerPits(bool, int);

//Check is a Move is a Valid Move
bool isValid(const Sungka*, const bool, char*, int*);

//Check if a Player's Pit is Empty
bool isEmptyPit(Sungka*, int);

//Check if a Player has possible moves
bool isHasMoves(const Sungka*,  const bool);

//Check if the End Condition is Met
bool isEndCondition(const Sungka*);

Winner whoWinner(const Sungka*);

//Return the Player's Name
char getPlayer(const bool);

//Get the Index Across a pit
int getPitIndexAcross(int);

//Get the score of a player
int getScore(const Sungka*, const bool);

//Get the User Move
int getUserMove(Sungka*);

//Simulate a player's turn
void simulate(Sungka*, int);