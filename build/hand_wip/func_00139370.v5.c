/* v5 (Claude agent, laneC11 2026-10-23): aligned 5 -> 4. cExtra = 0 moved before c = v, plus a 2nd pin cExtra in $10 (t2). Left: with cExtra pinned, if-conversion gives bnel+subu instead of slt/subu/movn (v1/v0 swap on the slt). cExtra unpinned with the early init: 13; px pinned to $9 too: 7. */
/* v4 (Claude agent, laneC9 2026-10-23): aligned 6 -> 5 with ONE register pin (c in $8) plus v = px->c; c = v; v >>= 1 (gives the target's lw v0 + daddu t0,v0). Left: cExtra = 0 (t2) is emitted after the loops; target sets it right after the load (then the loop-head alignment nops line up). cExtra = 0 right after c = v: 13 (px/cExtra swap t1/t2); declaration order: 13. */
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
    int n, v, i, j;
    register int cExtra asm("$10");
    register int c asm("$8"); /* register pin (Claude agent): c in t0 */
    GE *pge;
    p->p438 = (px->x8 & 1) ? D_002DD600 : D_002DD5C0;
    if (p->x3B0 == 0) {
        p->x3B0 = 1;
        for (j = 0; j < 4; j++)
            p->ab[j] = (px->ab[j] + 1) >> 1;
    }
    v = px->c;
    cExtra = 0;
    c = v;
    n = 1;
    for (v >>= 1; v; v >>= 1)
        n <<= 1;
    n <<= (n < c);
    while (n >= 32)
        n >>= 1;
    if (c < n)
        cExtra = n - c;
    p->n1A0 = n;
    pge = p->age;
    for (i = 0; i < c; i++) {
        pge->s.l = px->al[i];
        pge->s.n = 6;
        if (i < cExtra) {
            pge[1].q = pge[0].q;
            pge++;
        }
        pge++;
    }
}
