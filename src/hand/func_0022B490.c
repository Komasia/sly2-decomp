struct CHK { int a[16]; };
struct X { int flags; struct CHK chk; int a; int b; };
struct M { char pad[0x3C40]; struct CHK chk; };
extern char D_00443740[];
void func_0022B220(void *p, struct X *px, int n, int f);
void func_0020DF80(struct M *pm, struct X *px);
static __inline__ int FSameChk(struct CHK *a, struct CHK *b)
{
    if (a == b) return 1;
    if (!a || !b) return 0;
    return (a->a[2] ^ a->a[14]) == (b->a[2] ^ b->a[14]);
}
void func_0022B490(struct M *pm, struct CHK *pchk, int a, int b, int flags, int n)
{
    struct X x;
    struct CHK *pchkCur = &pm->chk;
    struct CHK *pchkX = &x.chk;
    *pchkX = *(pchk ? pchk : pchkCur);
    x.a = a;
    x.b = b;
    x.flags = flags;
    if (FSameChk(pchkX, pchkCur)) x.flags |= 2;
    if (n != -1)
        func_0022B220(D_00443740, &x, n, 1);
    else
        func_0020DF80(pm, &x);
}
