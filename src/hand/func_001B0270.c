/* A paged menu entry's action (SafeHouse menu.cpp: case 0x1B0270, "Keep Playing": the menu closed) on the menu D_003D9ED0. */
struct MENU;
extern struct MENU D_003D9ED0;   /* the paged menu (SafeHouse menu.h: orig 0x3D9ED0) */
void CloseMenu__Fii(struct MENU *pmenu);

void func_001B0270(void)
{
    CloseMenu__Fii(&D_003D9ED0);
}
