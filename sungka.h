#include <stdio.h>
#include <stdbool.h>
#include <unistd.h> 

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
	bool finished; //true: all regular pits are empty; false: there are non empty pits
	int turns; // number of turns in the game
};

void initSungka(Sungka*);

void displayPit(const int);

//Display the pits on a side of the board
void displayPits(const int*, const bool);

void displayGuide();

//Display the Whole Board
void displayBoard(const Sungka*);

void switchPlayer(Sungka*);

void addScore(Sungka*, int);

void addPitShell(Sungka*, int, int*);

bool isPlayerHome(Sungka*, int);

bool isPlayerPits(bool, int);

bool isEmptyPit(Sungka*, int);

bool isHasMoves(const bool, const int*);

bool isFinished(Sungka*);

char getPlayer(const bool);

int getPitIndexAcross(int);

int getScore(const Sungka*, const bool);

int getUserMove(Sungka*);

void simulate(Sungka*, int);