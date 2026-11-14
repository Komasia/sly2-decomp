extern char D_002E6550[], g_sw[];
int NCardPrompt__FPv(void *p);
char *func_0013E368(void *p, int n);
char *strcpy(char *, const char *);
char *strcat(char *, const char *);
void func_001AD820(char *buf)
{
    switch (NCardPrompt__FPv(D_002E6550)) {
    case 1:
        strcpy(buf, "&2S&.: ");
        strcat(buf, func_0013E368(g_sw, 0x38));
        break;
    case 2:
        strcpy(buf, "&2S&. : ");
        strcat(buf, func_0013E368(g_sw, 0x36));
        strcat(buf, "       ");
        strcat(buf, func_0013E368(g_sw, 0x37));
        strcat(buf, " : &2T&.");
        break;
    }
}
