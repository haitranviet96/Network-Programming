#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Constants.h"
#include "Utils.h"

//// CHALLENGE
SDL_Texture *textureChallengeBG;

void loadChallengeTexture(){
    // create bg texture
    SDL_Surface *bgSurface = IMG_Load("assets/challenge_bg.png");
    if (bgSurface == NULL) {
        printf("IMG_Load Error: Error load assets/battle_bg.bmp");
        return;
    }
    textureChallengeBG = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
};

int renderListHost(bool *rendered) {
    SDL_Rect bgRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, textureChallengeBG, NULL, &bgRect);

}

void closeChallenge() {
    SDL_DestroyTexture(textureChallengeBG);
}