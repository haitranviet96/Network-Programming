#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Constants.h"
#include "Utils.h"

void scanChallenge(int *x, int *y) {
    switch (event.type) {
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(x, y);
            click = NONE_CLICK;
            break;
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
        default:
            break;
    }
}

enum CHALLENGESTATE currentChallengeState = CHALLENGING;

SDL_Rect peopleRect[MAX_NUM_PLAYER];
//// CHALLENGE
SDL_Texture *challengeBgTexture;
SDL_Texture *boxTexture;
SDL_Texture *refreshBtnTexture;
SDL_Texture *waitingTextTexture;
SDL_Texture *nameTexture[MAX_NUM_PLAYER];
int opponentId;

void handleMouseChallenge(int x, int y) {

    if (currentChallengeState == WAITING_RESPOND)
        return;
    currentChallengeState = CHALLENGING;
    if (x > 800 && x < 1000 && y > 28 && y < 76) {
        if (click == NONE_CLICK) currentChallengeState = HOVER_REFRESH_BUTTON;
        else if (click == LEFT_CLICK) currentChallengeState = CLICK_REFRESH_BUTTON;
    }
    for (int i = 0; i < games_count; i++) {
        if (x < (40 + 240 * ((i + 1) % 4)) && x > (40 + 240 * (i % 4)) &&
            y < 95 + 150 * (int) ((i / 4) + 1) && y > 95 + 150 * (int) (i / 4)) {
            if (click == LEFT_CLICK) {
                opponentId = i;
                currentChallengeState = WAITING_RESPOND;
            }
        }
    }
};

void createNewName() {
    for (int i = 0; i < games_count; i++) {
        SDL_Surface *surfaceName = TTF_RenderText_Blended_Wrapped(boldFont, games[i].name, textColor, 175);
        if (surfaceName != NULL) {
            if (nameTexture[i] != NULL) SDL_DestroyTexture(nameTexture[i]);
            //Create texture from surface pixels
            nameTexture[i] = SDL_CreateTextureFromSurface(renderer, surfaceName);
            if (nameTexture[i] == NULL) {
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
    challengeBgTexture = SDL_CreateTextureFromSurface(renderer, bgChallengeSurface);
    SDL_FreeSurface(bgChallengeSurface);

    // create box texture
    SDL_Surface *boxSurface = IMG_Load("assets/challenge/box.png");
    if (boxSurface == NULL) {
        printf("IMG_Load Error: Error load assets/challenge/box.png");
        return;
    }
    boxTexture = SDL_CreateTextureFromSurface(renderer, boxSurface);
    SDL_FreeSurface(boxSurface);

    // create refresh button texture
    SDL_Surface *refreshBtnSurface = IMG_Load("assets/challenge/refresh_btn_pr.png");
    if (refreshBtnSurface == NULL) {
        printf("IMG_Load Error: Error load assets/challenge/refresh_btn_pr.png");
        return;
    }
    refreshBtnTexture = SDL_CreateTextureFromSurface(renderer, refreshBtnSurface);
    SDL_FreeSurface(refreshBtnSurface);

    SDL_Surface *surfaceWait = TTF_RenderText_Blended_Wrapped(regularFont, "Waiting for respond...", textColor, 175);
    if (surfaceWait != NULL) {
        if (waitingTextTexture != NULL) SDL_DestroyTexture(waitingTextTexture);
        //Create texture from surface pixels
        waitingTextTexture = SDL_CreateTextureFromSurface(renderer, surfaceWait);
        if (waitingTextTexture == NULL) {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        //Get rid of old surface
        SDL_FreeSurface(surfaceWait);
    } else {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }

    createNewName();
};

int renderListHost(int x, int y) {
    handleMouseChallenge(x, y);

    createNewName();

    SDL_Rect bgRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, challengeBgTexture, NULL, &bgRect);

    for (int i = 0; i < MAX_NUM_PLAYER; i++) {
        peopleRect[i].x = 40 + 240 * (i % 4);
        peopleRect[i].y = 95 + 150 * (int) (i / 4);
        peopleRect[i].w = 225;
        peopleRect[i].h = 125;
        SDL_RenderCopy(renderer, boxTexture, NULL, &peopleRect[i]);
        if (i < games_count) {
            render(nameTexture[i], 40 + 240 * (i % 4) + 25, 95 + 150 * (int) (i / 4) + 10, NULL, 0, NULL,
                   SDL_FLIP_NONE);
        }
    }

    if (currentChallengeState == HOVER_REFRESH_BUTTON || currentChallengeState == CLICK_REFRESH_BUTTON) {
        SDL_Rect rectRefreshBtn = {795, 25, 197, 48};
        SDL_RenderCopy(renderer, refreshBtnTexture, NULL, &rectRefreshBtn);
    }

    if (currentChallengeState == WAITING_RESPOND)
        render(waitingTextTexture, 40 + 240 * (opponentId % 4) + 25,
               95 + 150 * (opponentId / 4) + 50, NULL, 0, NULL, SDL_FLIP_NONE);

    return 0;
}

void closeChallenge() {
    if (challengeBgTexture != NULL) SDL_DestroyTexture(challengeBgTexture);
    if (boxTexture != NULL) SDL_DestroyTexture(boxTexture);
    for (int i = 0; i < games_count; i++)
        SDL_DestroyTexture(nameTexture[i]);
}