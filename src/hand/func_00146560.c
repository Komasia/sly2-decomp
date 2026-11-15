typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
/* JOBBENTLEYATTACK::Drive (AIJOB vt slot 14): Bentley's attack as pad input: the stick toward the enemy (slowly, 0.1,
 * in state 0), and in the swing (state 2) Square held for its first 0.1 s. Layout: SafeHouse port (actorai.cpp). */
/* a controller state (SafeHouse po.h PADCTL) */
struct PADCTL {
    /* 0x00 */ char pad[0x18];
    /* 0x18 */ float radJoy;   /* field: SafeHouse port - the left stick's world heading */
    /* 0x1c */ float uJoy;     /* field: SafeHouse port - its deflection */
    /* 0x20 */ char pad2[0x30 - 0x20];
    /* 0x30 */ int grfbtn;     /* field: SafeHouse port - the buttons down */
};
struct JOBBENTLEYATTACK {
    /* 0x00 */ char pad[0x10];
    /* 0x10 */ void *pactor;     /* field: SafeHouse port (AIJOB) */
    /* 0x14 */ char pad2[0x30 - 0x14];
    /* 0x30 */ int st;           /* field: SafeHouse port */
    /* 0x34 */ float tSt;        /* field: SafeHouse port */
    /* 0x38 */ void *ploEnemy;   /* field: SafeHouse port */
};
#define PADBTN_Square 0x80   /* the pad controller's square: the attack */
#include "clock.h"
void Drive__5AIJOBP6PADCTL(struct JOBBENTLEYATTACK *pjob, struct PADCTL *ppadctl);
qword PosOfLo__FP2LO(void *p);
float atan2f(float y, float x);
void StampPadctlState__FP6PADCTL(struct PADCTL *ppadctl);
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
// name: SafeHouse port (JOBBENTLEYATTACK::Drive)
void Drive__16JOBBENTLEYATTACKP6PADCTL(struct JOBBENTLEYATTACK *pjob, struct PADCTL *ppadctl)
{
    Drive__5AIJOBP6PADCTL(pjob, ppadctl);
    if (pjob->st < 3) if (pjob->st >= 0) {
        qword a, b, d;   /* the enemy, the actor, the direction */
        float u;   /* the stick's deflection */
        a = PosOfLo__FP2LO(pjob->ploEnemy);
        b = PosOfLo__FP2LO(pjob->pactor);
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
        u = 1.0f;
        if (pjob->st == 0) u = 0.1f;
        ppadctl->uJoy = u;
        ppadctl->radJoy = atan2f(GetY(d), GetX(d));
        if (pjob->st == 2 && g_clock.t - pjob->tSt < 0.1f) {
            ppadctl->grfbtn |= PADBTN_Square;
            StampPadctlState__FP6PADCTL(ppadctl);
        }
    }
}
