/* CloseMenu: an open menu (state 7) closes (state 8), back to its first level. Layout: SafeHouse port (menu.cpp
 * MENU). */
struct MENU {
    /* 0x000 */ char pad0[0x24];
    /* 0x024 */ int depth;      /* field: SafeHouse port */
    /* 0x028 */ char pad28[0x1e8 - 0x28];
    /* 0x1e8 */ int state;      /* field: SafeHouse port */
};
void SetMenuState(struct MENU *pmenu, int state) asm("SetMenuState__FP4MENUi");

// name: SafeHouse port (CloseMenu)
void CloseMenu__Fii(struct MENU *pmenu, int a1)
{
    if (pmenu->state == 7) {
        if (pmenu->depth >= 2)
            pmenu->depth = 1;
        SetMenuState(pmenu, 8);
    }
}
