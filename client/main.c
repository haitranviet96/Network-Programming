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
#include "Utils.h"

int click;
int gameState = LOGIN_STATE;
char *inputText;
int opponentTableStatusTemp[HORIZONTAL_SQUARE * VERTICAL_SQUARE];
int playerTableStatusTemp[HORIZONTAL_SQUARE * VERTICAL_SQUARE];

int main(int argc, char **argv) {
    // text next to rerendered or not
    bool rendered = false;

    // login user text
    inputText = (char *) malloc(50);

    int x = 288;
    int y = 208;
    int j = 0;

    int playerTableStatus[HORIZONTAL_SQUARE * VERTICAL_SQUARE];
    int opponentTableStatus[HORIZONTAL_SQUARE * VERTICAL_SQUARE];
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

    ////DRAW NUMBER
    drawOrangeNumberTexture();
    // texturenum = SDL_CreateTextureFromSurface(renderer, numdigit);

    /////////STATS and SATES
    for (int i = 0; i < HORIZONTAL_SQUARE * VERTICAL_SQUARE; i++) {
        playerTableStatus[i] = 0;
        opponentTableStatus[i] = 0;
    }
    ////////////////////////
    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
    }

    //Open the font
    gFont = TTF_OpenFont("assets/fonts/OpenSans-Regular.ttf", 24);
    if (gFont == NULL) {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
    }

    if (gameState == LOGIN_STATE) {
        //Render the prompt
        if (!loadFromRenderedText(&gPromptTextTexture, "Enter your name:", textColor)) {
            printf("Failed to render prompt text!\n");
            printf("Failed to load media!\n");
        }
        //Enable text input
        SDL_StartTextInput();
    }

    loadEditorTexture();

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
    data = fopen("assets/data/map_opponent.txt", "r+");
    if (data == NULL) {
        printf("Error opening data files!\n");
        return -1;
    }
    /* Get the number of bytes */
    fseek(data, 0L, SEEK_END);
    long numbytes = ftell(data);

    /* reset the file position indicator to
    the beginning of the file */
    fseek(data, 0L, SEEK_SET);

    /* grab sufficient memory for the
    buffer to hold the text */
    char *buffer = (char *) calloc((size_t) numbytes, sizeof(char));

    /* memory error */
    if (buffer == NULL)
        return 1;

    /* copy all the text into the buffer */
    fread(buffer, sizeof(char), (size_t) numbytes, data);

    char *token;

    j = 0;

    /* get the first token */
    token = strtok(buffer, "\t\n");
    while (token != NULL) {
        opponentTableStatusTemp[j] = atoi(token);
        j++;
        token = strtok(NULL, "\t\n");
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

            default:
                break;
        }
        click = NONE_CLICK;

        if (gameState == LOGIN_STATE) {
            if (receiveUserName(&rendered)) {
                // continue
                gameState = EDITOR_STATE;
                closeLogin();
                loadEditorTexture();
            };
        }
        if (gameState == EDITOR_STATE) {
            scanEditor(&x, &y);
            if (layoutEditor(x, y, playerTableStatus)) {
                gameState = BATTLE_STATE;
                destroyEditorTexture();
                loadBattleTexture();
            }
        }
        if (gameState == BATTLE_STATE) {
            scanBattle(&x, &y);
            if (battle(x, y, playerTableStatus, opponentTableStatus)) {
                gameState = CHALLENGE_STATE;
                destroyBattleTexture();
            }
        }

        SDL_RenderPresent(renderer);
    }

    // Destroy texture
    destroyOrangeNumberTexture();

    // Destroy SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    //Free global font
    TTF_CloseFont(gFont);
    gFont = NULL;

    //Quit SDL subsystems
    TTF_Quit();

    SDL_Quit();

    return 0;
}
