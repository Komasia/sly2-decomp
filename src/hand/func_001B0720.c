/* A paged menu entry's action (SafeHouse menu.cpp: case 0x1B0720, the slider started) on the menu D_003D9ED0. */
struct MENU;
extern struct MENU D_003D9ED0;   /* the paged menu (SafeHouse menu.h: orig 0x3D9ED0) */
void func_001AF6A0(struct MENU *pmenu);

void func_001B0720(void)
{
    func_001AF6A0(&D_003D9ED0);
}
