/* func_001AD820 (0x1AD820): the memory card prompt's button line: a notice "&2S&.: <OK>" (string 0x38), a question
 * "&2S&. : <yes>       <no> : &2T&." (strings 0x36 / 0x37); the &2S / &2T codes draw the button glyphs. */
extern char D_002E6550[], g_sw[];
int NCardPrompt__FPv(void *p);
char *func_0013E368(void *p, int n);
char *strcpy(char *, const char *);
char *strcat(char *, const char *);
void func_001AD820(char *szOut)
{
    switch (NCardPrompt__FPv(D_002E6550)) {
    case 1:
        strcpy(szOut, "&2S&.: ");
        strcat(szOut, func_0013E368(g_sw, 0x38));
        break;
    case 2:
        strcpy(szOut, "&2S&. : ");
        strcat(szOut, func_0013E368(g_sw, 0x36));
        strcat(szOut, "       ");
        strcat(szOut, func_0013E368(g_sw, 0x37));
        strcat(szOut, " : &2T&.");
        break;
    }
}
