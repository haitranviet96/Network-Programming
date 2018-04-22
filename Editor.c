#include <stdio.h>
#include <SDL.h>
#include "Constants.h"
#include "Draw.h"
#include "handlemouseEditor.h"

////EDITOR
SDL_Surface *playBG;
SDL_Texture *textureEditBG;
SDL_Surface *refresh;
SDL_Texture *refreshBtnTexture;
SDL_Surface *next;
SDL_Texture *nextBtnTexture;

SDL_Renderer *renderer;

int layoutEditor(int x, int y, int *states, int *tableStatus) {
    handleMouseEditor(x, y, states, tableStatus);

    SDL_SetRenderDrawColor(renderer, 255, 255, 55, 55);

    SDL_Rect bgRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, textureEditBG, NULL, &bgRect);

    draw_squares(x, y, tableStatus, gameTable, renderer);

    // draw number of ship
    draw_number(911, 260, orangeNumberTexture[NUMBER_OF_SHIP[1][0]], renderer);
    draw_number(946, 260, orangeNumberTexture[NUMBER_OF_SHIP[1][1]], renderer);
    draw_number(980, 260, orangeNumberTexture[NUMBER_OF_SHIP[1][2]], renderer);
    draw_number(959, 398, orangeNumberTexture[NUMBER_OF_SHIP[1][3]], renderer);

    if ((*states) == -1 || (*states) == -11) {
        if ((*states) == -11) {
            NUMBER_OF_SHIP[1][0] = NUMBER_OF_SHIP[0][0];
            (*states) = 0;
        }
        SDL_Rect rectRefreshBtn = {904, 305, 27, 32};
        SDL_RenderCopy(renderer, refreshBtnTexture, NULL, &rectRefreshBtn);
    }

    if ((*states) == -2 || (*states) == -22) {

        if ((*states) == -22) {
            NUMBER_OF_SHIP[1][1] = NUMBER_OF_SHIP[0][1];
            (*states) = 0;

        }
        SDL_Rect rectRefreshBtn = {938, 305, 27, 32};
        SDL_RenderCopy(renderer, refreshBtnTexture, NULL, &rectRefreshBtn);
    }

    if ((*states) == -3 || (*states) == -33) {

        if ((*states) == -33) {
            NUMBER_OF_SHIP[1][2] = NUMBER_OF_SHIP[0][2];
            (*states) = 0;

        }
        SDL_Rect rectRefreshBtn = {972, 305, 27, 32};
        SDL_RenderCopy(renderer, refreshBtnTexture, NULL, &rectRefreshBtn);
    }

    if ((*states) == -4 || (*states) == -44) {
        if ((*states) == -44) {
            NUMBER_OF_SHIP[1][3] = NUMBER_OF_SHIP[0][3];
            (*states) = 0;

        }
        SDL_Rect rectRefreshBtn = {986, 394, 27, 32};
        SDL_RenderCopy(renderer, refreshBtnTexture, NULL, &rectRefreshBtn);

    }

    if (((*states) == -5 || (*states) == -55) && NUMBER_OF_SHIP[1][0] == 0
        && NUMBER_OF_SHIP[1][1] == 0 && NUMBER_OF_SHIP[1][2] == 0 && NUMBER_OF_SHIP[1][3] == 0) {
        SDL_Rect rectRefreshBtn = {883, 504, 136, 49};
        SDL_RenderCopy(renderer, nextBtnTexture, NULL, &rectRefreshBtn);
        if ((*states) == -55) {
            //printf("sakdasdasd");
            FILE *file;
            file = fopen("assets/data/map.txt", "w+");
            for (int i = 0; i < VERTICAL_SQUARE * HORIZONTAL_SQUARE; i++) {
                if (i % 17 == 16)fprintf(file, "%d\t\n", tableStatus[i]);
                else
                    fprintf(file, "%d\t", tableStatus[i]);
            }
            fclose(file);
            return 1;
        }
    }
    return 0;
}

void loadEditorTexture(SDL_Renderer *ren) {
    renderer = ren;

    playBG = SDL_LoadBMP("assets/editor_bg.bmp");
    if (playBG == NULL) {
        printf("SDL_LoadBMP Error: Error load assets/editor_bg.bmp");
        return;
    }
    textureEditBG = SDL_CreateTextureFromSurface(renderer, playBG);
    SDL_FreeSurface(playBG);

    refresh = SDL_LoadBMP("assets/Editor/refresh.bmp");
    if (refresh == NULL) {
        printf("SDL_LoadBMP Error: Error load assets/Editor/refresh.bmp");
        return;
    }
    refreshBtnTexture = SDL_CreateTextureFromSurface(renderer, refresh);
    SDL_FreeSurface(refresh);

    next = SDL_LoadBMP("assets/Editor/next.bmp");
    if (next == NULL) {
        printf("SDL_LoadBMP Error: Error load assets/Editor/next.bmp");
        return;
    }
    nextBtnTexture = SDL_CreateTextureFromSurface(renderer, next);
    SDL_FreeSurface(next);
}

void destroyEditorTexture(){
    SDL_DestroyTexture(textureEditBG);
    SDL_DestroyTexture(refreshBtnTexture);
    SDL_DestroyTexture(nextBtnTexture);
}
