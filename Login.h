#ifndef LOGIN_FILE
#define LOGIN_FILE

int loadFromRenderedText(SDL_Texture** texture, char* text, SDL_Color color);

int loadMedia();

void render( SDL_Texture* texture, int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip );

void closeLogin();

#endif