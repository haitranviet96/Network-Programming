#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include "Constants.h"
#include <stdbool.h>
#include "Utils.h"


// Draw points with random colors and positions
void draw_random_points(int nr_points, bool randomizeColor, SDL_Renderer *renderer)
{
    for(int i = 0; i < nr_points; ++i)
    {
        if(randomizeColor)
        {
            SDL_SetRenderDrawColor(renderer, randomColor(), randomColor(), randomColor(), 255);
        }
        SDL_RenderDrawPoint(renderer, randomNumber(0, WINDOW_WIDTH), randomNumber(0, WINDOW_HEIGHT));
    }
}

// Draw random lines with random color
void draw_random_lines(int nr_lines, bool randomizeColor, SDL_Renderer *renderer)
{
    for(int i = 0; i < nr_lines; ++i)
    {
        if(randomizeColor)
        {
            SDL_SetRenderDrawColor(renderer, randomColor(), randomColor(), randomColor(), 255);
        }
        SDL_RenderDrawLine(renderer, randomNumber(0, WINDOW_WIDTH), randomNumber(0, WINDOW_HEIGHT), randomNumber(0, WINDOW_WIDTH), randomNumber(0, WINDOW_HEIGHT));
    }
}


void draw_squares(int x, int y,int* stats, SDL_Rect *rect, SDL_Renderer *renderer){
    int j;
//SDL_SetRenderDrawColor(renderer, 0, 191, 255, 255);
       // SDL_RenderClear(renderer);



        for (j=0;j<HORIZONTAL_SQUARE*VERTICAL_SQUARE;j++){
        rect[j].x=22+50*(j%HORIZONTAL_SQUARE);
        rect[j].y=24+50*(int)(j/HORIZONTAL_SQUARE);
        rect[j].h=49;
        rect[j].w=49;
         if (stats[j]==4){
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //??
        }else if(rect[j].x<=x&&x<=rect[j].x+rect[j].h&&rect[j].y<=y&&y<=rect[j].y+rect[j].w){
        SDL_SetRenderDrawColor(renderer, 255, 20, 60, 255);
        }
        else if(stats[j]==0) {
        SDL_SetRenderDrawColor(renderer, 0, 100, 0, 255); //DARK GREEN
        }
        else if (stats[j]==1){
        SDL_SetRenderDrawColor(renderer, 72, 61, 139, 255); //PURPLE
        }
        else if  (stats[j]==10){
       SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); //VIOLETRED
        }
        else if  (stats[j]==110){
       SDL_SetRenderDrawColor(renderer, 220, 62, 150, 255); //CRIMSON
        }
        else if (stats[j]==2){
        SDL_SetRenderDrawColor(renderer, 216, 191, 216, 255); //THISTLE
        }
        else if (stats[j]==20){
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); //LIME GREEN
        }
        else if (stats[j]==220){
        SDL_SetRenderDrawColor(renderer, 127, 255, 0, 255); //CHARTREUSE
        }
        else if (stats[j]==3){
        SDL_SetRenderDrawColor(renderer, 107, 130, 255, 255); //MEDIUM PURPLE
        }
        else if (stats[j]==30){
        SDL_SetRenderDrawColor(renderer, 61, 89, 171, 255); //COBALT
        }
        else if (stats[j]==330){
        SDL_SetRenderDrawColor(renderer, 198, 226, 255, 255); //SLATEGRAY

        }

        else if (stats[j]==40){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //??
        }
        // stats = 0: SEA
        // stats =1: PROSPECTIVE SHIP
        // stats =2: PROSPECTIVE SUBMARINE
        // stats =3: PROSPECTIVE CRUISER
        // stats =10: SHIP  HORIZONTAL
        // stats =11: SHIP  VERTICAL
        // stats =20: SUBMARINE  HORIZONTAL
        // stats =22: SUBMARINE  VERTICAL
        // stats =30: CRUISER  HORIZONTAL
        // stats =33: CRUISER  VERTICAL
        SDL_RenderFillRect(renderer, &rect[j]);
        }
       // SDL_RenderPresent(renderer)

}


void draw_number(int x,  int y,SDL_Texture *texture, SDL_Renderer *renderer){
    SDL_Rect dstrect2 = { x, y,13, 25 };
    SDL_RenderCopy(renderer, texture, NULL, &dstrect2);

}
