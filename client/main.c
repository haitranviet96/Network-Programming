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

bool quit = false;

// battleship game
Coordinate target;                         // x, y value of a target
Stats players[2] = {{0, 0}, {0, 0}};
int sunkShip[2][NUM_OF_SHIPS] = {{4, 4, 4, 6, 6, 2, 2, 1},
                                 {4, 4, 4, 6, 6, 2, 2, 1}};  /* tracks parts of the ship destroyed */
WaterCraft ship[NUM_OF_SHIPS] = {{'l', 4, "Long ship"},
                                 {'l', 4, "Long ship"},
                                 {'l', 4, "Long ship"},
                                 {'s', 6, "Submarine"},
                                 {'s', 6, "Submarine"},
                                 {'c', 2, "Cruiser"},
                                 {'c', 2, "Cruiser"},
                                 {'h', 1, "Headquater"}};

int click;
int gameState = LOGIN_STATE;
char *inputText;
int opponentTableStatusTemp[HORIZONTAL_SQUARE * VERTICAL_SQUARE];

int playerTableStatus[HORIZONTAL_SQUARE * VERTICAL_SQUARE];
int opponentTableStatus[HORIZONTAL_SQUARE * VERTICAL_SQUARE];

int games_count;
game_t games[MAX_GAMES];

int hostOrJoin();

int hostLoop(void *d) ;

int joinLoop(void *d) ;

int waitFire(void *d) ;

int sfd;//!< Dialog socket file descriptor between players
int sfd_s, sfd_l; // s: server, l: listening
int mode;

int main(int argc, char **argv) {
    // client server connect
    opponent_t connected;
    SDL_Thread *joinThread = NULL;
    SDL_Thread *hostThread = NULL;
    target.column = -1;
    target.row = -1;

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
            sfd = connected.sfd; // Make the created socket file descriptor global
            scanEditor(&x, &y);
            if (layoutEditor(x, y, playerTableStatus)) {
                gameState = BATTLE_STATE;
                destroyEditorTexture();
                loadBattleTexture();
                if (mode) { // join player
                    currentBattleState = OPPONENT_TURN;
                    target.row = -1;
                    target.column = -1;

                    joinThread = SDL_CreateThread(waitFire, "hitThread", (void *) &connected);
                    if (NULL == joinThread) {
                        printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
                    }
                } else { // host player
                    currentBattleState = PLAYER_TURN;
                }
            }
        }
        if (gameState == BATTLE_STATE) {
            scanBattle(&x, &y);
            if (currentBattleState == OPPONENT_TURN) {
                if (target.row >= 0 && target.column >= 0) { // receive Fire and return hit or miss
                    char message[50];
                    char cmd[10];

                    if (checkShot(playerOneGameBoard, target)) { // HIT
                        players[1].numHits++;
                        if (checkSunkShip(sunkShip, 0, playerOneGameBoard[target.row][target.column].symbol,message)) {
                            //Check winner
                            if (isWinner(players, sunkShip, 1)) {
                                printf("\n> Player %s wins!\n", games[opponentId].name);
                                sprintf(message,"> Player %s wins!", games[opponentId].name);
                                currentBattleState = GAME_END;
                                sprintf(cmd, "END");
                            } else sprintf(cmd, "SINK");
                        }

                        if(currentBattleState != GAME_END) {
                            updateGameBoard(playerOneGameBoard, target);
                            currentBattleState = OPPONENT_TURN;
                            target.column = -1;
                            target.row = -1;
                            joinThread = SDL_CreateThread(waitFire, "hitThread", (void *) &connected);
                            if (NULL == joinThread) {
                                printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
                            }
                            sprintf(cmd, "HIT");
                            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Hit!", "You have been hit! Your opponent can fire again :(", NULL);
                        }
                    } else { // MISS
                        sprintf(cmd, "MISS");
                        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Miss!", "Your turn to revenge!", NULL);
                        currentBattleState = PLAYER_TURN;
                    };
                    returnFire(sfd,cmd,message);
                }
            }
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

int waitFire(void *d) {
    char buff[MAX_REQ];
    printf("Waiting for the fire of opponent...\n");
    check(recv(sfd, buff, MAX_REQ, 0), "Error receiveing");
    sscanf(buff, "FIRE %d %d", &(target.column), &(target.row));
}