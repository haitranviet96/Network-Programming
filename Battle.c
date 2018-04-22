#include <stdio.h>
#include <SDL.h>
#include "Constants.h"
#include "Draw.h"
#include "handlemouseEditor.h"

//// BATTLE
SDL_Surface *playBG;
SDL_Texture *textureBattleBG;

SDL_Renderer *renderer;

int layoutBattle(int x, int y, int *states, int *tableStatus) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 55, 55);

    SDL_Rect bgRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, textureBattleBG, NULL, &bgRect);

    draw_squares(x, y, tableStatus, gameTable, renderer);
}

void loadBattleTexture(SDL_Renderer *ren) {
    renderer = ren;

    playBG = SDL_LoadBMP("assets/battle_bg.bmp");
    if (playBG == NULL) {
        printf("SDL_LoadBMP Error: Error load assets/battle_bg.bmp");
        return;
    }
    textureBattleBG = SDL_CreateTextureFromSurface(renderer, playBG);
    SDL_FreeSurface(playBG);
}

void destroyBattleTexture(){
    SDL_DestroyTexture(textureBattleBG);
}
