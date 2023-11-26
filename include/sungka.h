# ifndef SUNGKA_H
# define SUNGKA_H
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>

// Typedefs
typedef struct Score Score;
typedef struct Sungka Sungka;
typedef struct Player Player;

//Define type alias
#define on true
#define off false

struct Score{
	unsigned int win;
	unsigned int draw;
	unsigned int lost;
};

struct Player{
	bool who; // true for Player A, false for Player B
	bool toMove; // Check if the Player to Move
	bool isMoving; // Check if the Player is Moving
	char name[256]; // Name of the Player
	int shells; //number of shells on hand
	int currentIndex;
	Score score; //Score of Player i.e # of (win, draw, lost)
};

struct Sungka {
    int pits[16]; // 0 to 6: Player B's pits; 7: B's Home; 8 to 14: A's Pits; 15: A's Home
	bool currentPlayer;  // true for Player A, false for Player B
	bool isStartState; // Check if it is still start state
	bool flow; // true: clockwise, false counter clockwise;
	int turns; // number of turns in the game
	int winner; // 1: Player A, 0: Player B, -1: Draw
	Player A;
	Player B;
};

//Initialize Sungka Board
void initSungka(Sungka*);

//Initialize a Player
void initPlayer(Sungka*, bool);

//Initialize Score
void initScore(Player*);

//Flush input buffer
void flushInputBuffer();

//Format Print a Representation of a pit
void displayPit(const Sungka*, const int);

//Display the pits on a side of the board
void displayPits(const Sungka*, const bool);

// Display Which Pits are Playable
void displayGuide();

//Display the Whole Board
void displayBoard(const Sungka*);

//Display the Updated Board relative to who's Turn it is
void updateScreen(Sungka*, const bool, int);

//Display the Board during Start State
void startStateUpdate(Sungka*, int);

//Clear the Screen
void clearScreen();

//Switch Player's Turn
void switchPlayer(Sungka*);

//Add Score to a Player
void addScore(Sungka*, int);

/*Increment shell to a Pit, then Decrement the number of shells on hand 
param 1: Reference to sungka board: Sungka* 
param 2: Index to put the shell: int
param 3: Reference to the shell: int
*/
void addPitShell(Sungka*, int, int*);

//Check Whether a Pit is a player's home
bool isPlayerHome(Sungka*, int);

//Check Whether a Pit is a Player's Pit
bool isPlayerPits(const bool, const int);

//Check if the input is valid
bool isValid(const Sungka*, const bool, char*, int*);

//Check if a Player's Pit is Empty
bool isEmptyPit(const Sungka*, const int);

//Check if a Player has possible moves
bool isHasMoves(const Sungka*,  const bool);

//Check if a Player has shells on hand
bool isHasShells(Sungka*, const bool);

//Check if the End Condition is Met
bool isEndCondition(Sungka*);

//Return the Pointer to Player Object
Player* getPlayer(Sungka*, const bool);

/* 
	Get Score of Player
	param 1: Player Object
	param 2: Which Score to Get, 1: win, 2: draw, 3: lost
*/
unsigned int getPlayerScore(Player, int type);

//Get the Index Across a pit
int getPitIndexAcross(const int);

//Get the score of a player
int getScore(const Sungka*, const bool);

void getShellsFromPit(Sungka*, int*, const int i);

//Get the User Move
void setUserMove(Sungka*);

//Toggle Current Player to Move
void toggleToMove(Sungka*);

//Toggle Specifici Player to Move
void toggleToMovePlayer(Sungka*, bool, bool);

//Logic if the last shell of the Player is at their Home
void lastShellAtHome(Sungka*, int*);

//Logic if the player's on hand shells is 1
void lastShellLogic(Sungka*, int*, int);

//Logic if the player's on hand shells are greater than 1
void notLastShellLogic(Sungka*, int*, int);

//Simulate a Single Step
void simulateStep(Sungka*);

//Simulate Start State of the Game
void startState(Sungka*, const bool, const int);

//Simulate Normal State
void normalState(Sungka*, const bool, const int);

//sets who won
void setWinner(Sungka*);

//Check Who is Winner
void whoWinner(Sungka*, const bool);

#endif