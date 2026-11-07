extern char D_002E6550[], g_sw[];
int NCardPrompt__FPv(void *p);
char *func_0013E368(void *p, int n);
char *strcpy(char *, const char *);
void func_0021EDA0(char *a, const char *b);
void func_001AD820(char *buf)
{
    switch (NCardPrompt__FPv(D_002E6550)) {
    case 1:
        strcpy(buf, "&2S&.: ");
        func_0021EDA0(buf, func_0013E368(g_sw, 0x38));
        break;
    case 2:
        strcpy(buf, "&2S&. : ");
        func_0021EDA0(buf, func_0013E368(g_sw, 0x36));
        func_0021EDA0(buf, "       ");
        func_0021EDA0(buf, func_0013E368(g_sw, 0x37));
        func_0021EDA0(buf, " : &2T&.");
        break;
    }
}
