typedef int qword __attribute__((mode(TI)));
struct X;
extern "C" {
#include "clock.h"
extern float D_002BE76C;
extern float D_002BE770[16];
struct X { qword a; qword v; X(); };
struct T { char pad[0x40]; struct X x40; };
struct D { char pad[0x10]; void *p10; };
struct C { char pad[0xDC]; struct D *pDC; };
struct A { char pad[0xE8]; struct C *pE8; };
struct S { char pad[0x10]; struct A *p10; int pad2; struct T *p18; char pad3[0x1C]; void *p38; float f3C; };
qword PosOfLo(void *p) asm("PosOfLo__FP2LO");
float atan2f(float y, float x) asm("atan2f");
qword PosGoal(struct X *s, qword v) asm("PosGoal__FP4GOALG9VU_VECTOR");
qword SetVectorCylind(float a, float b, float c) asm("SetVectorCylind__Ffff");
int FKeepOnNav(void *q, qword v, qword *out) asm("FKeepOnNav__FP9NAVREGIONG9VU_VECTORP6VECTOR");
void func_002562A8(struct X *x);
void SetGoal(void *p, struct X *x) asm("SetGoal__7JOBGOTOP4GOAL");
}
inline X::X() { func_002562A8(this); }
extern "C" {
}
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
// name: SafeHouse port (JOBBD::ChooseAway)
extern "C" void ChooseAway__5JOBBD(struct S *p) {
    union { qword q; } hit;
    qword a, b, d, r;
    struct T *t;
    struct C *c;
    struct D *dd;
    void *q;
    float ang, best;
    unsigned int i;
    p->f3C = g_clock.t;
    t = p->p18;
    a = PosOfLo(p->p38);
    b = PosOfLo(p->p10);
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(b), "j"(a));
    c = p->p10->pE8;
    dd = c ? c->pDC : 0;
    q = dd ? dd->p10 : 0;
    best = 0.0f;
    ang = atan2f(GetY(d), GetX(d));
    r = PosGoal(&t->x40, b);
    for (i = 0; i < 16; i++) {
        qword o = SetVectorCylind(ang + D_002BE770[i], D_002BE76C, 0.0f);
        qword s;
        __asm__("vadd.xyzw %0, %1, %2" : "=j"(s) : "j"(b), "j"(o));
        if (FKeepOnNav(q, s, &hit.q)) {
            qword e, l;
            float g;
            __asm__("vsub.xyzw %0, %1, %2" : "=j"(e) : "j"(hit.q), "j"(a));
            __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(e) : "j"(e));
            __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(e));
            __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(l));
            if (g > best) {
                best = g;
                r = hit.q;
            }
        }
    }
    struct X x;
    x.v = r;
    SetGoal(t, &x);
}
