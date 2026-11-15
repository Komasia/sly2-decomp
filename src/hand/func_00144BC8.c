// Match notes (Claude agent): Hard-reg VF vars in Dot fixed the first block; remaining: 2nd block vsub scheduled before the lui of D_002BD2F0 (target lui first).
typedef int qword __attribute__((mode(TI)));
/* JOBACTORFOLLOW::Drive (AIJOB vt slot 14): the path follower's pad input for an actor: the stick toward the steered
 * point (deflection 0.01 per unit of distance, at most 1, times the actor's speed), the walk button when asked; when
 * copying a player's controller, after the copy delay: walk when more than 500 away from it, and the player's
 * buttons of the copy mask pressed too (unless the copied actor's jump kind is 0).
 * Layout: SafeHouse port (actorai.h JOBACTORFOLLOW, aijobs.h JOBFOLLOW, po.h PADCTL). */
struct ACTOR;
struct ACTORVT { char pad[0x2C8]; short d; short pad2; int (*pfn)(struct ACTOR *); };   /* vt slot 89: the jump kind */
struct ACTOR { char pad[0xC]; struct ACTORVT *pvt; };
/* a controller state (SafeHouse po.h PADCTL) */
struct PADCTL {
    /* 0x00 */ char pad0[0x18];
    /* 0x18 */ float radJoy;          /* field: SafeHouse port - the left stick's world heading */
    /* 0x1c */ float uJoy;            /* field: SafeHouse port - its deflection */
    /* 0x20 */ char pad20[0x30 - 0x20];
    /* 0x30 */ int grfbtn;            /* field: SafeHouse port - the buttons down */
    /* 0x34 */ char pad34[0x7C - 0x34];
    /* 0x7c */ struct ACTOR *plo;     /* field: SafeHouse port - the owner */
};
struct JOBACTORFOLLOW {
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ void *pactor;                /* field: SafeHouse port (AIJOB) */
    /* 0x14 */ char pad14[0x4C - 0x14];
    /* 0x4c */ int st;                      /* field: SafeHouse port (JOBFOLLOW) */
    /* 0x50 */ float tSt;                   /* field: SafeHouse port */
    /* 0x54 */ char pad54[0x80 - 0x54];
    /* 0x80 */ qword pos;                   /* field: SafeHouse port - the steered point */
    /* 0x90 */ char pad90[0xC0 - 0x90];
    /* 0xc0 */ struct PADCTL *pcCopy;       /* field: SafeHouse port - the followed player's controller */
    /* 0xc4 */ int grfCopy;                 /* field: SafeHouse port - the buttons copied from it */
    /* 0xc8 */ float dtCopy;                /* field: SafeHouse port - the delay before copying */
    /* 0xcc */ int fWalk;                   /* field: SafeHouse port */
    /* 0xd0 */ float uSpeedActor;           /* field: SafeHouse port */
};
#define PADBTN_Walk 0x08   /* the walk button (SafeHouse actorai.cpp: grfbtn |= 8 when fWalk) */
#include "cid.h"
#include "clock.h"
extern qword g_normalZ;
extern float D_002BD2E0[3];   /* the deflection by distance: 0 + 0.01 d */
extern float g_lmZeroOne[2];
extern float D_002BD2F0;      /* 500: walk when farther from the copied player */
void Drive__5AIJOBP6PADCTL(struct JOBACTORFOLLOW *pjob, struct PADCTL *ppadctl);
qword PosOfLo__FP2LO(void *p);
float atan2f(float y, float x);
int FIsBasicDerivedFrom__FP5BASIC3CID(struct ACTOR *plo, int cid);
void StampPadctlState__FP6PADCTL(struct PADCTL *ppadctl);
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }

static __inline__ float LenXY(qword d)
{
    float g;
    qword t;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(t) : "j"(d));
    d = t;
    __asm__("vsqrt Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "+j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
static __inline__ float LenXY2(qword d)
{
    float g;
    qword t;
    /* volatile: raises the priority of the preceding limit load so lui/lwc1 interleave with vsub (Claude agent) */
    __asm__ __volatile__("vmul.xy %0, %1, %1" : "=j"(t) : "j"(d));
    __asm__("vaddy.x %0, %0, %0y" : "+j"(t));
    d = t;
    __asm__("vsqrt Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "+j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}

static __inline__ float GClampR(float g, float lo, float hi) { if (g < lo) return lo; if (hi < g) return hi; return g; }
static __inline__ int FFar(qword a, qword b) { qword d; float lim = D_002BD2F0; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b)); return lim < LenXY2(d); }
static __inline__ qword Dot(qword a, qword b) { register qword r __asm__("vf2"); register qword t __asm__("vf4");
        __asm__("vmul.xyz %1, %2, %3\n\tvaddw.x %0, $vf0, $vf0w\n\tvadday.x $ACC, %1, %1y\n\tvmaddz.x %1, %0, %1z"
                : "=&j"(t), "=&j"(r) : "j"(a), "j"(b)); return r; }
static __inline__ qword Perp(qword d, qword axis) { qword v, r;
        v = Dot(d, axis);
        __asm__("vmulx.xyzw %0, %1, %0x" : "+j"(v) : "j"(axis));
        __asm__("vsub.xyzw %0, %1, %0" : "+j"(v) : "j"(d)); return v; }
static __inline__ float GPoly(float *a, float g) { return a[0] + g * (a[1] + g * a[2]); }
// name: SafeHouse port (JOBACTORFOLLOW::Drive)
void Drive__14JOBACTORFOLLOWP6PADCTL(struct JOBACTORFOLLOW *pjob, struct PADCTL *ppadctl)
{
    Drive__5AIJOBP6PADCTL(pjob, ppadctl);
    if (pjob->st < 2) if (pjob->st >= 0) {
        qword pos;
        qword d, v, t, axis;   /* to the steered point; its xy part */
        float g, s;   /* the deflection, clamped */
        __asm__("lqc2 %0, %1" : "=j"(pos) : "m"(pjob->pos));
        v = PosOfLo__FP2LO(pjob->pactor);
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(pos), "j"(v));
        axis = g_normalZ;
        v = Perp(d, axis);
        g = GPoly(D_002BD2E0, LenXY(v));
        s = GClampR(g, g_lmZeroOne[0], g_lmZeroOne[1]);
        if (0.0f < s) {
            ppadctl->uJoy = s * pjob->uSpeedActor;
            ppadctl->radJoy = atan2f(GetY(v), GetX(v));
        }
        if (pjob->fWalk)
            ppadctl->grfbtn |= PADBTN_Walk;
        if (pjob->pcCopy && pjob->dtCopy < g_clock.t - pjob->tSt) {
            int fCopy = 1;
            struct ACTOR *pactorCopied = pjob->pcCopy->plo;
            qword a, b;
            __asm__("qmtc2.ni %1, %0" : "=j"(a) : "r"(PosOfLo__FP2LO(pjob->pactor)));
            __asm__("qmtc2.ni %1, %0" : "=j"(b) : "r"(PosOfLo__FP2LO(pactorCopied)));
            if (FFar(a, b))
                ppadctl->grfbtn |= PADBTN_Walk;
            if (FIsBasicDerivedFrom__FP5BASIC3CID(pactorCopied, CID_ACTOR))
                fCopy = pactorCopied->pvt->pfn((struct ACTOR *)((char *)pactorCopied + pactorCopied->pvt->d)) != 0;
            if (fCopy) {
                ppadctl->grfbtn |= pjob->pcCopy->grfbtn & pjob->grfCopy;
                StampPadctlState__FP6PADCTL(ppadctl);
            }
        }
    }
}
