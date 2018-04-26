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
    if (891 <= x && x < 1015 && 40 <= y && y <= 92)
        return 1; // Selecting ship 1
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

void changeStates(int x, int y) {
    if (click < LEFT_CLICK && editState <= 0) {
        if (getState(x, y) <= 0)
            editState = getState(x, y);
        return;
    }
    if (editState == 1 && click == LEFT_CLICK && getSquare(x, y) >= 0) {
        editState = 10;

    } else if (editState == 1 && click == RIGHT_CLICK && getSquare(x, y) >= 0) {
        editState = 11;
    } else if (editState == 11 && click == RIGHT_CLICK && getSquare(x, y) >= 0) {
        editState = 1;
    } else if (editState == 11 && click == LEFT_CLICK && getSquare(x, y) >= 0) {
        editState = 110;
    } else if (editState == 2 && click == LEFT_CLICK && getSquare(x, y) >= 0) {
        editState = 20;
    } else if (editState == 2 && click == RIGHT_CLICK && getSquare(x, y) >= 0) {
        editState = 22;
    } else if (editState == 22 && click == RIGHT_CLICK && getSquare(x, y) >= 0) {
        editState = 2;
    } else if (editState == 22 && click == LEFT_CLICK && getSquare(x, y) >= 0) {
        editState = 220;
    } else if (editState == 3 && click == LEFT_CLICK && getSquare(x, y) >= 0) {
        editState = 30;
    } else if (editState == 3 && click == RIGHT_CLICK && getSquare(x, y) >= 0) {
        editState = 33;
    } else if (editState == 33 && click == RIGHT_CLICK && getSquare(x, y) >= 0) {
        editState = 3;
    } else if (editState == 33 && click == LEFT_CLICK && getSquare(x, y) >= 0) {
        editState = 330;
    } else if (editState == -1 && click == LEFT_CLICK) {

        editState = -11;
    } else if (editState == -2 && click == LEFT_CLICK) {

        editState = -22;
    } else if (editState == -3 && click == LEFT_CLICK) {

        editState = -33;
    } else if (editState == -4 && click == LEFT_CLICK) {

        editState = -44;
    } else if (editState == 4 && click == LEFT_CLICK && getSquare(x, y) >= 0) {

        editState = 40;//Adding black square
    } else if (editState == -5 && click == LEFT_CLICK) {

        editState = -55;//Confirm complete
    } else if (editState == 0 && click == RIGHT_CLICK && getSquare(x, y) >= 0) {

        editState = -444;//Removing black square
    } else if (getSquare(x, y) < 0 && click == LEFT_CLICK) {
        editState = getState(x, y);
    }
}



