#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Constants.h"
#include "Utils.h"
#include "battleship.h"

int GetMenu() {
    int option;
    printf("> Welcome to Battleship!\n");
    printf("> Please select from the following menu:\n");
    printf("> [1] Player 1 Go First\n");
    printf("> [2] Player 2 Go First\n");
    printf("> [3] Random\n");
    printf("> [4] Exit\n");
    printf("> Enter Option: ");
    scanf("%d", &option);
    return option;
}

void initializeGameBoard(Cell gameBoard[][COLS]) {
    int i = 0, j = 0;

    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++) {
            gameBoard[i][j].symbol = WATER;
            gameBoard[i][j].position.row = i;
            gameBoard[i][j].position.column = j;
        }
}

void printGameBoard(Cell gameBoard[][COLS], Boolean showLocations) {
    int i = 0, j = 0;

    printf("   A B C D E F G H I J K L M N O P Q\n");

    for (i = 0; i < ROWS; i++) {
        if (i < 10) {
            printf("%d  ", i);
        } else {
            printf("%d ", i);
        }
        for (j = 0; j < COLS; j++) {
            if (showLocations == TRUE)
                printf("%c ", gameBoard[i][j].symbol);
            else {
                switch (gameBoard[i][j].symbol) {
                    case HIT:
                        printf("%c ", HIT);
                        break;
                    case MISS:
                        printf("%c ", MISS);
                        break;
                    case WATER:
                    default:
                        printf("%c ", WATER);
                        break;
                }
            }
        }

        putchar('\n');
    }
}

void placeShipsOnGameBoard(Cell gameBoard[][COLS], WaterCraft ship[]) {
    char stringPosition[11] = "";
    int i = 0, j = 0;

    Coordinate position[5];
    Boolean isValid = FALSE;

    fflush(stdin);

    for (i = 0; i < NUM_OF_SHIPS; i++) {

        while (TRUE) {
            system("clear");
            //system ("cls");
            printGameBoard(gameBoard, TRUE);
            printf("> Place the %s across %d cells (either horizontal or vertical, no spaces):\n", ship[i].name,
                   ship[i].length);
            printf("> ");
            scanf("%s", stringPosition);

            /* convertStringtoPosition returns false if unsuccessful */
            if (convertStringtoPosition(position, stringPosition, ship[i].length)) {

                isValid = TRUE;

                for (j = 0; j < ship[i].length; j++) {

                    if (gameBoard[position[j].row][position[j].column].symbol == WATER) {
                        gameBoard[position[j].row][position[j].column].symbol = ship[i].symbol;
                    } else {
                        isValid = FALSE;
                        printf("> Invalid input!\n");

                        if (j != 0)
                            while (j >= 0) {
                                gameBoard[position[j].row][position[j].column].symbol = WATER;
                                j--;
                            }

                        break;
                    }
                }
            } else {
                isValid = FALSE;
                printf("> Invalid input!\n");
            }

            if (isValid == TRUE) break;
        }

    }
}

void updateGameBoard(Cell gameBoard[][COLS], Coordinate target) {
    switch (gameBoard[target.row][target.column].symbol) {
        /* miss */
        case WATER:
            gameBoard[target.row][target.column].symbol = MISS;
            break;

            /* hit */
        case LONGSHIP:
        case SUBMARINE:
        case CRUISER:
        case HEADQUATER:
            gameBoard[target.row][target.column].symbol = HIT;
            break;

        case HIT:
        case MISS:
        default:
            break;
    }
}

void systemMessage(char *message) {
    char ch = '\0';

    do {
        printf("%s", message);
        getchar();
    } while ((ch = getchar()) != '\n');
    //system ("cls");
    system("clear");
}

Boolean checkSunkShip(int sunkShip[][NUM_OF_SHIPS], int player, char shipSymbol, char *message) {
    Boolean sunked = FALSE;

    switch (shipSymbol) {
        case LONGSHIP:
            if (--sunkShip[player][0] == 0 || --sunkShip[player][1] == 0 || --sunkShip[player][2] == 0) {
                sprintf(message,"> Player %s's Long ship sunked!\n", inputText);
                sunked = TRUE;
            }
            break;

        case SUBMARINE:
            if (--sunkShip[player][3] == 0 || --sunkShip[player][4] == 0) {
                sprintf(message,"> Player %s's Submarine sunked!\n", inputText);
                sunked = TRUE;
            }
            break;

        case CRUISER:
            if (--sunkShip[player][5] == 0 || --sunkShip[player][6] == 0) {
                sprintf(message,"> Player %s's Cruiser sunked!\n", inputText);
                sunked = TRUE;
            }
            break;

        case HEADQUATER:
            if (--sunkShip[player][7] == 0) {
                sprintf(message,"> Player %s's Headquater sunked!\n",inputText);
                sunked = TRUE;
            }
            break;
    }

    return sunked;
}

Boolean convertStringtoPosition(Coordinate position[], char *stringPosition, int length) {
    Boolean flag = TRUE;
    char temp = '\0';
    int i = 0, j = 0, k = 1;

    // Check input length
    if (strlen(stringPosition) / 3 <= length <= strlen(stringPosition) / 2) {
        // Loop through ship length
        for (i = 0; i < length && flag; i++) {

            if ((stringPosition[j] - '0') < ROWS && (stringPosition[k] - 'A') < COLS) {
                if ((stringPosition[j] - '0') == 1 && (stringPosition[k] - '0') == 0) {
                    position[i].row = 10;
                    position[i].column = stringPosition[k + 1] - 'A';
                    j += 3;
                    k += 3;
                } else {
                    position[i].row = stringPosition[j] - '0';
                    position[i].column = stringPosition[k] - 'A';

                    j += 2;
                    k += 2;
                }
            } else {
                flag = FALSE;
            }
        }
    } else {
        flag = FALSE;
    }

    return flag;
}

Coordinate getTarget(void) {
    Coordinate target;
    int flag = 0;
    char column;

    printf("> Enter Target (ex. > 3 D):\n");
    do {
        fflush(stdin);
        printf("> ");
        flag = scanf("%d %c", &target.row, &column);
        target.column = column - 'A';
    } while (flag != 2 || target.row >= ROWS || target.column >= COLS);
    return target;
}

int checkShot(Cell gameBoard[][COLS], Coordinate target) {
    int hit = -2;

    switch (gameBoard[target.row][target.column].symbol) {
        /* miss */
        case WATER:
            hit = 0;
            break;

            /* hit */
        case LONGSHIP:
        case SUBMARINE:
        case CRUISER:
        case HEADQUATER:
            hit = 1;
            break;

        case HIT:
        case MISS:
        default:
            hit = -1;
            break;
    }

    return hit;
}

int getRandomNumber(int lowest, int highest) {
    return rand() % (highest - lowest + 1) + lowest;
}

Boolean isWinner(Stats players[], int sunkShip[][NUM_OF_SHIPS], int player) {
    Boolean isWin = FALSE;

    if (sunkShip[!player][7] == 0)
        isWin = TRUE;
    if (players[player].numHits == 28 && sunkShip[player][7] != 0)
        isWin = TRUE;


    return isWin;
}

void placeGameBoard(Cell gameBoard[][COLS], WaterCraft *ship, int *table) {
    int i = 0, j = 0;

    for (i = 0; i < COLS; ++i) {
        for (j = 0; j < ROWS; ++j) {
            if (table[i + COLS * j] == 10 || table[i + COLS * j] == 110) {
                gameBoard[j][i].symbol = ship[0].symbol;
            } else if (table[i + COLS * j] == 20 || table[i + COLS * j] == 220) {
                gameBoard[j][i].symbol = ship[3].symbol;
            } else if (table[i + COLS * j] == 30 || table[i + COLS * j] == 330) {
                gameBoard[j][i].symbol = ship[5].symbol;
            } else if (table[i + COLS * j] == 40) {
                gameBoard[j][i].symbol = ship[7].symbol;
            }
        }
    }
}