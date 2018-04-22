#ifndef EDITOR_FILE
#define EDITOR_FILE

int layoutEditor(int x, int y, int *states, int *tableStatus);

void loadEditorTexture(SDL_Renderer *renderer);

void destroyEditorTexture();

#endif