/* class: MENU, the paged menu (SafeHouse menu.cpp, orig 0x001AFF88: the game settings applied, state 9). */
struct MENU;
extern char D_003D4A60[];   /* the game save */
void ApplyGameSettings__FP8GAMESAVE(void *pgamesave);
void SetMenuState__FP4MENUi(struct MENU *pmenu, int state);

void func_001AFF88(struct MENU *pmenu)
{
    ApplyGameSettings__FP8GAMESAVE(D_003D4A60);
    SetMenuState__FP4MENUi(pmenu, 9);
}
