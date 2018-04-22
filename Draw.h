#ifndef DRAW_FILE
#define DRAW_FILE

#include <SDL.h>
#include "Constants.h"
#include <stdbool.h>
#include "Utils.h"

void draw_random_points(int nr_points, bool randomizeColor, SDL_Renderer *renderer);

void draw_random_lines(int nr_lines, bool randomizeColor, SDL_Renderer *renderer);

void draw_squares(int x, int y, int *stats, SDL_Rect *rect, SDL_Renderer *renderer);

void draw_number(int x, int y, SDL_Texture *texture, SDL_Renderer *renderer);

#endif