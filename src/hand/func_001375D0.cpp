/* SetSlyDodgeState: Sly's dodge state: -1 ends it (his velocity scaled by D_002BC9B8); 0 / 1 dodge to one side: he
 * faces his object (+0x10DC), the dodge clip's root channel velocity at its speed becomes his velocity (in world space)
 * and its reverse his +0x190, and the clip is applied. Layout: SafeHouse port (sly.cpp, asega.h). */
// MATCH (Claude agent, laneB7, 2026-10-23), from fresh3 (2). One commented register pin: vel pinned to vf2 in the VU_FLOATM operator*, and the allocation-only duplicate g operand is "jm" (memory allowed, so it needs no second reload of the spilled g). The VU_FLOATM ctor is asm("lw") from "m"(f).
typedef int qword __attribute__((mode(TI)));
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); }
};
struct VU_VECTOR {
    qword q;
    VU_VECTOR(const qword &v) { q = v; }
};
struct VU_FLOATM {
    qword q;
    VU_FLOATM(const float &f) { __asm__("lw %0, %1" : "=r"(q) : "m"(f)); }
};
static inline qword operator*(VU_VECTOR v, VU_FLOATM f)
{
    qword r;
    register qword vv __asm__("vf2") = v.q; /* register pin: vel must be vf2 while g's reload and the output share vf1 */
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(vv), "j"(f.q), "jm"(f.q));
    return r;
}
static inline qword operator*(VU_VECTOR v, VU_FLOAT f)
{
    qword r;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v.q), "j"(f.q));
    return r;
}
struct MATRIX3 { qword r[3]; };
static inline qword operator*(const MATRIX3 &m, VU_VECTOR v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
        : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(v.q));
    return r;
}

#define V4(a) virtual void a##0(); virtual void a##1(); virtual void a##2(); virtual void a##3();
struct BASE { int x0, x4, x8; };
struct P : BASE {
    V4(a) V4(b) V4(c) V4(d) V4(e) V4(f) V4(g) V4(h)
    virtual qword GetVel();            /* 33 */
    virtual void v34();
    virtual void SetVel(qword v);      /* 35 */
};
struct PX {
    char pad[0x190];
    qword v190;
    char pad1A0[0x10];
    MATRIX3 m1B0;
    char pad1E0[0x1030 - 0x1E0];
    int a1030;
    int a1034[(0x10DC - 0x1034) / 4];
    int x10DC;
};
struct Q {
    virtual void v1();
    virtual void v2();
    virtual void Eval(int n, qword *pv, float g0, float g1);
};
struct R { int x0; Q *pq; };   // ASEGCHN: its position track
struct X { char pad[0x78]; float svt; };   // ASEG: +0x78 its speed (SafeHouse sm.h)
struct S { P *p; int state; float tState; int stateLast; X *paseg0; X *paseg1; };   // SLYDODGE (Sly +0x1FF0)
#include "clock.h"
extern "C" {
extern float D_002BC9B8;
void FaceObject(P *p, int n) asm("FaceObject__FP5ACTORP2LO");
R *PchnFindAseg(X *px, P *p, int a, int b) asm("PchnFindAseg__FP4ASEGP3ALOPvi");
void ClearSmaHandle(void *pv) asm("ClearSmaHandle__FPP3SMA");
void ApplyAsegCur(X *px, P *p, int n, void *pv, float g0, float g1) asm("ApplyAsegCur__FP4ASEGP3ALOffiPP5ASEGA");
}
#define PXOF(p) ((PX *)(p))

// name: SafeHouse port (SetSlyDodgeState)
extern "C" void SetSlyDodgeState__FP3SLYi(S *s, int state)
{
    X *px;
    if (state == s->state)
        return;
    s->state = state;
    px = 0;
    s->tState = g_clock.t;
    if (state == -1) {
        VU_FLOATM g(D_002BC9B8);
        qword vel = s->p->GetVel();
        qword r = VU_VECTOR(vel) * g;
        s->p->SetVel(r);
        return;
    }
    if (state >= -1) if (state < 2) {
        union { qword q; } v;
        if (state == 0)
            px = s->paseg0;
        else
            px = s->paseg1;
        FaceObject(s->p, PXOF(s->p)->x10DC);
        PchnFindAseg(px, s->p, 1, 1)->pq->Eval(0, &v.q, 0.0f, px->svt);
        s->p->SetVel(PXOF(s->p)->m1B0 * VU_VECTOR(v.q));
        PXOF(s->p)->v190 = VU_VECTOR(v.q) * VU_FLOAT(-1.0f);
        s->stateLast = state;
    }
    ClearSmaHandle(PXOF(s->p)->a1034);
    ApplyAsegCur(px, s->p, 1, &PXOF(s->p)->a1030, 0.0f, 1.0f);
}
