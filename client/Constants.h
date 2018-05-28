#ifndef VARIABLE_FILE
#define VARIABLE_FILE

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>

#define NONE_CLICK (-1)
#define LEFT_CLICK 0
#define RIGHT_CLICK 1

#define LOGIN_STATE 0
#define CHALLENGE_STATE 1
#define EDITOR_STATE 2
#define BATTLE_STATE 3

#define NUM_SHIP_KIND 4
#define NUM_PLAYER 2

#define HORIZONTAL_SQUARE 17
#define VERTICAL_SQUARE 11
#define NUMBER_OF_SQUARE (11 * 17)

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 576

// variables
static bool quit = false;

static const SDL_Color textColor = {0xFF, 0xFF, 0xF2, 0xFF};

SDL_Surface *orangeNumber[10];
SDL_Texture *orangeNumberTexture[10];

int NUMBER_OF_SHIP[NUM_PLAYER][NUM_SHIP_KIND];

SDL_Window *window;
extern SDL_Renderer *renderer;
SDL_Event event;

extern int click;
extern int gameState;
extern char* inputText;
extern int opponentTableStatusTemp[HORIZONTAL_SQUARE * VERTICAL_SQUARE];
extern int playerTableStatusTemp[HORIZONTAL_SQUARE * VERTICAL_SQUARE];

extern int editState;
enum BATTLESTATE {
    PLAYER_TURN,
    PLAYER_HIT,
    OPPONENT_TURN,
};
extern enum BATTLESTATE currentBattleState;
extern SDL_Texture* explodeTexture;
extern SDL_Texture* missTexture;

SDL_Rect gameTable[NUMBER_OF_SQUARE];

static struct timeval startTime, now;

TTF_Font* gFont;
SDL_Texture* gPromptTextTexture;
SDL_Texture* gInputTextTexture;

#endif
