extern char D_003DD040[];
extern char g_sw[];
struct S { char pad[0x2A0]; int a[6]; };
int func_001FD0C0(void *p, int i);
void *PloFindSwNearest__FP2LO3OIDii(void *p, int a, int b, struct S *ps);
void *PsmaFindSm(void *x, struct S *ps) asm("PsmaFindSm__FP2SMP3ALO");
void func_001F0198(void *x, struct S *ps, int a, int b, void **ppv);
void func_00205478(struct S *p, int mask)
{
    int i;
    for (i = 0; i < 6; i++) {
        int f = (unsigned int)i < 6;
        int bit = 1 << i;
        if (!f) bit = 0;
        if (mask & bit) {
            if (++p->a[i] < 2) {
                int id = func_001FD0C0(D_003DD040, i);
                void *x = PloFindSwNearest__FP2LO3OIDii(g_sw, 4, id, p);
                if (x) {
                    void *y = PsmaFindSm(x, p);
                    if (!y)
                        func_001F0198(x, p, -1, 9, &y);
                }
            }
        }
    }
}
