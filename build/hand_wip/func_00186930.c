typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } MATRIX4;
struct A { MATRIX4 m; char pad[0x30]; qword v70; char pad2[0x20]; void *pA0; };
struct B { char pad[0x40]; MATRIX4 m; };
struct S { int x0; struct A *p4; struct A *p8; struct B *pC; MATRIX4 m10; MATRIX4 m50; qword v90; qword vA0; qword vB0;
    float gC0; float gC4; float gC8; };
extern float func_0011E4B0(qword a, qword b, qword *pv);
extern qword func_0022FCC8(int n, void *p, qword v);
static __inline__ qword Mul(MATRIX4 *pm, qword v)
{
    qword o;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(o) : "j"(pm->r[0]), "j"(pm->r[1]), "j"(pm->r[2]), "j"(pm->r[3]), "j"(v));
    return o;
}
static __inline__ qword VSub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static __inline__ int NLen(qword a)
{
    qword d, one;
    int n;
    __asm__("vmul.xyz %0, %1, %1" : "=j"(d) : "j"(a));
    __asm__("vaddw.x %0, $vf0, $vf0w\n\tvadday.x ACC, %1, %1y\n\tvmaddz.x %1, %0, %1z" : "=&j"(one), "+j"(d));
    __asm__("vsqrt Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(n) : "j"(d));
    return n;
}
void func_00186930(struct S *p)
{
    qword d1, d2, v;
    int n1, n2;
    p->m10 = p->p4->m;
    p->m50 = p->p8->m;
    v = p->p8->v70;
    d1 = VSub(Mul(&p->pC->m, p->vB0), v);
    n1 = NLen(d1);
    d2 = VSub(v, p->p4->v70);
    n2 = NLen(d2);
    *(int *)&p->gC4 = n1;
    *(int *)&p->gC0 = n2;
    p->gC8 = func_0011E4B0(d2, d1, &p->v90);
    p->v90 = func_0022FCC8(0, p->p8->pA0, p->v90);
}
