#include <stdio.h>
#include "Constants.h"

void ChangeCruiserMovingState3(int k, int *stats) {
    int i, a1 = -1, a2 = -1;

    if (k % HORIZONTAL_SQUARE + 1 < HORIZONTAL_SQUARE) {
        if (stats[k] == 0 && stats[k + 1] == 0) {
            stats[k + 1] = 3;
            stats[k] = 3;
        }
        if (stats[k] == 3 && stats[k + 1] == 3) {
            a1 = k;
            a2 = k + 1;
        }


    }
    if (k % HORIZONTAL_SQUARE - 1 >= 0) {
        if (stats[k - 1] == 0 && stats[k] == 0) {
            stats[k - 1] = 3;
            stats[k] = 3;

        }
        if (stats[k - 1] == 3 && stats[k] == 3) {
            a1 = k - 1;
            a2 = k;
        }

    }
    for (i = 0; i < HORIZONTAL_SQUARE * VERTICAL_SQUARE; i++) {
        if (stats[i] == 3) {
            if (i != a1 && i != a2) {
                stats[i] = 0;
            }
        }

    }

}


void ChangeCruiserClickState30(int k, int *stats) {
    if (k % HORIZONTAL_SQUARE + 1 < HORIZONTAL_SQUARE) {
        if (stats[k] == 3 && stats[k + 1] == 3) {
            stats[k + 1] = 30;
            stats[k] = 30;

            NUMBER_OF_SHIP[1][2]--;
        }
    }
    if (k % HORIZONTAL_SQUARE - 1 >= 0) {
        if (stats[k - 1] == 3 && stats[k] == 3) {
            stats[k - 1] = 30;
            stats[k] = 30;

            NUMBER_OF_SHIP[1][2]--;
        }
    }
}


void ChangeCruiserMovingState33(int k, int *stats) {
    int i, a1 = -1, a2 = -1;

    if ((int) k / HORIZONTAL_SQUARE + 1 < VERTICAL_SQUARE) {
        if (stats[k] == 0 && stats[k + 1 * HORIZONTAL_SQUARE] == 0) {
            stats[k + 1 * HORIZONTAL_SQUARE] = 3;
            stats[k] = 3;
        }
        if (stats[k] == 3 && stats[k + 1 * HORIZONTAL_SQUARE] == 3) {
            a1 = k;
            a2 = k + 1 * HORIZONTAL_SQUARE;
        }


    }
    if ((int) k / HORIZONTAL_SQUARE - 1 >= 0) {
        if (stats[k - 1 * HORIZONTAL_SQUARE] == 0 && stats[k] == 0) {
            stats[k - 1 * HORIZONTAL_SQUARE] = 3;
            stats[k] = 3;

        }
        if (stats[k - 1 * HORIZONTAL_SQUARE] == 3 && stats[k] == 3) {
            a1 = k - 1 * HORIZONTAL_SQUARE;
            a2 = k;
        }

    }
    for (i = 0; i < HORIZONTAL_SQUARE * VERTICAL_SQUARE; i++) {
        if (stats[i] == 3) {
            if (i != a1 && i != a2) {
                stats[i] = 0;
            }
        }

    }

}

void ChangeCruiserClickState330(int k, int *stats) {
    if ((int) k / HORIZONTAL_SQUARE + 1 < VERTICAL_SQUARE) {
        if (stats[k] == 3 && stats[k + 1 * HORIZONTAL_SQUARE] == 3) {
            stats[k + 1 * HORIZONTAL_SQUARE] = 330;
            stats[k] = 330;

            NUMBER_OF_SHIP[1][2]--;
        }
    }

    if ((int) k / HORIZONTAL_SQUARE - 1 >= 0) {
        if (stats[k - 1 * HORIZONTAL_SQUARE] == 3 && stats[k] == 3) {
            stats[k - 1 * HORIZONTAL_SQUARE] = 330;
            stats[k] = 330;

            NUMBER_OF_SHIP[1][2]--;
        }
    }
}


