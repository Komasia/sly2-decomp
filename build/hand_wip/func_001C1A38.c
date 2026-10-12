struct E { float t; unsigned short k; unsigned short bit; };
void *func_002332B8(void *dst, void *src, int cb);
void func_001C1A38(int c, struct E *ae, int bit, float g0, float g1)
{
    int i, j;
    struct E *pe, *pi;
    for (i = 0; i < c; i++)
        if (g0 <= ae[i].t) break;
    for (j = i; j < c; j++)
        if (g1 < ae[j].t) break;
    func_002332B8(&ae[j + 2], &ae[j], (c - j) * 8);
    ae[j + 1].t = g1;
    ae[j + 1].bit = bit;
    ae[j + 1].k = 0;
    func_002332B8(&ae[i + 1], &ae[i], (j - i) * 8);
    ae[i].bit = bit;
    ae[i].t = g0;
    ae[i].k = 1;
}