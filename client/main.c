#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <zconf.h>

#include "States.h"
#include "Number.h"
#include "Constants.h"
#include "Editor.h"
#include "Battle.h"
#include "Login.h"
#include "Utils.h"
#include "overall_net.h"
#include "Challenge.h"

int click;
int gameState = LOGIN_STATE;
char *inputText;
int opponentTableStatusTemp[HORIZONTAL_SQUARE * VERTICAL_SQUARE];

int playerTableStatus[HORIZONTAL_SQUARE * VERTICAL_SQUARE];
int opponentTableStatus[HORIZONTAL_SQUARE * VERTICAL_SQUARE];

int games_count;
game_t games[MAX_GAMES];

int main(int argc, char **argv) {
    // client server connect
    int sfd_s, sfd_l; // s: server, l: listening
    opponent_t connected;

    // rendered or not
    bool rendered = false;

    // login user text
    inputText = (char *) malloc(50);

    int x = 0;
    int y = 0;
    int j = 0;

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
    boldFont = TTF_OpenFont("assets/fonts/OpenSans-Bold.ttf", 32);
    if (boldFont == NULL) {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
    }

    regularFont = TTF_OpenFont("assets/fonts/OpenSans-Regular.ttf", 24);
    if (regularFont == NULL) {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
    }

    if (gameState == LOGIN_STATE) {
        //Enable text input
        SDL_StartTextInput();
    }

    loadLoginTexture();

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
                if(sign_in(inputText,"127.0.0.1",&sfd_s, &sfd_l)) {
                    closeLogin();

                    sleep(1);
                    gameState = CHALLENGE_STATE;
                    rendered = false;

                    // Fetch and select a game
                    games_count = get_games(sfd_s, games);
                    printf("%d games received.\n", games_count);
                    print_games(games, games_count);

                    loadChallengeTexture();
                }
            };
        }
        if (gameState == CHALLENGE_STATE) {
            scanChallenge(&x, &y);
            int state = renderListHost(x,y);
            if (state == 1) {
                // continue to editor state

                gameState = EDITOR_STATE;
                closeChallenge();
                loadEditorTexture();
                rendered = false;
                click = NONE_CLICK;
            }else if( state == -2 ){
                games_count = get_games(sfd_s, games);
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
    TTF_CloseFont(boldFont);
    boldFont = NULL;

    //Quit SDL subsystems
    TTF_Quit();

    SDL_Quit();

    return 0;
}
