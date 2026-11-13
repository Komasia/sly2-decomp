/* A screen string (SafeHouse menu.cpp case 0x2F2, orig 0x001AD7E0): the card dialog's message D_002E6590 localized. */
struct SW;
extern struct SW g_sw;
extern int D_002E6590;   /* the card dialog's message id */
char *func_0013E368(struct SW *psw, int id);   /* the world's localized string */
char *strcpy(char *, const char *);

void func_001AD7E0(char *pch)
{
    strcpy(pch, func_0013E368(&g_sw, D_002E6590));
}
