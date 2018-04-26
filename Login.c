#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Constants.h"

int loadFromRenderedText(SDL_Texture **texture, char *text, SDL_Color color) {
    SDL_DestroyTexture(*texture);
    if (text != NULL && text[0] != (char)'\0') {
        //Render text surface
        SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, text, color);
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

int loadMedia() {
    //Loading success flag
    int success = 1;

    //Open the font
    gFont = TTF_OpenFont("assets/fonts/OpenSans-Regular.ttf", 36);
    if (gFont == NULL) {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        success = 0;
    } else {
        //Render the prompt
        SDL_Color textColor = {0xFF, 0xFF, 0xFF, 0xFF};
        if (!loadFromRenderedText(&gPromptTextTexture, "Enter your name:", textColor)) {
            printf("Failed to render prompt text!\n");
            success = 0;
        }
    }

    return success;
}

void closeLogin() {
    //Disable text input
    SDL_StopTextInput();

    //Free loaded images
    free(gPromptTextTexture);
    free(gInputTextTexture);

    //Free global font
    TTF_CloseFont(gFont);
    gFont = NULL;

    //Quit SDL subsystems
    TTF_Quit();
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