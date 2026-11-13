/* A screen string (SafeHouse screenrt.cpp, orig 0x001DDFB0 (0x5D5): the current game's percent "%d%%" (D_002A7AB8;
 * 0x1D82B8 on the save D_003D4A60)). */
extern char D_002A7AB8[];   /* "%d%%" */
extern char D_003D4A60[];
extern char D_003E0EA8[];
int func_001D82B8(void *p, void *psave);
int sprintf(char *, const char *, ...);

void func_001DDFB0(char *pch)
{
    sprintf(pch, D_002A7AB8, func_001D82B8(D_003E0EA8, D_003D4A60));
}
