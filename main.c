#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>

#include "States.h"
#include "Number.h"
#include "Constants.h"
#include "Editor.h"
#include "Battle.h"
#include "Login.h"

int click = NONE_CLICK;
int gameState = LOGIN_STATE;

int main(int argc, char **argv) {
    // variables
    bool quit = false;
    SDL_Event event;
    int x = 288;
    int y = 208;
    int j = 0;

    int tableStatus[HORIZONTAL_SQUARE * VERTICAL_SQUARE];
    int states;
    FILE *data;
    char c;

    char text[20];

    // init SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error : %s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("Battle Ship", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("SDL_CreateWindow Error : %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return 1;
    }

    // Draw layoutEditor texture
    loadEditorTexture(renderer);

    ////DRAW NUMBER
    drawOrangeNumberTexture();
    // texturenum = SDL_CreateTextureFromSurface(renderer, numdigit);

    // load font
    loadMedia();

    /////////STATS and SATES
    for (int i = 0; i < HORIZONTAL_SQUARE * VERTICAL_SQUARE; i++) {
        tableStatus[i] = 0;
    }
    states = 0;
    ////////////////////////

    ////////DATA
    data = fopen("assets/data/data.txt", "r+");
    if (data == NULL) {
        printf("Error opening data files!\n");
        return -1;
    }
    for (j = 0; j < 4; j++) {
        c = (char) fgetc(data);
        NUMBER_OF_SHIP[0][j] = -48 + (int) c;
        NUMBER_OF_SHIP[1][j] = NUMBER_OF_SHIP[0][j];
    }
    ////////////////////////

    gettimeofday(&startTime, NULL);
    while (!quit) {
        SDL_WaitEvent(&event);

        gettimeofday(&now, NULL);
        switch (event.type) {

            case SDL_QUIT:
                quit = true;
                break;

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
                SDL_GetMouseState(&x, &y);
//                if (now.tv_sec - startTime.tv_sec > 1) {
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&x, &y);
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        printf("Left Mouse Clicked: %d-%d\tstates:%d\n", x, y, states);
                        click = LEFT_CLICK;
                        // printf("%d\n",getSquare(x,y));
                        break;
                    case SDL_BUTTON_RIGHT:
                        click = RIGHT_CLICK;
                        break;
                    default:
                        //    printf("Unknown Mouse Clicked: %d-%d",x,y);
                        break;
                }
                break;
                gettimeofday(&now, NULL);
//                }
//                break;
            default:
                break;
        }
        // if(click <0&&states <=0 )printf("L�NNONONO");
        changeStates(x, y, &states, click);
        click = NONE_CLICK;

        if (gameState == LOGIN_STATE) {

        }
        if (gameState == EDITOR_STATE) {
            if (layoutEditor(x, y, &states, tableStatus)) {
                gameState = BATTLE_STATE;
                destroyEditorTexture();
                loadBattleTexture(renderer);
            }
        }
        if (gameState == BATTLE_STATE) {
            if (layoutBattle(x, y, &states, tableStatus)) {
                destroyBattleTexture();
                gameState = CHALLENGE_STATE;
            }
        }

        SDL_RenderPresent(renderer);
    }

    // Destroy texture
    destroyOrangeNumberTexture();

    // Destroy SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
