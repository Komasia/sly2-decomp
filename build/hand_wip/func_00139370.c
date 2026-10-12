typedef int qword __attribute__((mode(TI)));
typedef union { qword q; struct { long l; int n; int pad; } s; } GE;
struct X { int x0; int x4; int x8; unsigned char ab[4]; int c; long *al; };
struct P { char pad[0x1A0]; int n1A0; int pad1[3]; GE age[0x20]; int x3B0; unsigned char ab[4]; char pad2[0x438 - 0x3B8]; void *p438; };
extern char D_002DD600[];
extern char D_002DD5C0[];
struct X *func_001EC8D0(void *pv);
static __inline__ int NPow2(int c)
{
    int n = 1;
    int v;
    for (v = c >> 1; v; v >>= 1)
        n <<= 1;
    n <<= (n < c);
    return n;
}
void func_00139370(struct P *p, void *pv)
{
    struct X *px = func_001EC8D0(pv);
    int c, n, v, cExtra, i;
    GE *pge;
    p->p438 = (px->x8 & 1) ? D_002DD600 : D_002DD5C0;
    if (p->x3B0 == 0) {
        p->x3B0 = 1;
        for (i = 0; i < 4; i++)
            p->ab[i] = (px->ab[i] + 1) >> 1;
    }
    c = px->c;
    cExtra = 0;
    n = NPow2(c);
    while (n >= 32)
        n >>= 1;
    if (c < n)
        cExtra = n - c;
    p->n1A0 = n;
    pge = p->age;
    for (i = 0; i < c; i++) {
        pge->s.n = 6;
        pge->s.l = px->al[i];
        if (i < cExtra) {
            pge[1].q = pge[0].q;
            pge++;
        }
        pge++;
    }
}
