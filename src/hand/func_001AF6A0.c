/* class: MENU, the paged menu (SafeHouse menu.h / menu.cpp, orig 0x001AF490 / 0x001AF608 / 0x001AF6A0): from state 7
 * to state 0xB (the slider started, menu.cpp StartSlider). */
struct MENU {
    /* 0x000 */ char pad0[0x1e8];
    /* 0x1e8 */ int state;   /* field: SafeHouse port */
};
void SetMenuState__FP4MENUi(struct MENU *pmenu, int state);

void func_001AF6A0(struct MENU *pmenu, int n)
{
    if (pmenu->state == 7) {
        SetMenuState__FP4MENUi(pmenu, 0xB);
    }
}
