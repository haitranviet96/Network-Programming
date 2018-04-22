#ifndef VARIABLE_FILE
#define VARIABLE_FILE

#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <SDL.h>
#include <SDL_ttf.h>

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

static const int WINDOW_WIDTH = 1024;
static const int WINDOW_HEIGHT = 576;

SDL_Surface *orangeNumber[10];
SDL_Texture *orangeNumberTexture[10];

int NUMBER_OF_SHIP[NUM_PLAYER][NUM_SHIP_KIND];

SDL_Window *window;
SDL_Renderer *renderer;

SDL_Rect gameTable[NUMBER_OF_SQUARE];

static struct timeval startTime, now;

TTF_Font* gFont;
SDL_Texture* gPromptTextTexture;

#endif
