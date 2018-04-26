#include <stdio.h>
#include <SDL.h>
#include "Constants.h"
#include "Draw.h"
#include "handlemouseEditor.h"
#include "States.h"

void scanEditor(int *x, int *y) {
    switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    x--;
                    break;
                case SDLK_RIGHT:
                    x++;
                    break;
                case SDLK_UP:
                    y--;
                    break;
                case SDLK_DOWN:
                    y++;
                    break;
                default:
                    break;
            }
            break;

        case SDL_MOUSEMOTION:
            SDL_GetMouseState(x, y);
//                if (now.tv_sec - startTime.tv_sec > 1) {
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(x, y);
            switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    printf("Left Mouse Clicked: %d-%d\tstates:%d\n", *x, *y, editState);
                    click = LEFT_CLICK;
                    // printf("%d\n",getSquare(x,y));
                    break;
                case SDL_BUTTON_RIGHT:
                    click = RIGHT_CLICK;
                    break;
                default:
                    //    printf("Unknown Mouse Clicked: %d-%d",x,y);
                    break;
            }
            break;
            gettimeofday(&now, NULL);
//                }
//                break;
    }
    changeStates(*x, *y);
}

////EDITOR
SDL_Surface *playBG;
SDL_Texture *textureEditBG;
SDL_Surface *refresh;
SDL_Texture *refreshBtnTexture;
SDL_Surface *next;
SDL_Texture *nextBtnTexture;

SDL_Renderer *renderer;

int layoutEditor(int x, int y, int *tableStatus) {
    handleMouseEditor(x, y, &editState, tableStatus);

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

    if (editState == -1 || editState == -11) {
        if (editState == -11) {
            NUMBER_OF_SHIP[1][0] = NUMBER_OF_SHIP[0][0];
            editState = 0;
        }
        SDL_Rect rectRefreshBtn = {904, 305, 27, 32};
        SDL_RenderCopy(renderer, refreshBtnTexture, NULL, &rectRefreshBtn);
    }

    if (editState == -2 || editState == -22) {

        if (editState == -22) {
            NUMBER_OF_SHIP[1][1] = NUMBER_OF_SHIP[0][1];
            editState = 0;
        }
        SDL_Rect rectRefreshBtn = {938, 305, 27, 32};
        SDL_RenderCopy(renderer, refreshBtnTexture, NULL, &rectRefreshBtn);
    }

    if (editState == -3 || editState == -33) {

        if (editState == -33) {
            NUMBER_OF_SHIP[1][2] = NUMBER_OF_SHIP[0][2];
            editState = 0;
        }
        SDL_Rect rectRefreshBtn = {972, 305, 27, 32};
        SDL_RenderCopy(renderer, refreshBtnTexture, NULL, &rectRefreshBtn);
    }

    if (editState == -4 || editState == -44) {
        if (editState == -44) {
            NUMBER_OF_SHIP[1][3] = NUMBER_OF_SHIP[0][3];
            editState = 0;
        }
        SDL_Rect rectRefreshBtn = {986, 394, 27, 32};
        SDL_RenderCopy(renderer, refreshBtnTexture, NULL, &rectRefreshBtn);

    }

    if ((editState == -5 || editState == -55) && NUMBER_OF_SHIP[1][0] == 0
        && NUMBER_OF_SHIP[1][1] == 0 && NUMBER_OF_SHIP[1][2] == 0 && NUMBER_OF_SHIP[1][3] == 0) {
        SDL_Rect rectRefreshBtn = {883, 504, 136, 49};
        SDL_RenderCopy(renderer, nextBtnTexture, NULL, &rectRefreshBtn);
        if (editState == -55) {
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

void loadEditorTexture() {
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

void destroyEditorTexture() {
    SDL_DestroyTexture(textureEditBG);
    SDL_DestroyTexture(refreshBtnTexture);
    SDL_DestroyTexture(nextBtnTexture);
}
