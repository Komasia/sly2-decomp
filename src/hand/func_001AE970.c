/* class: the menu HUD widget D_003D9ED0 (vtable 0x2D37D0; ResetHudWidgets 0x1D9408 calls it): closed (CloseMenu), its menu state
 * 0 (SetMenuState) and +0x20 cleared. */
typedef struct MENU {
    /* 0x00 */ char pad0[0x20];
    /* 0x20 */ int n20;
} MENU;

void CloseMenu__Fii(void);
void SetMenuState__FP4MENUi(MENU *pmenu, int state);

void func_001AE970(MENU *pmenu)
{
    CloseMenu__Fii();
    SetMenuState__FP4MENUi(pmenu, 0);
    pmenu->n20 = 0;
}
