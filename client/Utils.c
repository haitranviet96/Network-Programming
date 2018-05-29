#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <SDL_system.h>
#include <SDL_ttf.h>
#include "Constants.h"

// Generate a random number from nr_min to nr_max
int randomNumber(int nr_min, int nr_max)
{
    // Initialize the random number generator with the current time
    // be sure that it is initialized only once
    static bool initialized = false;
    if(!initialized)
    {
        initialized = true;
        srand(time(NULL));
    }
    // generate the random number
    return rand() % nr_max + nr_min;
}

// Generate a random color from 0 to 255
int randomColor()
{
    return randomNumber(0, 255);
}

int loadFromRenderedText(SDL_Texture **texture, char *text, SDL_Color color) {
    SDL_DestroyTexture(*texture);
    if (text != NULL && text[0] != (char)'\0') {
        //Render text surface
        SDL_Surface *textSurface = TTF_RenderText_Solid(boldFont, text, color);
        if (textSurface != NULL) {
            //Create texture from surface pixels
            (*texture) = SDL_CreateTextureFromSurface(renderer, textSurface);
            if ((*texture) == NULL) {
                printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
            } else {
                //Get image dimensions
                textSurface->w;
                textSurface->h;
            }

            //Get rid of old surface
            SDL_FreeSurface(textSurface);
        } else {
            printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        }
    }

    //Return success
    return (*texture) != NULL;
}

void
render(SDL_Texture *texture, int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip) {
    int w, h;
    SDL_QueryTexture(texture, NULL, NULL, &w, &h);
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, w, h};

    //Set clip rendering dimensions
    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx(renderer, texture, clip, &renderQuad, angle, center, flip);
}