extern char D_003D9ED0[], g_sw[], D_002A6EB8[];
int KindDataAccess__FP4MENU(void *p);
void *func_0013E368(void *p, int n);
void s1_strcpy(void *s, void *q);
void strcpy1(void *s, void *q);
void func_001ADBB8(void *s)
{
    switch (KindDataAccess__FP4MENU(D_003D9ED0)) {
    case 0x19:
    case 0x1E:
    case 0x1F:
        s1_strcpy(s, func_0013E368(g_sw, 0x40));
        strcpy1(s, D_002A6EB8);
        break;
    }
}
