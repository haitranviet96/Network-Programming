#include "Constants.h"

void ChangeSubmarineMovingState2(int k, int *stats) {
    int i, a1 = -1, a2 = -1, a3 = -1, a4 = -1, a5 = -1, a6 = -1;

    if (k % HORIZONTAL_SQUARE - 1 >= 0 && (int) k / HORIZONTAL_SQUARE + 1 < VERTICAL_SQUARE && k % HORIZONTAL_SQUARE + 1 < HORIZONTAL_SQUARE) {
        if (stats[k - 1] == 0 && stats[k] == 0 && stats[k + 1] == 0 && stats[k + 1 * HORIZONTAL_SQUARE] == 0 &&
            stats[k + 1 * HORIZONTAL_SQUARE + 1] == 0 && stats[k + 1 * HORIZONTAL_SQUARE - 1] == 0) {
            stats[k - 1] = 2;
            stats[k + 1 * HORIZONTAL_SQUARE] = 2;
            stats[k + 1] = 2;
            stats[k] = 2;
            stats[k + 1 * HORIZONTAL_SQUARE + 1] = 2;
            stats[k + 1 * HORIZONTAL_SQUARE - 1] = 2;
        }
        if (stats[k - 1] == 2 && stats[k] == 2 && stats[k + 1 * HORIZONTAL_SQUARE] == 2 && stats[k + 1] == 2 &&
            stats[k + 1 * HORIZONTAL_SQUARE - 1] == 2 && stats[k + 1 * HORIZONTAL_SQUARE + 1] == 2) {
            a1 = k - 1;
            a2 = k + 1;
            a3 = k;
            a4 = k + 1 * HORIZONTAL_SQUARE - 1;
            a5 = k + 1 * HORIZONTAL_SQUARE + 1;
            a6 = k + 1 * HORIZONTAL_SQUARE;
        }


    }

    if (k % HORIZONTAL_SQUARE - 1 >= 0 && (int) k / HORIZONTAL_SQUARE - 1 >= 0 && k % HORIZONTAL_SQUARE + 1 < HORIZONTAL_SQUARE) {
        if (stats[k - 1] == 0 && stats[k] == 0 && stats[k + 1] == 0 && stats[k - 1 * HORIZONTAL_SQUARE] == 0 &&
            stats[k - 1 * HORIZONTAL_SQUARE + 1] == 0 && stats[k - 1 * HORIZONTAL_SQUARE - 1] == 0) {
            stats[k - 1] = 2;
            stats[k - 1 * HORIZONTAL_SQUARE] = 2;
            stats[k + 1] = 2;
            stats[k] = 2;
            stats[k - 1 * HORIZONTAL_SQUARE + 1] = 2;
            stats[k - 1 * HORIZONTAL_SQUARE - 1] = 2;
        }
        if (stats[k - 1] == 2 && stats[k] == 2 && stats[k - 1 * HORIZONTAL_SQUARE] == 2 && stats[k + 1] == 2 &&
            stats[k - 1 * HORIZONTAL_SQUARE - 1] == 2 && stats[k - 1 * HORIZONTAL_SQUARE + 1] == 2) {
            a1 = k - 1;
            a2 = k + 1;
            a3 = k;
            a4 = k - 1 * HORIZONTAL_SQUARE - 1;
            a5 = k - 1 * HORIZONTAL_SQUARE + 1;
            a6 = k - 1 * HORIZONTAL_SQUARE;
        }

    }
    for (i = 0; i < HORIZONTAL_SQUARE * VERTICAL_SQUARE; i++) {
        if (stats[i] == 2) {
            if (i != a1 && i != a2 && i != a3 && i != a4 && i != a5 && i != a6) {
                stats[i] = 0;
            }
        }

    }

}

void ChangeSubmarineClickState20(int k, int *stats) {
    if (k % HORIZONTAL_SQUARE - 1 >= 0 && (int) k / HORIZONTAL_SQUARE + 1 < VERTICAL_SQUARE && k % HORIZONTAL_SQUARE + 1 < HORIZONTAL_SQUARE) {
        if (stats[k - 1] == 2 && stats[k] == 2 && stats[k + 1] == 2 && stats[k + 1 * HORIZONTAL_SQUARE] == 2 &&
            stats[k + 1 * HORIZONTAL_SQUARE + 1] == 2 && stats[k + 1 * HORIZONTAL_SQUARE - 1] == 2) {
            stats[k - 1] = 20;
            stats[k + 1 * HORIZONTAL_SQUARE] = 20;
            stats[k + 1] = 20;
            stats[k] = 20;
            stats[k + 1 * HORIZONTAL_SQUARE + 1] = 20;
            stats[k + 1 * HORIZONTAL_SQUARE - 1] = 20;

            NUMBER_OF_SHIP[1][1]--;
        }
    }

    if (k % HORIZONTAL_SQUARE - 1 >= 0 && (int) k / HORIZONTAL_SQUARE - 1 >= 0 && k % HORIZONTAL_SQUARE + 1 < HORIZONTAL_SQUARE) {
        if (stats[k - 1] == 2 && stats[k] == 2 && stats[k + 1] == 2 && stats[k - 1 * HORIZONTAL_SQUARE] == 2 &&
            stats[k - 1 * HORIZONTAL_SQUARE + 1] == 2 && stats[k - 1 * HORIZONTAL_SQUARE - 1] == 2) {
            stats[k - 1] = 20;
            stats[k - 1 * HORIZONTAL_SQUARE] = 20;
            stats[k + 1] = 20;
            stats[k] = 20;
            stats[k - 1 * HORIZONTAL_SQUARE + 1] = 20;
            stats[k - 1 * HORIZONTAL_SQUARE - 1] = 20;

            NUMBER_OF_SHIP[1][1]--;
        }
    }
}

void ChangeSubmarineMovingState22(int k, int *stats) {
    int i, a1 = -1, a2 = -1, a3 = -1, a4 = -1, a5 = -1, a6 = -1;

    if ((int) k / HORIZONTAL_SQUARE - 1 >= 0 && (int) k / HORIZONTAL_SQUARE + 1 < VERTICAL_SQUARE && k % HORIZONTAL_SQUARE + 1 < HORIZONTAL_SQUARE) {
        if (stats[k - 1 * HORIZONTAL_SQUARE] == 0 && stats[k] == 0 && stats[k + 1] == 0 && stats[k + 1 * HORIZONTAL_SQUARE] == 0 &&
            stats[k + 1 * HORIZONTAL_SQUARE + 1] == 0 && stats[k - 1 * HORIZONTAL_SQUARE + 1] == 0) {
            stats[k - 1 * HORIZONTAL_SQUARE] = 2;
            stats[k + 1 * HORIZONTAL_SQUARE] = 2;
            stats[k + 1] = 2;
            stats[k] = 2;
            stats[k + 1 * HORIZONTAL_SQUARE + 1] = 2;
            stats[k - 1 * HORIZONTAL_SQUARE + 1] = 2;
        }
        if (stats[k - 1 * HORIZONTAL_SQUARE] == 2 && stats[k] == 2 && stats[k + 1 * HORIZONTAL_SQUARE] == 2 && stats[k + 1] == 2 &&
            stats[k - 1 * HORIZONTAL_SQUARE + 1] == 2 && stats[k + 1 * HORIZONTAL_SQUARE + 1] == 2) {
            a1 = k - 1 * HORIZONTAL_SQUARE;
            a2 = k + 1;
            a3 = k;
            a4 = k - 1 * HORIZONTAL_SQUARE + 1;
            a5 = k + 1 * HORIZONTAL_SQUARE + 1;
            a6 = k + 1 * HORIZONTAL_SQUARE;
        }


    }

    if ((int) k / HORIZONTAL_SQUARE - 1 >= 0 && (int) k / HORIZONTAL_SQUARE + 1 < VERTICAL_SQUARE && k % HORIZONTAL_SQUARE - 1 >= 0) {

        if (stats[k - 1 * HORIZONTAL_SQUARE] == 0 && stats[k] == 0 && stats[k - 1] == 0 && stats[k + 1 * HORIZONTAL_SQUARE] == 0 &&
            stats[k + 1 * HORIZONTAL_SQUARE - 1] == 0 && stats[k - 1 * HORIZONTAL_SQUARE - 1] == 0) {

            stats[k - 1 * HORIZONTAL_SQUARE] = 2;
            stats[k + 1 * HORIZONTAL_SQUARE] = 2;
            stats[k - 1] = 2;
            stats[k] = 2;
            stats[k + 1 * HORIZONTAL_SQUARE - 1] = 2;
            stats[k - 1 * HORIZONTAL_SQUARE - 1] = 2;
            //printf("fjlsdjfksdlfkjsdklf\n");
        }
        if (stats[k - 1 * HORIZONTAL_SQUARE] == 2 && stats[k] == 2 && stats[k + 1 * HORIZONTAL_SQUARE] == 2 && stats[k - 1] == 2 &&
            stats[k - 1 * HORIZONTAL_SQUARE - 1] == 2 && stats[k + 1 * HORIZONTAL_SQUARE - 1] == 2) {
            a1 = k - 1 * HORIZONTAL_SQUARE;
            a2 = k - 1;
            a3 = k;
            a4 = k - 1 * HORIZONTAL_SQUARE - 1;
            a5 = k + 1 * HORIZONTAL_SQUARE - 1;
            a6 = k + 1 * HORIZONTAL_SQUARE;


        }
    }


    for (i = 0; i < HORIZONTAL_SQUARE * VERTICAL_SQUARE; i++) {
        if (stats[i] == 2) {
            if (i != a1 && i != a2 && i != a3 && i != a4 && i != a5 && i != a6) {
                stats[i] = 0;
            }
        }


    }


}

void ChangeSubmarineClickState220(int k, int *stats) {
    if ((int) k / HORIZONTAL_SQUARE - 1 >= 0 && (int) k / HORIZONTAL_SQUARE + 1 < VERTICAL_SQUARE && k % HORIZONTAL_SQUARE + 1 < HORIZONTAL_SQUARE) {
        // printf("%d %d %d %d %d %d\n",stats[k-1*HORIZONTAL_SQUARE],stats[k],stats[k+1],stats[k+1*HORIZONTAL_SQUARE],stats[k+1*HORIZONTAL_SQUARE+1],stats[k-1*HORIZONTAL_SQUARE+1]);
        if (stats[k - 1 * HORIZONTAL_SQUARE] == 2 && stats[k] == 2 && stats[k + 1] == 2 && stats[k + 1 * HORIZONTAL_SQUARE] == 2 &&
            stats[k + 1 * HORIZONTAL_SQUARE + 1] == 2 && stats[k - 1 * HORIZONTAL_SQUARE + 1] == 2) {
            stats[k - 1 * HORIZONTAL_SQUARE] = 220;
            stats[k + 1 * HORIZONTAL_SQUARE] = 220;
            stats[k + 1] = 220;
            stats[k] = 220;
            stats[k + 1 * HORIZONTAL_SQUARE + 1] = 220;
            stats[k - 1 * HORIZONTAL_SQUARE + 1] = 220;
            // printf("�idjasjdasdsad");

            NUMBER_OF_SHIP[1][1]--;
        }
    }

    if ((int) k / HORIZONTAL_SQUARE - 1 >= 0 && (int) k / HORIZONTAL_SQUARE + 1 < VERTICAL_SQUARE && k % HORIZONTAL_SQUARE - 1 >= 0) {
        if (stats[k - 1 * HORIZONTAL_SQUARE] == 2 && stats[k] == 2 && stats[k - 1] == 2 && stats[k + 1 * HORIZONTAL_SQUARE] == 2 &&
            stats[k + 1 * HORIZONTAL_SQUARE - 1] == 2 && stats[k - 1 * HORIZONTAL_SQUARE - 1] == 2) {
            stats[k - 1 * HORIZONTAL_SQUARE] = 220;
            stats[k + 1 * HORIZONTAL_SQUARE] = 220;
            stats[k - 1] = 220;
            stats[k] = 220;
            stats[k + 1 * HORIZONTAL_SQUARE - 1] = 220;
            stats[k - 1 * HORIZONTAL_SQUARE - 1] = 220;

            NUMBER_OF_SHIP[1][1]--;
        }
    }
}
