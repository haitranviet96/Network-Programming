#include <stdio.h>
#include "Constants.h"

void ChangeSpecialboxMovingState4(int k, int *stats) {
    for (int i = 0; i < (VERTICAL_SQUARE * HORIZONTAL_SQUARE); i++) {
        if (stats[i] == 4)stats[i] = 0;
    }
    if (stats[k] == 0)stats[k] = 4;
}

void ChangeSpecialboxClickState40(int k, int *stats) {
    if (stats[k] == 4) {
        stats[k] = 40;
        NUMBER_OF_SHIP[1][3]--;
    }
}

int RemoveSpecialboxClickState444(int k, int *stats) {
    if (stats[k] == 40) {
        stats[k] = 0;
        return 1;
    }
    return 0;
}
