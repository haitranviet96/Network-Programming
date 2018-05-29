#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Constants.h"
#include "Utils.h"

void scanChallenge(int *x, int *y) {
    switch (event.type) {
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(x, y);
            switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    printf("Left Mouse Clicked: %d-%d\n", *x, *y);
                    click = LEFT_CLICK;
                    break;
                default:
                    break;
            }
            break;
        default: break;
    }
}

//// CHALLENGE
SDL_Texture *textureChallengeBG;
SDL_Texture *boxTexture;
SDL_Texture *nameTexture[MAX_NUM_PLAYER];

int handleMouseChallenge(int x, int y){
    for (int i = 0; i < games_count; i++) {
        if(x < ( 40 + 240 * ((i+1) % 4) ) && x > ( 40 + 240 * (i % 4) ) &&
                y < 95 + 150 * (int) ((i / 4) + 1) && y > 95 + 150 * (int) (i / 4))
            return i + 1;
    }
    return 0;
};

void createNewName() {
    for(int i = 0 ; i < games_count ; i++) {
        SDL_Surface *surfaceName = TTF_RenderText_Blended_Wrapped(boldFont, games[i].name, textColor, 175);
        if (surfaceName != NULL) {
            //Create texture from surface pixels
            nameTexture[i] = SDL_CreateTextureFromSurface(renderer, surfaceName);
            if (nameTexture == NULL) {
                printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
            }
            //Get rid of old surface
            SDL_FreeSurface(surfaceName);
        } else {
            printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        }
    }
}

void loadChallengeTexture() {
    // create bg texture
    SDL_Surface *bgChallengeSurface = IMG_Load("assets/challenge_bg.png");
    if (bgChallengeSurface == NULL) {
        printf("IMG_Load Error: Error load assets/challenge_bg.png");
        return;
    }
    textureChallengeBG = SDL_CreateTextureFromSurface(renderer, bgChallengeSurface);
    SDL_FreeSurface(bgChallengeSurface);

    // create box texture
    SDL_Surface *boxSurface = IMG_Load("assets/challenge/box.png");
    if (boxSurface == NULL) {
        printf("IMG_Load Error: Error load assets/challenge/box.png");
        return;
    }
    boxTexture = SDL_CreateTextureFromSurface(renderer, boxSurface);
    SDL_FreeSurface(boxSurface);

    createNewName();
};

int renderListHost(int x, int y) {
    if(handleMouseChallenge(x,y) != 0 ){ // 1 - 12 if click, 0 if nothing happen
        return 1;
    }

    SDL_Rect bgRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, textureChallengeBG, NULL, &bgRect);

    for (int i = 0; i < MAX_NUM_PLAYER; i++) {
        peopleRect[i].x = 40 + 240 * (i % 4);
        peopleRect[i].y = 95 + 150 * (int) (i / 4);
        peopleRect[i].w = 225;
        peopleRect[i].h = 125;
        SDL_RenderCopy(renderer, boxTexture, NULL, &peopleRect[i]);
        if (i < games_count && strcmp(games[i].name,inputText) != 0) {
            render(nameTexture[i], 40 + 240 * (i % 4) + 25, 95 + 150 * (int) (i / 4) +25
                    , NULL, 0, NULL, SDL_FLIP_NONE);
        }
    }

    return 0;
}

void closeChallenge() {
    SDL_DestroyTexture(textureChallengeBG);
    SDL_DestroyTexture(boxTexture);
    for(int i = 0 ; i < games_count ; i++)
        SDL_DestroyTexture(nameTexture[i]);
}