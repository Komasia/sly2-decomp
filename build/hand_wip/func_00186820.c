typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } MATRIX4;
struct A { MATRIX4 m; char pad[0x30]; qword v70; char pad2[0x20]; void *pA0; };
struct B { char pad[0x40]; MATRIX4 m; };
struct S { int x0; struct A *p4; struct A *p8; struct B *pC; MATRIX4 m10; MATRIX4 m50; qword v90; qword vA0; qword vB0;
    float gC0; float gC4; float gC8; };
struct N { int k; char pad[0xC]; struct N *next; char pad2[8]; struct S *ps; };
struct E { char pad[0x90]; struct N *pn; char pad2[0x100 - 0x94]; };
struct O { char pad[0x50]; int c; struct E *ae; char pad2[0x148 - 0x58]; unsigned long grf; };
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
void func_00186820(struct O *po)
{
    int i;
    struct N *pn;
    if (!(po->grf & 0x1000000000L)) return;
    for (i = 0; i < po->c; i++) {
        for (pn = po->ae[i].pn; pn; pn = pn->next) {
            if (pn->k == 7) {
                struct S *p = pn->ps;
                qword v = p->p8->v70;
                qword w = p->p4->v70;
                *(int *)&p->gC4 = NLen(VSub(Mul(&p->pC->m, p->vB0), v));
                *(int *)&p->gC0 = NLen(VSub(v, w));
            }
        }
    }
}
