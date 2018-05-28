#include "States.h"
#include "ship.h"
#include "submarine.h"
#include "Cruiser.h"
#include "Constants.h"
#include "specialbox.h"

void handleMouseEditor(int x, int y, int *states, int *tableStatus) {
    if ((*states) == 1 && getSquare(x, y) >= 0) {
        ChangeShipMovingState1(getSquare(x, y), tableStatus);
        return;
    }

    if ((*states) == 10 && getSquare(x, y) >= 0) {
        if (NUMBER_OF_SHIP[1][0])
            ChangeShipClickState10(getSquare(x, y), tableStatus);
        (*states) = 0;
        return;
    }

    if ((*states) == 11 && getSquare(x, y) >= 0) {
        ChangeShipMovingState11(getSquare(x, y), tableStatus);
        return;
    }

    if ((*states) == 110 && getSquare(x, y) >= 0) {
        if (NUMBER_OF_SHIP[1][0])
            ChangeShipClickState110(getSquare(x, y), tableStatus);
        (*states) = 0;
        return;
    }
    if ((*states) == 2 && getSquare(x, y) >= 0) {
        ChangeSubmarineMovingState2(getSquare(x, y), tableStatus);
        return;
    }
    if ((*states) == 20 && getSquare(x, y) >= 0) {
        if (NUMBER_OF_SHIP[1][1] > 0)
            ChangeSubmarineClickState20(getSquare(x, y), tableStatus);
        (*states) = 0;

        return;
    }
    if ((*states) == 22 && getSquare(x, y) >= 0) {
        ChangeSubmarineMovingState22(getSquare(x, y), tableStatus);
        return;
    }
    if ((*states) == 220 && getSquare(x, y) >= 0) {

        if (NUMBER_OF_SHIP[1][1] > 0)
            ChangeSubmarineClickState220(getSquare(x, y), tableStatus);
        (*states) = 0;
        return;
    }

    if ((*states) == 3 && getSquare(x, y) >= 0) {
        ChangeCruiserMovingState3(getSquare(x, y), tableStatus);
        return;
    }
    if ((*states) == 30 && getSquare(x, y) >= 0) {
        if (NUMBER_OF_SHIP[1][2] > 0)
            ChangeCruiserClickState30(getSquare(x, y), tableStatus);
        (*states) = 0;

        return;
    }
    if ((*states) == 33 && getSquare(x, y) >= 0) {
        ChangeCruiserMovingState33(getSquare(x, y), tableStatus);
        return;
    }
    if ((*states) == 330 && getSquare(x, y) >= 0) {

        if (NUMBER_OF_SHIP[1][2] > 0)
            ChangeCruiserClickState330(getSquare(x, y), tableStatus);
        (*states) = 0;


        return;
    }
    if ((*states) == 4 && getSquare(x, y) >= 0) {
        ChangeSpecialboxMovingState4(getSquare(x, y), tableStatus);

        return;
    }
    if ((*states) == 40 && getSquare(x, y) >= 0) {
        if (NUMBER_OF_SHIP[1][3] > 0)
            ChangeSpecialboxClickState40(getSquare(x, y), tableStatus);

        (*states) = 0;
        return;
    }
    if ((*states) == -444 && getSquare(x, y) >= 0) {
        if (NUMBER_OF_SHIP[1][3] < NUMBER_OF_SHIP[0][3]) {
            if ((RemoveSpecialboxClickState444(getSquare(x, y), tableStatus)) > 0)
                NUMBER_OF_SHIP[1][3]++;
        }
        (*states) = 0;
    }


    for (int i = 0; i < HORIZONTAL_SQUARE * VERTICAL_SQUARE; i++) {
        if (tableStatus[i] == 1 || tableStatus[i] == 2 || tableStatus[i] == 3 || tableStatus[i] == 4) {
            tableStatus[i] = 0;
        }
    }


    if ((*states) == -11) {
        for (int i = 0; i < HORIZONTAL_SQUARE * VERTICAL_SQUARE; i++) {
            if (tableStatus[i] == 10 || tableStatus[i] == 110) {
                tableStatus[i] = 0;
            }
        }
    }
    if ((*states) == -22) {
        for (int i = 0; i < HORIZONTAL_SQUARE * VERTICAL_SQUARE; i++) {
            if (tableStatus[i] == 20 || tableStatus[i] == 220) {
                tableStatus[i] = 0;
            }
        }
    }
    if ((*states) == -33) {
        for (int i = 0; i < HORIZONTAL_SQUARE * VERTICAL_SQUARE; i++) {
            if (tableStatus[i] == 30 || tableStatus[i] == 330) {
                tableStatus[i] = 0;
            }
        }
    }
    if ((*states) == -44) {
        for (int i = 0; i < HORIZONTAL_SQUARE * VERTICAL_SQUARE; i++) {
            if (tableStatus[i] == 40) {
                tableStatus[i] = 0;
            }
        }
    }
    // return getEditorState(x,y);
}


