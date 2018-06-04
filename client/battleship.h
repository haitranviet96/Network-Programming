#ifndef BATTLESHIP_FILE
#define BATTLESHIP_FILE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define ROWS 11
#define COLS 17

#define NUM_OF_SHIPS  8

#define PLAYER_ONE    0
#define PLAYER_TWO    1

#define WATER         '~'
#define HIT           '*'
#define MISS          'm'

#define LONGSHIP      'l'
#define SUBMARINE     's'
#define CRUISER       'c'
#define HEADQUATER    'h'

typedef enum {
    FALSE, TRUE
} Boolean;

typedef struct watercraft {
    char symbol;
    int length;
    char *name;
} WaterCraft;

typedef struct stats {
    int numHits;
    int numMisses;
} Stats;

typedef struct coordinate {
    int row;
    int column;
} Coordinate;

typedef struct cell {
    char symbol;
    Coordinate position;
} Cell;

int GetMenu(void);

void systemMessage(char *message);

void initializeGameBoard(Cell gameBoard[][COLS]);

void printGameBoard(Cell gameBoard[][COLS], Boolean showLocations);

void placeShipsOnGameBoard(Cell gameBoard[][COLS], WaterCraft ship[]);

void updateGameBoard(Cell gameBoard[][COLS], Coordinate target);

Boolean checkSunkShip(int sunkShip[][NUM_OF_SHIPS], int player, char shipSymbol, char* message);

Boolean convertStringtoPosition(Coordinate position[], char *stringPosition, int length);

Boolean isWinner(Stats players[], int sunkShip[][NUM_OF_SHIPS], int player);

Coordinate getTarget(void);

int checkShot(Cell gameBoard[][COLS], Coordinate target);

int getRandomNumber(int lowest, int highest);

void placeGameBoard(Cell gameBoard[][COLS], WaterCraft *ship, int *table);

#endif