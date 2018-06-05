#ifndef VARIABLE_FILE
#define VARIABLE_FILE

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include "overall_net.h"
#include "battleship.h"

#define NONE_CLICK (-1)
#define LEFT_CLICK 0
#define RIGHT_CLICK 1

#define LOGIN_STATE 0
#define CHALLENGE_STATE 1
#define EDITOR_STATE 2
#define BATTLE_STATE 3

#define NUM_SHIP_KIND 4
#define NUM_PLAYER 2

#define MAX_NUM_PLAYER 12

#define HORIZONTAL_SQUARE 17
#define VERTICAL_SQUARE 11
#define NUMBER_OF_SQUARE (11 * 17)

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 576

// variables
extern bool quit;

static const SDL_Color textColor = {0x00, 0x00, 0x00, 0xFF};

SDL_Surface *orangeNumber[10];
SDL_Texture *orangeNumberTexture[10];

int NUMBER_OF_SHIP[NUM_PLAYER][NUM_SHIP_KIND];

SDL_Window *window;
extern SDL_Renderer *renderer;
SDL_Event event;

extern int click;
extern int gameState;
extern char* inputText;
extern int playerTableStatusTemp[HORIZONTAL_SQUARE * VERTICAL_SQUARE];
extern int playerTableStatus[HORIZONTAL_SQUARE * VERTICAL_SQUARE];
extern int opponentTableStatus[HORIZONTAL_SQUARE * VERTICAL_SQUARE];

extern int editState;
enum BATTLESTATE {
    PLAYER_TURN,
    PLAYER_HIT,
    OPPONENT_TURN,
    GAME_END,
};
extern enum BATTLESTATE currentBattleState;
extern SDL_Texture* explodeTexture;
extern SDL_Texture* missTexture;

// state of challenge screen
enum CHALLENGESTATE {
    HOVER_REFRESH_BUTTON,  // hovering refresh button
    CLICK_REFRESH_BUTTON,  // click refresh button
    WAITING_RESPOND,       // waiting for respond of opponent
    CHALLENGING,
    CHALLENGED,
};
extern enum CHALLENGESTATE currentChallengeState;
extern int opponentId;
extern int mode; // host = 0, join = 1
extern int sfd;//!< Dialog socket file descriptor between players
extern int sfd_s, sfd_l; // s: server, l: listening

// battleship game
Cell playerOneGameBoard[VERTICAL_SQUARE][HORIZONTAL_SQUARE];       //P1 game board
extern Coordinate target;                         // x, y value of a target
extern int sunkShip[2][NUM_OF_SHIPS];  /* tracks parts of the ship destroyed */
extern WaterCraft ship[NUM_OF_SHIPS];
extern Stats players[2];        //initialize stats for 2 players

SDL_Rect gameTable[NUMBER_OF_SQUARE];
extern game_t games[MAX_GAMES];
extern int games_count;

static struct timeval startTime, now;

TTF_Font* boldFont;
TTF_Font* regularFont;
SDL_Texture* gInputTextTexture;

// thread
extern int hostOrJoin();

extern int hostLoop(void *d) ;

extern int joinLoop(void *d) ;

extern int waitFire(void *d) ;

#endif
