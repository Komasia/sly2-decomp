struct E { int a; int b; int c; int d; };
void func_002090D0(struct E *pe, void *p);
void func_00207EB8(void *p, int mask, int b, int d, struct E *pe)
{
    int i;
    int bit = 1;
    for (i = 25; i >= 0; i--) {
        if (mask & bit) {
            func_002090D0(pe, p);
            pe->b = b;
            pe->d = d;
        }
        bit <<= 1;
        pe++;
    }
}
