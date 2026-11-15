/* func_001ADBB8 (0x1ADBB8): a menu line for the data-access menus (kinds 0x19 / 0x1E / 0x1F): string 0x40 followed by
 * D_002A6EB8. */
extern char D_003D9ED0[], g_sw[], D_002A6EB8[];
int KindDataAccess__FP4MENU(void *p);
void *func_0013E368(void *p, int n);
void s1_strcpy(void *s, void *q) asm("strcpy");
char *strcat(char *, const char *);
void func_001ADBB8(void *szOut)
{
    switch (KindDataAccess__FP4MENU(D_003D9ED0)) {
    case 0x19:
    case 0x1E:
    case 0x1F:
        s1_strcpy(szOut, func_0013E368(g_sw, 0x40));
        strcat(szOut, D_002A6EB8);
        break;
    }
}
