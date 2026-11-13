/* A screen string (SafeHouse menu.cpp case 0x5CB, orig 0x001AD928): the menu's data access kind localized. */
struct SW;
struct MENU;
extern struct SW g_sw;
extern struct MENU D_003D9ED0;   /* the paged menu */
char *func_0013E368(struct SW *psw, int id);   /* the world's localized string */
int KindDataAccess__FP4MENU(struct MENU *pmenu);
char *strcpy(char *, const char *);

void func_001AD928(char *pch)
{
    strcpy(pch, func_0013E368(&g_sw, KindDataAccess__FP4MENU(&D_003D9ED0)));
}
