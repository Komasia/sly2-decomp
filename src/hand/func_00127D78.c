int func_00127DB8(void *a, void *b, void *c, void *d);
void func_00129658(void *a, int b);
int func_00127D78(void *a, void *b, void *c, void *d)
{
    int v = func_00127DB8(a, b, c, d);
    if (v) {
        if (d)
            func_00129658(d, v);
        return 1;
    }
    return 0;
}
