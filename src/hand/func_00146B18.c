// MATCH (Claude agent for Lilly, T1657 2026-10-25). Case 3 builds CLQ clq = {-0.25, 0.0015625} and LM lm = {0.1, 1.0} on the
// stack: q->x1C = GLimitLm(&lm, GFromClq(|d.xy|, &clq)), q->x18 = atan2(d.y, d.x) with d = pos(p->p38) - pos(p->p10).
// What finished it (the old 1-off was the por/li.s order of the clq init): see notes/140000.md (T1657).
typedef int qword __attribute__((mode(TI)));
struct Q { char pad[0x18]; float x18; float x1C; char pad2[0x30 - 0x20]; int x30; };
struct PO { char pad[0x2DC]; int x2DC; };
struct P { char pad[0x10]; struct PO *p10; char pad2[0x30 - 0x14]; int x30; float x34; void *p38; };
#include "clock.h"
struct CLQ { float g0, g1, g2, gPad; } __attribute__((aligned(16)));
struct LM { float gMin, gMax; };
void Drive__5AIJOBP6PADCTL(struct P *p, struct Q *q);
qword PosOfLo__FP2LO(void *p);
float atan2f(float y, float x);
void StampPadctlState__FP6PADCTL(struct Q *q);
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ qword Sub(qword a, qword b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return d; }
static __inline__ float SqrtQ(qword t)
{
    float g;
    __asm__ __volatile__("vsqrt Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "+j"(t));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(t));
    return g;
}
static __inline__ float GFromClq(float g, struct CLQ *pclq) { return pclq->g0 + g * (pclq->g1 + g * pclq->g2); }
static __inline__ float GLimitLm(struct LM *plm, float g)
{
    float gMin = plm->gMin, gMax = plm->gMax;
    if (g < gMin)
        return gMin;
    if (gMax < g)
        return gMax;
    return g;
}
/* b: allocation-only "j" input (Claude agent). It keeps b live past the clamp, so b gets its own early qmtc2 instead of
   staying in v0 until the vsub (then the clq clear can use v0 like the target). */
static __inline__ float GAtanXY2(qword d, qword b) { register qword r __asm__("v1"); /* register pin (Claude agent) */ float x; __asm__("qmfc2.ni %0, %1" : "=r"(r) : "j"(d), "j"(b)); x = GetX(r); { float y; __asm__("prot3w %0,%1" : "=r"(y) : "0"(r)); return atan2f(y, x); } }
/* y via an int + mtc1 (as in PanTiltFromVector__FG9VU_VECTORPfT1): no GPR output reload here, which keeps reload's round-robin on the target's v0 for case 3 */
static __inline__ float GAtanR(qword d)
{
    int y;
    float fy;
    __asm__("prot3w %0,%1" : "=r"(y) : "r"(d));
    __asm__("mtc1 %1,%0" : "=f"(fy) : "r"(y));
    return atan2f(fy, GetX(d));
}
// name: SafeHouse port (JOBSLYATTACK::Drive)
void Drive__12JOBSLYATTACKP6PADCTL(struct P *p, struct Q *q)
{
    Drive__5AIJOBP6PADCTL(p, q);
    switch (p->x30) {
    case 1: {
        qword d = Sub(PosOfLo__FP2LO(p->p38), PosOfLo__FP2LO(p->p10));
        q->x1C = 1.0f;
        q->x18 = GAtanR(d);
        break;
    }
    case 2: {
        qword d = Sub(PosOfLo__FP2LO(p->p38), PosOfLo__FP2LO(p->p10));
        q->x1C = 1.0f;
        q->x18 = GAtanR(d);
        if (g_clock.t - p->x34 < 0.1f) {
            q->x30 |= 0x80;
            StampPadctlState__FP6PADCTL(q);
        }
        break;
    }
    case 3: {
        qword a = PosOfLo__FP2LO(p->p38);
        qword b = PosOfLo__FP2LO(p->p10);
        struct CLQ clq = {-0.25f, 0.00156249990686774f};
        qword d;
        float s;
        {
        qword t;
        /* "m"(clq.g0): allocation-only input (Claude agent); the vsub waits for the g0 store, like the target */
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b), "m"(clq.g0));
        __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(t) : "j"(d));
        {
        struct LM lm = {0.1f, 1.0f};
        s = GLimitLm(&lm, GFromClq(SqrtQ(t), &clq));
        }
        }
        q->x1C = s;
        q->x18 = GAtanXY2(d, b);
        if (g_clock.t - p->x34 < 0.1f && p->p10->x2DC == -1) {
            q->x30 |= 0x40;
            StampPadctlState__FP6PADCTL(q);
        }
        break;
    }
    case 4: {
        qword d = Sub(PosOfLo__FP2LO(p->p38), PosOfLo__FP2LO(p->p10));
        q->x1C = 1.0f;
        q->x18 = GAtanR(d);
        if (g_clock.t - p->x34 < 0.1f) {
            q->x30 |= 0x80;
            StampPadctlState__FP6PADCTL(q);
        }
        break;
    }
    }
}
