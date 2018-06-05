#ifndef BATTLE_FILE
#define BATTLE_FILE

void scanBattle(int *x, int *y);

int battle(int x, int y, int *playerTableStatus, int *opponentTableStatus);

void loadBattleTexture();

void destroyBattleTexture();

void endGameMessage(const char* message);
#endif