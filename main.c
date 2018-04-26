#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>

#include "States.h"
#include "Number.h"
#include "Constants.h"
#include "Editor.h"
#include "Battle.h"
#include "Login.h"

int click;
int gameState = LOGIN_STATE;

int main(int argc, char **argv) {
    // text next to rerendered or not
    bool rendered = false;

    // login user text
    SDL_Color textColor = {0xFF, 0xFF, 0xFF, 0xFF};
    char *inputText = (char *) malloc(50);

    int x = 288;
    int y = 208;
    int j = 0;

    int tableStatus[HORIZONTAL_SQUARE * VERTICAL_SQUARE];
    FILE *data;
    char c;

    char text[20];

    // init SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error : %s\n", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("Battle Ship", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("SDL_CreateWindow Error : %s\n", SDL_GetError());
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
        return 1;
    }

    ////DRAW NUMBER
    drawOrangeNumberTexture();
    // texturenum = SDL_CreateTextureFromSurface(renderer, numdigit);

    /////////STATS and SATES
    for (int i = 0; i < HORIZONTAL_SQUARE * VERTICAL_SQUARE; i++) {
        tableStatus[i] = 0;
    }
    ////////////////////////

    ////////DATA
    data = fopen("assets/data/data.txt", "r+");
    if (data == NULL) {
        printf("Error opening data files!\n");
        return -1;
    }
    for (j = 0; j < 4; j++) {
        c = (char) fgetc(data);
        NUMBER_OF_SHIP[0][j] = -48 + (int) c;
        NUMBER_OF_SHIP[1][j] = NUMBER_OF_SHIP[0][j];
    }
    ////////////////////////

    gettimeofday(&startTime, NULL);
    while (!quit) {
        SDL_WaitEvent(&event);

        gettimeofday(&now, NULL);
        switch (event.type) {

            case SDL_QUIT:
                quit = true;
                break;

            default:
                break;
        }
        click = NONE_CLICK;

        if (gameState == LOGIN_STATE) {
            if (!rendered) {
                // load font
                rendered = true;
                // Initialize SDL_ttf
                if (TTF_Init() == -1) {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                } else {
                    //Load media
                    if (!loadMedia()) {
                        printf("Failed to load media!\n");
                    }

                    // text color white
                    loadFromRenderedText(&gInputTextTexture, inputText, textColor);

                    //Enable text input
                    SDL_StartTextInput();
                }
            } else {
                //The rerender text flag
                bool renderText = false;

                if (event.type == SDL_KEYDOWN) {
                    //Handle backspace
                    if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(inputText) > 0) {
                        //lop off character
                        inputText[strlen(inputText) - 1] = 0;
                        renderText = true;
                    }
                        //Handle copy
                    else if (event.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
                        SDL_SetClipboardText(inputText);
                    }
                        //Handle paste
                    else if (event.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
                        inputText = SDL_GetClipboardText();
                        renderText = true;
                    }else if (event.key.keysym.sym == SDLK_RETURN && strlen(inputText) >= 6) {
                        // continue
                        gameState = EDITOR_STATE;
                        closeLogin();
                        loadEditorTexture();
                    }
                }
                    //Special text input event
                else if (event.type == SDL_TEXTINPUT) {
                    //Not copy or pasting
                    if (!((event.text.text[0] == 'c' || event.text.text[0] == 'C') &&
                          (event.text.text[0] == 'v' || event.text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL)) {
                        //Append character
                        strcat(inputText, event.text.text);
                        renderText = true;
                    }
                }


                //Rerender text if needed
                if (renderText) {
                    //Text is not empty
                    if (inputText != "") {
                        //Render new text
                        puts(inputText);
                        loadFromRenderedText(&gInputTextTexture, inputText, textColor);
                    }
                        //Text is empty
                    else {
                        //Render space texture
                        loadFromRenderedText(&gInputTextTexture, " ", textColor);
                    }
                }

                //Clear screen
                SDL_SetRenderDrawColor(renderer,0, 0, 0, 0xFF);
                SDL_RenderClear(renderer);

                int w, h;
                SDL_QueryTexture(gPromptTextTexture, NULL, NULL, &w, &h);

                //Render text textures
                render(gPromptTextTexture, (WINDOW_WIDTH - w) / 2, 0, NULL, 0, NULL, SDL_FLIP_NONE);

                SDL_QueryTexture(gInputTextTexture, NULL, NULL, &w, &h);
                render(gInputTextTexture, (WINDOW_WIDTH - w) / 2, h, NULL, 0, NULL, SDL_FLIP_NONE);
            }
        }
        if (gameState == EDITOR_STATE) {
            scanEditor(&x,&y);
            if (layoutEditor(x, y, tableStatus)) {
                gameState = BATTLE_STATE;
                destroyEditorTexture();
                loadBattleTexture();
            }
        }
        if (gameState == BATTLE_STATE) {
            if (battle(x, y, tableStatus)) {
                destroyBattleTexture();
                gameState = CHALLENGE_STATE;
            }
        }

        SDL_RenderPresent(renderer);
    }

// Destroy texture
    destroyOrangeNumberTexture();

// Destroy SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
