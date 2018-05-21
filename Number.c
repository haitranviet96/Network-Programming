#include <SDL.h>
#include "Constants.h"

void drawOrangeNumberTexture() {
    for (int i = 0; i < 10; i++) {
        char path[30];
        sprintf(path,"assets/digits/orange/%d.bmp",i);
        orangeNumber[i] = SDL_LoadBMP(path);
        orangeNumberTexture[i] = SDL_CreateTextureFromSurface(renderer, orangeNumber[i]);
        if (orangeNumberTexture[i] == NULL) {
            printf("SDL_LoadBMP Error: Error load %s",path);
            return;
        }
        SDL_FreeSurface(orangeNumber[i]);
    }
}

void destroyOrangeNumberTexture() {
    for (int i = 0; i < 10; i++) SDL_DestroyTexture(orangeNumberTexture[i]);
};
