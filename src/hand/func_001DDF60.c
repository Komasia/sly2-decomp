/* A screen string (SafeHouse screenrt.cpp, orig 0x001DDF60 (0x5D7): the world's string 0x40, then D_002A7AA8). */
struct SW;
extern struct SW g_sw;
extern char D_002A7AA8[];   /* " : &2T&." */
char *func_0013E368(struct SW *psw, int id);   /* the world's localized string */
char *strcpy(char *, const char *);
char *strcpy1(char *, const char *);   /* (strcat) */

void func_001DDF60(char *pch)
{
    strcpy(pch, func_0013E368(&g_sw, 0x40));
    strcpy1(pch, D_002A7AA8);
}
