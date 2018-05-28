#include <stdio.h>
#include "Constants.h"

void ChangeShipMovingState1(int square, int *tableStatus) {
    int i, a1 = -1, a2 = -1, a3 = -1, a4 = -1;

    int verticalIndex = square % HORIZONTAL_SQUARE;

    if (verticalIndex - 1 >= 0 && verticalIndex - 2 >= 0 && verticalIndex + 1 < HORIZONTAL_SQUARE) {
        if (tableStatus[square - 1] == 0 && tableStatus[square] == 0 && tableStatus[square - 2] == 0 && tableStatus[square + 1] == 0) {
            tableStatus[square - 1] = 1;
            tableStatus[square - 2] = 1;
            tableStatus[square + 1] = 1;
            tableStatus[square] = 1;
        }

        if (tableStatus[square - 1] == 1 && tableStatus[square] == 1 && tableStatus[square - 2] == 1 && tableStatus[square + 1] == 1) {
            a1 = square - 1;
            a2 = square - 2;
            a3 = square;
            a4 = square + 1;
        }
    }

    if (verticalIndex - 1 >= 0 && verticalIndex + 2 < HORIZONTAL_SQUARE && verticalIndex + 1 < HORIZONTAL_SQUARE) {
        if (tableStatus[square - 1] == 0 && tableStatus[square] == 0 && tableStatus[square + 2] == 0 && tableStatus[square + 1] == 0) {
            tableStatus[square - 1] = 1;
            tableStatus[square + 2] = 1;
            tableStatus[square + 1] = 1;
            tableStatus[square] = 1;
        }

        if (tableStatus[square - 1] == 1 && tableStatus[square] == 1 && tableStatus[square + 2] == 1 && tableStatus[square + 1] == 1) {
            a1 = square - 1;
            a2 = square + 2;
            a3 = square;
            a4 = square + 1;
        }
    }

    // clear previous position draw
    for (i = 0; i < HORIZONTAL_SQUARE * VERTICAL_SQUARE; i++) {
        if (tableStatus[i] == 1) {
            if (i != a1 && i != a2 && i != a3 && i != a4) {
                tableStatus[i] = 0;
            }
        }
    }
}

void ChangeShipClickState10(int square, int *tableStatus) {
    //state=1;

    int verticalIndex = square % HORIZONTAL_SQUARE;

    if (verticalIndex - 1 >= 0 && verticalIndex - 2 >= 0 && verticalIndex + 1 < HORIZONTAL_SQUARE) {
        if (tableStatus[square - 1] == 1 && tableStatus[square] == 1 && tableStatus[square - 2] == 1 && tableStatus[square + 1] == 1) {
            tableStatus[square - 1] = 10;
            tableStatus[square - 2] = 10;
            tableStatus[square + 1] = 10;
            tableStatus[square] = 10;

            NUMBER_OF_SHIP[1][0]--;
        }
    }

    if (verticalIndex - 1 >= 0 && verticalIndex + 2 < HORIZONTAL_SQUARE && verticalIndex + 1 < HORIZONTAL_SQUARE) {
        if (tableStatus[square - 1] == 1 && tableStatus[square] == 1 && tableStatus[square + 2] == 1 && tableStatus[square + 1] == 1) {
            tableStatus[square - 1] = 10;
            tableStatus[square + 2] = 10;
            tableStatus[square + 1] = 10;
            tableStatus[square] = 10;

            NUMBER_OF_SHIP[1][0]--;
        }
    }
}

void ChangeShipMovingState11(int k, int *stats) {
    int i, a1 = -1, a2 = -1, a3 = -1, a4 = -1;


    if ((int) k / HORIZONTAL_SQUARE - 1 >= 0 && (int) k / HORIZONTAL_SQUARE - 2 >= 0 && (int) k / HORIZONTAL_SQUARE + 1 < HORIZONTAL_SQUARE) {


        if (stats[k - 1 * HORIZONTAL_SQUARE] == 0 && stats[k] == 0 && stats[k - 2 * HORIZONTAL_SQUARE] == 0 &&
            stats[k + 1 * HORIZONTAL_SQUARE] == 0) {

            stats[k - 1 * HORIZONTAL_SQUARE] = 1;
            stats[k - 2 * HORIZONTAL_SQUARE] = 1;
            stats[k + 1 * HORIZONTAL_SQUARE] = 1;
            stats[k] = 1;
        }
        if (stats[k - 1 * HORIZONTAL_SQUARE] == 1 && stats[k] == 1 && stats[k - 2 * HORIZONTAL_SQUARE] == 1 &&
            stats[k + 1 * HORIZONTAL_SQUARE] == 1) {
            a1 = k - 1 * HORIZONTAL_SQUARE;
            a2 = k - 2 * HORIZONTAL_SQUARE;
            a3 = k;
            a4 = k + 1 * HORIZONTAL_SQUARE;
        }


    }
    if ((int) k / HORIZONTAL_SQUARE - 1 >= 0 && (int) k / HORIZONTAL_SQUARE + 2 < VERTICAL_SQUARE && (int) k / HORIZONTAL_SQUARE + 1 < VERTICAL_SQUARE) {
        if (stats[k - 1 * HORIZONTAL_SQUARE] == 0 && stats[k] == 0 && stats[k + 2 * HORIZONTAL_SQUARE] == 0 &&
            stats[k + 1 * HORIZONTAL_SQUARE] == 0) {
            stats[k - 1 * HORIZONTAL_SQUARE] = 1;
            stats[k + 2 * HORIZONTAL_SQUARE] = 1;
            stats[k + 1 * HORIZONTAL_SQUARE] = 1;
            stats[k] = 1;

        }
        if (stats[k - 1 * HORIZONTAL_SQUARE] == 1 && stats[k] == 1 && stats[k + 2 * HORIZONTAL_SQUARE] == 1 &&
            stats[k + 1 * HORIZONTAL_SQUARE] == 1) {
            a1 = k - 1 * HORIZONTAL_SQUARE;
            a2 = k + 2 * HORIZONTAL_SQUARE;
            a3 = k;
            a4 = k + 1 * HORIZONTAL_SQUARE;
        }

    }
    for (i = 0; i < HORIZONTAL_SQUARE * VERTICAL_SQUARE; i++) {
        if (stats[i] == 1) {
            if (i != a1 && i != a2 && i != a3 && i != a4) {
                stats[i] = 0;
            }
        }

    }


}

void ChangeShipClickState110(int k, int *stats) {
    if ((int) k / HORIZONTAL_SQUARE - 1 >= 0 && (int) k / HORIZONTAL_SQUARE - 2 >= 0 && (int) k / HORIZONTAL_SQUARE + 1 < VERTICAL_SQUARE) {
        if (stats[k - 1 * HORIZONTAL_SQUARE] == 1 && stats[k] == 1 && stats[k - 2 * HORIZONTAL_SQUARE] == 1 &&
            stats[k + 1 * HORIZONTAL_SQUARE] == 1) {

            stats[k - 1 * HORIZONTAL_SQUARE] = 110;
            stats[k - 2 * HORIZONTAL_SQUARE] = 110;
            stats[k + 1 * HORIZONTAL_SQUARE] = 110;
            stats[k] = 110;

            NUMBER_OF_SHIP[1][0]--;
        }
    }

    if ((int) k / HORIZONTAL_SQUARE - 1 >= 0 && (int) k / HORIZONTAL_SQUARE + 2 < VERTICAL_SQUARE && (int) k / HORIZONTAL_SQUARE + 1 < VERTICAL_SQUARE) {
        if (stats[k - 1 * HORIZONTAL_SQUARE] == 1 && stats[k] == 1 && stats[k + 2 * HORIZONTAL_SQUARE] == 1 &&
            stats[k + 1 * HORIZONTAL_SQUARE] == 1) {
            stats[k - 1 * HORIZONTAL_SQUARE] = 110;
            stats[k + 2 * HORIZONTAL_SQUARE] = 110;
            stats[k + 1 * HORIZONTAL_SQUARE] = 110;
            stats[k] = 110;

            NUMBER_OF_SHIP[1][0]--;
        }
    }
}
