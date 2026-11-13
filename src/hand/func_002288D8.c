extern char g_sw[];
void FAddRsmg(void *pq, void *a, int n, void *b, int c, int d, int e, int f) asm("FAddRsmg__FP4RSMGiPii3OIDN24");
void func_002288D8(char *p, int c, int d, int e, int f)
{
    if (c) FAddRsmg(g_sw, p + 0xE4, 4, p + 0xE0, c, d, e, f);
}
