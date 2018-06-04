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

int hostOrJoin();

int joinLoop(void *d);

int hostLoop(void *d);

int sfd_s, sfd_l; // s: server, l: listening
int mode;

int main(int argc, char **argv) {
    // client server connect
    opponent_t connected;
    SDL_Thread *joinThread;
    SDL_Thread *hostThread;

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
                mode = hostOrJoin(); // 0 = host, 1 = join

                // continue
                if (sign_in(inputText, "127.0.0.1", &sfd_s, &sfd_l, mode)) {
                    closeLogin();

                    sleep(1);
                    gameState = CHALLENGE_STATE;
                    rendered = false;

                    // Fetch and select a game
                    games_count = get_games(sfd_s, games);
                    printf("%d games received.\n", games_count);
                    print_games(games, games_count);
                    if (!mode) { // Host  player
//                        int threadReturnValue;
                        hostThread = SDL_CreateThread(hostLoop, "hostThread", (void *) &connected);
                        if (NULL == hostThread) {
                            printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
                        }
//                        else {
//                            SDL_WaitThread(thread, &threadReturnValue);
//                            printf("\nThread returned value: %d", threadReturnValue);
//                        }
                        printf("Waiting for an opponent to connect...\n");
                    }
                    loadChallengeTexture();
                    loadEditorTexture();
                }
            };
        }
        if (gameState == CHALLENGE_STATE) {
            scanChallenge(&x, &y);
            if (renderListHost(x, y)) {

            } else if (currentChallengeState == CLICK_REFRESH_BUTTON) {
                games_count = get_games(sfd_s, games);
            } else if (currentChallengeState == WAITING_RESPOND) {
                if (mode) {
                    if (joinThread == NULL) {
//                    int threadReturnValue;
                        joinThread = SDL_CreateThread(joinLoop, "waitThread", (void *) &connected);
                        if (NULL == joinThread) {
                            printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
                        }
//                    else {
//                        SDL_WaitThread(thread, &threadReturnValue);
//                        printf("\nThread returned value: %d", threadReturnValue);
//                    }
                    }
                }
            }
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

int hostOrJoin() {
    const SDL_MessageBoxButtonData buttons[] = {
            {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 0, "Host"},
            {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 1, "Join"},
    };
    const SDL_MessageBoxData messageboxdata = {
            SDL_MESSAGEBOX_INFORMATION, /* .flags */
            NULL, /* .window */
            "Host or Join", /* .title */
            "Please choose to host or join a game", /* .message */
            SDL_arraysize(buttons), /* .numbuttons */
            buttons, /* .buttons */
            NULL /* .colorScheme */
    };
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
        SDL_Log("error displaying message box");
    }
    if (buttonid == -1) {
        SDL_Log("no selection");
    } else {
        SDL_Log("selection was %s", buttons[buttonid].text);
    }

    return strcmp(buttons[buttonid].text, "Host");
}

int joinLoop(void *d) {
    opponent_t *connected = (opponent_t *) d;
    connect_player(games[opponentId], connected, sfd_s);
    send_name(connected->sfd, inputText);
    printf("Waiting for the host to start the game...\n");
    wait_start(connected->sfd);
    printf("Game starts!\n");

    // continue to editor state
    closeChallenge();
    gameState = EDITOR_STATE;
    click = NONE_CLICK;

    return 0;
}

int hostLoop(void *d) {
    opponent_t *connected = (opponent_t *) d;
    accept_player(sfd_l, connected);
    wait_name(connected);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Notification", "You have a Challenger", NULL);

    send_start(sfd_s, *connected);
    printf("Game starts!\n");

    // continue to editor state
    closeChallenge();
    click = NONE_CLICK;
    gameState = EDITOR_STATE;

    return 0;
}