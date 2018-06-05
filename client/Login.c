#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Constants.h"
#include "Utils.h"

SDL_Texture *loginBgTexture;

void loadLoginTexture() {
    // create bg texture
    SDL_Surface *bgSurface = IMG_Load("assets/login_bg.png");
    if (bgSurface == NULL) {
        printf("IMG_Load Error: Error load assets/login_bg.png");
        return;
    }
    loginBgTexture = SDL_CreateTextureFromSurface(renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
}

int receiveUserName(bool *rendered) {
    if (!(*rendered)) {
        // load font
        *rendered = true;

        // text color white
        loadFromRenderedText(&gInputTextTexture, inputText, textColor);
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
            } else if (event.key.keysym.sym == SDLK_RETURN) {
                if (strlen(inputText) >= 6) {
                    return 1;
                } else {
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED, "Error !", "Your name must be longer than 6 characters.", window);
                }
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
        SDL_Rect bgRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, loginBgTexture, NULL, &bgRect);

        int w, h;
        //Render text textures
        SDL_QueryTexture(gInputTextTexture, NULL, NULL, &w, &h);
        render(gInputTextTexture, (WINDOW_WIDTH - w) / 2, (WINDOW_HEIGHT - h) / 2, NULL, 0, NULL, SDL_FLIP_NONE);
    }

    return 0;
}

void closeLogin() {
    //Disable text input
    SDL_StopTextInput();

    //Free loaded images
    free(gInputTextTexture);
    free(loginBgTexture);
}