typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
struct Out { qword v; int n; };
extern int D_002C3C20[];
extern qword D_002C3BA0[];
extern qword D_002A2DD0;
static inline qword MulMV(M3 *pm, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z" : "=j"(r) : "j"(pm->r[0]), "j"(pm->r[1]), "j"(pm->r[2]), "j"(v));
    return r;
}
void func_001F5510(void *p, M3 *pm, int i, struct Out *po)
{
    qword v, l, one, r;
    float f;
    po->n = D_002C3C20[i];
    v = MulMV(pm, D_002C3BA0[i]);
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z\n\tvsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=&j"(l), "=&j"(one) : "j"(v));
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(l));
    if (!(f < 0.0001f)) __asm__("nop\n\tnop\n\tvdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(l), "j"(v));
    else r = D_002A2DD0;
    po->v = r;
}
