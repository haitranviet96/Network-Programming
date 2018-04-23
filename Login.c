#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Constants.h"

int loadFromRenderedText(SDL_Texture* texture, char* text, SDL_Color color){
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, text, color );
    if( textSurface != NULL )
    {
        //Create texture from surface pixels
        texture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( texture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            textSurface->w;
            textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    else
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }


    //Return success
    return texture != NULL;
}

int loadMedia()
{
    TTF_Init();
    
    //Loading success flag
    int success = 1;

    //Open the font
    gFont = TTF_OpenFont( "assets/fonts/lazy.ttf", 28 );
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = 0;
    }
    else
    {
        //Render the prompt
        SDL_Color textColor = { 0, 0, 0, 0xFF };
        if( !loadFromRenderedText( gPromptTextTexture, "Enter Text:", textColor ) )
        {
            printf( "Failed to render prompt text!\n" );
            success = 0;
        }
    }

    return success;
}