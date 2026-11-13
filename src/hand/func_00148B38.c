extern char g_sw[];
void FAddRsmg(void *a, void *b, int n, void *c, int d, int e, int f, int g) asm("FAddRsmg__FP4RSMGiPii3OIDN24");
void func_00148B38(char *p, int d, int e, int f, int g)
{
    FAddRsmg(g_sw, p + 0xB4, 8, p + 0xB0, d, e, f, g);
}
