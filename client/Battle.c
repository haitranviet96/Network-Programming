#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Constants.h"
#include "Draw.h"
#include "States.h"
#include "Challenge.h"

enum BATTLESTATE currentBattleState = PLAYER_TURN;

//// BATTLE
SDL_Texture *textureBattleBG;
SDL_Texture *playerTurnInstrTexture;
SDL_Texture *opponentTurnInstrTexture;
SDL_Texture *explodeTexture;
SDL_Texture *missTexture;

void scanBattle(int *x, int *y) {
    switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    x--;
                    break;
                case SDLK_RIGHT:
                    x++;
                    break;
                case SDLK_UP:
                    y--;
                    break;
                case SDLK_DOWN:
                    y++;
                    break;
                default:
                    break;
            }
            break;

        case SDL_MOUSEMOTION:
            SDL_GetMouseState(x, y);
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(x, y);
            switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    printf("Left Mouse Clicked: %d-%d\tstates:%d\n", *x, *y, currentBattleState);
                    click = LEFT_CLICK;
                    break;
                case SDL_BUTTON_RIGHT:
                    click = RIGHT_CLICK;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    changeBattleStates(*x, *y);
}

void destroyBattleTexture() {
    SDL_DestroyTexture(textureBattleBG);
    SDL_DestroyTexture(opponentTurnInstrTexture);
    SDL_DestroyTexture(playerTurnInstrTexture);
    SDL_DestroyTexture(explodeTexture);
    SDL_DestroyTexture(missTexture);
}

void endGameMessage(const char *message) {
//    const SDL_MessageBoxButtonData buttons[] = {
//            {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Continue"},
//            {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "Quit"},
//    };
//    const SDL_MessageBoxData messageboxdata = {
//            SDL_MESSAGEBOX_INFORMATION, /* .flags */
//            window, /* .window */
//            "Game End", /* .title */
//            message, /* .message */
//            SDL_arraysize(buttons), /* .numbuttons */
//            buttons, /* .buttons */
//            NULL /* .colorScheme */
//    };
//    int buttonid;
//    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
//        SDL_Log("error displaying message box");
//    }
//    if (buttonid == -1) {
//        SDL_Log("no selection");
//    } else {
//        SDL_Log("selection was %s", buttons[buttonid].text);
//        if (!strcmp(buttons[buttonid].text, "Continue")) {
//            gameState = CHALLENGE_STATE;
//            destroyBattleTexture();
//            loadChallengeTexture();
//            click = NONE_CLICK;
//        } else {
//            quit = true;
//        };
//    }

    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Game End",message,window);
    quit = true;
}

int battle(int x, int y, int *playerTableStatus, int *opponentTableStatus) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 55, 55);

    SDL_Rect bgRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, textureBattleBG, NULL, &bgRect);

    int w, h;

    int fireStatus;
    int squareHit = getSquare(x, y);

    switch (currentBattleState) {
        case PLAYER_TURN:
            draw_squares(x, y, opponentTableStatus, gameTable);
            SDL_QueryTexture(playerTurnInstrTexture, NULL, NULL, &w, &h);
            // Render text textures
            render(playerTurnInstrTexture, WINDOW_WIDTH - w, 260, NULL, 0, NULL, SDL_FLIP_NONE);
            break;
        case OPPONENT_TURN:
            draw_squares(x, y, playerTableStatus, gameTable);
            SDL_QueryTexture(opponentTurnInstrTexture, NULL, NULL, &w, &h);
            // Render text textures
            render(opponentTurnInstrTexture, WINDOW_WIDTH - w, 260, NULL, 0, NULL, SDL_FLIP_NONE);
            break;
        case PLAYER_HIT:
            // GO-TO send to server the coordinate of hit
            target.column = squareHit % 17;
            target.row = squareHit / 17;
            char message[100] = "";
            fireStatus = sendFire(sfd, message);

            switch (fireStatus) {
                case 1: // Hit
                    players[0].numHits++;
                    opponentTableStatus[squareHit] = 'h';
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Hit !","You have hit opponent's ship !", window);
                    currentBattleState = PLAYER_TURN;
                    break;
                case 0: // Miss
                    players[0].numMisses++;
                    opponentTableStatus[squareHit] = 'm';
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED, "Miss !",
                                             "You have missed !", window);
                    currentBattleState = OPPONENT_TURN;

                    target.column = -1;
                    target.row = -1;

                    SDL_Thread *joinThread;
                    joinThread = SDL_CreateThread(waitFire, "hitThread", NULL);
                    if (NULL == joinThread) {
                        printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
                    }
                    break;
                case 2: // End
                    currentBattleState = GAME_END;
                    sprintf(message + strlen(message), "You won!");
                    endGameMessage(message);
                    break;
                default:
                    break;
            }

//            if (playerTableStatusTemp[squareHit] != 0) {
//                opponentTableStatus[squareHit] = 'h';
//                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Hit !",
//                                         "You have hit opponent's ship !", NULL);
//                currentBattleState = PLAYER_TURN;
//            } else {
//                opponentTableStatus[squareHit] = 'm';
//                SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED, "Miss !",
//                                         "You have missed !", NULL);
//                currentBattleState = OPPONENT_TURN;
//            }
            draw_squares(x, y, playerTableStatus, gameTable);
            break;
        default:
            break;
    }

}

void loadBattleTexture() {
    // create bg texture
    SDL_Surface *bgSurface = IMG_Load("assets/battle_bg.bmp");
    if (bgSurface == NULL) {
        printf("SDL_LoadBMP Error: Error load assets/battle_bg.bmp");
        return;
    }
    textureBattleBG = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);

    // create explode texture
    SDL_Surface *explodeSurface = IMG_Load("assets/explode.png");
    if (explodeSurface == NULL) {
        printf("SDL_LoadBMP Error: Error load assets/explode.png");
        return;
    }
    explodeTexture = SDL_CreateTextureFromSurface(renderer, explodeSurface);
    SDL_FreeSurface(explodeSurface);

    // create explode texture
    SDL_Surface *missSurface = IMG_Load("assets/miss.png");
    if (missSurface == NULL) {
        printf("SDL_LoadBMP Error: Error load assets/miss.png");
        return;
    }
    missTexture = SDL_CreateTextureFromSurface(renderer, missSurface);
    SDL_FreeSurface(missSurface);

    // create instruct texture
    SDL_Surface *instructionSurface = TTF_RenderText_Blended_Wrapped(regularFont,
                                                                     "Your turn. Please choose a coordinate to shoot.",
                                                                     textColor, 140);
    if (instructionSurface != NULL) {
        //Create texture from surface pixels
        playerTurnInstrTexture = SDL_CreateTextureFromSurface(renderer, instructionSurface);
        if (playerTurnInstrTexture == NULL) {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        //Get rid of old surface
        SDL_FreeSurface(instructionSurface);
    } else {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }

    instructionSurface = TTF_RenderText_Blended_Wrapped(regularFont,
                                                        "Opponent's turn. Please wait ...",
                                                        textColor, 140);
    if (instructionSurface != NULL) {
        //Create texture from surface pixels
        opponentTurnInstrTexture = SDL_CreateTextureFromSurface(renderer, instructionSurface);
        if (opponentTurnInstrTexture == NULL) {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        //Get rid of old surface
        SDL_FreeSurface(instructionSurface);
    } else {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
}

