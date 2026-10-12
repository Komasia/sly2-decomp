int func_001AC7A0(void *s, void *a, int n, int *out);
int func_001AC850(void *s, int h, void *b, int c, int *out);
void func_001AC808(void *s, int h);
int func_001AC9A0(void *s, void *a, void *b, int c)
{
    int h = -1;
    int v;
    int r = func_001AC7A0(s, a, 1, &h);
    if (r)
        return r;
    r = func_001AC850(s, h, b, c, &v);
    if (!r && v != c)
        r = 8;
    func_001AC808(s, h);
    return r;
}
