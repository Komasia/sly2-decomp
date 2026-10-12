/* 2 diff: qmfc2/sw use $a0 instead of $v1 for the length; everything else matches */
typedef int qword __attribute__((mode(TI)));
typedef struct Y { char pad[0xB0]; qword vB0; qword vC0; int nD0; char pad2[0xE0 - 0xD4]; int nE0; } Y;
typedef struct X { char pad[8]; Y *py; char pad2[0x20 - 0xC]; qword v20; } X;
extern qword D_002A2DA0;
void func_0012CE98(X *x);
static __inline__ qword VLen(qword c)
{
    qword l, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(l), "=&j"(one) : "j"(c));
    __asm__("vsqrt Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "=j"(l) : "j"(l));
    return l;
}
static __inline__ qword Normalize1(qword *pv, qword *pdef)
{
    qword c;
    qword l;
    float gl;
    __asm__("qmtc2.ni %1, %0" : "=j"(c) : "r"(*pv));
    l = VLen(c);
    __asm__("qmfc2.ni %0, %1" : "=r"(gl) : "j"(l));
    if (gl < 1e-4f) {
        *pv = *pdef;
    } else {
        qword rn;
        __asm__("vdiv Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, Q" : "=j"(rn) : "j"(c), "j"(l));
        *pv = rn;
    }
    return l;
}
void func_0012E120(X *x) { qword l; int n; func_0012CE98(x); x->py->vB0 = x->v20; x->py->vC0 = x->v20; l = Normalize1(&x->py->vC0, &D_002A2DA0); __asm__("qmfc2.ni %0, %2\n\tsw %0, %1" : "=r"(n), "=m"(x->py->nD0) : "j"(l)); x->py->nE0 = 0; }
