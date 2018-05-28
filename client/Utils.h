
#pragma once

// Generate a random number from nr_min to nr_max
int randomNumber(int nr_min, int nr_max);

// Generate a random color from 0 to 255
int randomColor();

int loadFromRenderedText(SDL_Texture** texture, char* text, SDL_Color color);

void
render(SDL_Texture *texture, int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip);