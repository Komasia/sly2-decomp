int func_001ABE78(int a, int b, int c, int d, int *pn);
int FUN_0018c9c0(int a, int b, int c)
{
    int n;
    int r = func_001ABE78(a, b, 1, c, &n);
    if (r) return r;
    return n == 1 ? 0 : 0xE;
}
