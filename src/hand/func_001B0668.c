/* A paged menu entry's action (SafeHouse menu.cpp: case 0x1B0668, "No": back to the replaced page) on the menu D_003D9ED0. */
struct MENU;
extern struct MENU D_003D9ED0;   /* the paged menu (SafeHouse menu.h: orig 0x3D9ED0) */
void BackReplaced__FP4MENU(struct MENU *pmenu);

void func_001B0668(void)
{
    BackReplaced__FP4MENU(&D_003D9ED0);
}
