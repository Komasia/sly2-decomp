// MATCH (Claude agent for Lilly, T1657 2026-10-25). Case 3 builds CLQ clq = {-0.25, 0.0015625} and LM lm = {0.1, 1.0} on the
// stack: uJoy = GLimitLm(&lm, GFromClq(|d.xy|, &clq)), radJoy = atan2(d.y, d.x) with d = pos(ploEnemy) - pos(pactor).
// What finished it (the old 1-off was the por/li.s order of the clq init): see notes/140000.md (T1657).
typedef int qword __attribute__((mode(TI)));
/* JOBSLYATTACK::Drive (AIJOB vt slot 14): Sly's attack as pad input, the stick toward the enemy in states 1..4: full
 * deflection, with Square held for the first 0.1 s of the cane strike (2) and the dive (4); in the jump (3) the
 * deflection by distance (-0.25 + d / 640, clamped to 0.1..1) and Cross for its first 0.1 s while still on the ground.
 * Layout: SafeHouse port (actorai.cpp JOBSLYATTACK::Drive). */
/* a controller state (SafeHouse po.h PADCTL) */
struct PADCTL {
    /* 0x00 */ char pad[0x18];
    /* 0x18 */ float radJoy;   /* field: SafeHouse port - the left stick's world heading */
    /* 0x1c */ float uJoy;     /* field: SafeHouse port - its deflection */
    /* 0x20 */ char pad2[0x30 - 0x20];
    /* 0x30 */ int grfbtn;     /* field: SafeHouse port - the buttons down */
};
struct SLY { char pad[0x2DC]; int stJump; };   /* jump.state (-1 none) */
struct JOBSLYATTACK {
    /* 0x00 */ char pad[0x10];
    /* 0x10 */ struct SLY *pactor;   /* field: SafeHouse port (AIJOB) */
    /* 0x14 */ char pad2[0x30 - 0x14];
    /* 0x30 */ int st;               /* field: SafeHouse port */
    /* 0x34 */ float tSt;            /* field: SafeHouse port */
    /* 0x38 */ void *ploEnemy;       /* field: SafeHouse port */
};
#define PADBTN_Cross  0x40   /* the jump */
#define PADBTN_Square 0x80   /* the attack */
#include "clock.h"
struct CLQ { float g0, g1, g2, gPad; } __attribute__((aligned(16)));
struct LM { float gMin, gMax; };
void Drive__5AIJOBP6PADCTL(struct JOBSLYATTACK *pjob, struct PADCTL *ppadctl);
qword PosOfLo__FP2LO(void *p);
float atan2f(float y, float x);
void StampPadctlState__FP6PADCTL(struct PADCTL *ppadctl);
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
void Drive__12JOBSLYATTACKP6PADCTL(struct JOBSLYATTACK *pjob, struct PADCTL *ppadctl)
{
    Drive__5AIJOBP6PADCTL(pjob, ppadctl);
    switch (pjob->st) {
    case 1: {
        qword d = Sub(PosOfLo__FP2LO(pjob->ploEnemy), PosOfLo__FP2LO(pjob->pactor));
        ppadctl->uJoy = 1.0f;
        ppadctl->radJoy = GAtanR(d);
        break;
    }
    case 2: {
        qword d = Sub(PosOfLo__FP2LO(pjob->ploEnemy), PosOfLo__FP2LO(pjob->pactor));
        ppadctl->uJoy = 1.0f;
        ppadctl->radJoy = GAtanR(d);
        if (g_clock.t - pjob->tSt < 0.1f) {
            ppadctl->grfbtn |= PADBTN_Square;
            StampPadctlState__FP6PADCTL(ppadctl);
        }
        break;
    }
    case 3: {
        qword a = PosOfLo__FP2LO(pjob->ploEnemy);
        qword b = PosOfLo__FP2LO(pjob->pactor);
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
        ppadctl->uJoy = s;
        ppadctl->radJoy = GAtanXY2(d, b);
        if (g_clock.t - pjob->tSt < 0.1f && pjob->pactor->stJump == -1) {
            ppadctl->grfbtn |= PADBTN_Cross;
            StampPadctlState__FP6PADCTL(ppadctl);
        }
        break;
    }
    case 4: {
        qword d = Sub(PosOfLo__FP2LO(pjob->ploEnemy), PosOfLo__FP2LO(pjob->pactor));
        ppadctl->uJoy = 1.0f;
        ppadctl->radJoy = GAtanR(d);
        if (g_clock.t - pjob->tSt < 0.1f) {
            ppadctl->grfbtn |= PADBTN_Square;
            StampPadctlState__FP6PADCTL(ppadctl);
        }
        break;
    }
    }
}
