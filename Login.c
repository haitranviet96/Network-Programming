#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Constants.h"
#include "Utils.h"

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
            } else if (event.key.keysym.sym == SDLK_RETURN && strlen(inputText) >= 6) {
                return 1;
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
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
        SDL_RenderClear(renderer);

        int w, h;
        SDL_QueryTexture(gPromptTextTexture, NULL, NULL, &w, &h);

        //Render text textures
        render(gPromptTextTexture, (WINDOW_WIDTH - w) / 2, (WINDOW_HEIGHT - h) / 2 - h, NULL, 0, NULL, SDL_FLIP_NONE);

        SDL_QueryTexture(gInputTextTexture, NULL, NULL, &w, &h);
        render(gInputTextTexture, (WINDOW_WIDTH - w) / 2, (WINDOW_HEIGHT - h) / 2, NULL, 0, NULL, SDL_FLIP_NONE);
    }

    return 0;
}

void closeLogin() {
    //Disable text input
    SDL_StopTextInput();

    //Free loaded images
    free(gPromptTextTexture);
    free(gInputTextTexture);
}