#include "Constants.h"

//#include "getState.c"
//states determine which is select, which is clicked
//EX:   1 means SHIP is selected, and preparing to place
//      10 means SHIP is selected and clicked
//      11 means SHIP is selected and rotated
//      110 means SHIP is selected, rotated and clicked
int getSquare(int x, int y) {
    int sqrn = (int) ((x - 22) / 50) + (int) ((y - 24) / 50) * HORIZONTAL_SQUARE;
    if (22 <= x && x <= 22 + 50 * HORIZONTAL_SQUARE && 24 <= y && y <= 24 + 50 * VERTICAL_SQUARE) return sqrn;
    return -1;
}

int getState(int x, int y) {
    if (891 <= x && x < 1015 && 40 <= y && y <= 92) return 1; // Selecting ship 1
    if (891 <= x && x < 1015 && 108 <= y && y <= 162) return 2; // Selecting ship 2
    if (891 <= x && x < 1015 && 178 <= y && y <= 231) return 3; // Selecting ship 3
    if (890 <= x && x < 940 && 384 <= y && y < 435) return 4;// Selecting headquarter
    if (906 <= x && x < 928 && 307 <= y && y <= 334) return -1; // Remove ship 1
    if (941 <= x && x < 963 && 307 <= y && y <= 334) return -2; // Remove ship 2
    if (976 <= x && x < 998 && 307 <= y && y <= 334) return -3; // Remove ship 3
    if (988 <= x && x < 1008 && 398 <= y && y <= 424) return -4; // Remove headquarter
    if (893 <= x && x < 1002 && 514 <= y && y <= 544) return -5; // NEXT
    return 0;
}

void changeStates(int x, int y, int *states, int click) {
    if (click < LEFT_CLICK && (*states) <= 0) {
        if (getState(x, y) <= 0)(*states) = getState(x, y);
        return;
    }
    if ((*states) == 1 && click == LEFT_CLICK && getSquare(x, y) >= 0) {
        (*states) = 10;

    } else if ((*states) == 1 && click == RIGHT_CLICK && getSquare(x, y) >= 0) {
        (*states) = 11;
    } else if ((*states) == 11 && click == RIGHT_CLICK && getSquare(x, y) >= 0) {
        (*states) = 1;
    } else if ((*states) == 11 && click == LEFT_CLICK && getSquare(x, y) >= 0) {
        (*states) = 110;
    } else if ((*states) == 2 && click == LEFT_CLICK && getSquare(x, y) >= 0) {
        (*states) = 20;
    } else if ((*states) == 2 && click == RIGHT_CLICK && getSquare(x, y) >= 0) {
        (*states) = 22;
    } else if ((*states) == 22 && click == RIGHT_CLICK && getSquare(x, y) >= 0) {
        (*states) = 2;
    } else if ((*states) == 22 && click == LEFT_CLICK && getSquare(x, y) >= 0) {
        (*states) = 220;
    } else if ((*states) == 3 && click == LEFT_CLICK && getSquare(x, y) >= 0) {
        (*states) = 30;
    } else if ((*states) == 3 && click == RIGHT_CLICK && getSquare(x, y) >= 0) {
        (*states) = 33;
    } else if ((*states) == 33 && click == RIGHT_CLICK && getSquare(x, y) >= 0) {
        (*states) = 3;
    } else if ((*states) == 33 && click == LEFT_CLICK && getSquare(x, y) >= 0) {
        (*states) = 330;
    } else if ((*states) == -1 && click == LEFT_CLICK) {

        (*states) = -11;
    } else if ((*states) == -2 && click == LEFT_CLICK) {

        (*states) = -22;
    } else if ((*states) == -3 && click == LEFT_CLICK) {

        (*states) = -33;
    } else if ((*states) == -4 && click == LEFT_CLICK) {

        (*states) = -44;
    } else if ((*states) == 4 && click == LEFT_CLICK && getSquare(x, y) >= 0) {

        (*states) = 40;//Adding black square
    } else if ((*states) == -5 && click == LEFT_CLICK) {

        (*states) = -55;//Confirm complete
    } else if ((*states) == 0 && click == RIGHT_CLICK && getSquare(x, y) >= 0) {

        (*states) = -444;//Removing black square
    } else if (getSquare(x, y) < 0 && click == LEFT_CLICK) {
        (*states) = getState(x, y);
    }
}



