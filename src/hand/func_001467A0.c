typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
/* JOBSLYATTACK::Update (AIJOB vt slot 10): Sly's attack. It ends (-1) when Sly is reacting to damage or the enemy is
 * gone (inactive, or its +0x330 set). Otherwise by the enemy's xy distance: 0 approach slowly; within 450 and facing it
 * (within acos 0.8) a cane strike (2), or 30% of the time a jump (3); 1 approach beyond 550, back to 0 within 400;
 * 2 the strike, over when Sly's mode (+0x18D8) ends; 3 the jump: over on landing, or the dive (4) 0.2 s into its rise
 * (jump state 1); 4 the dive, over when Sly leaves state 13. Layout: SafeHouse port (actorai.cpp JOBSLYATTACK). */
struct SLY {
    /* 0x0000 */ char pad[0x2DC];
    /* 0x02dc */ int stJump;      /* jump.state (-1 none, 1 rising) */
    /* 0x02e0 */ float tJump;     /* jump.t20: the jump state's start */
    /* 0x02e4 */ char pad2[0xDF4 - 0x2E4];
    /* 0x0df4 */ int stDamage;    /* the damage reaction's state (SafeHouse nSubDF4; -1 none) */
    /* 0x0df8 */ char pad3[0x18C8 - 0xDF8];
    /* 0x18c8 */ int state;       /* field: SafeHouse port (SLY state; 13 the dive) */
    /* 0x18cc */ char pad4[0x18D8 - 0x18CC];
    /* 0x18d8 */ int mode;        /* field: SafeHouse port (SLY mode; -1 none) */
};
struct GUARD { char pad[0x330]; int f330; };   /* the enemy (SafeHouse GUARD f330: out of the fight) */
struct JOBSLYATTACK {
    /* 0x00 */ char pad[0x10];
    /* 0x10 */ struct SLY *pactor;      /* field: SafeHouse port (AIJOB) */
    /* 0x14 */ char pad2[0x30 - 0x14];
    /* 0x30 */ int st;                  /* field: SafeHouse port */
    /* 0x34 */ float tSt;               /* field: SafeHouse port */
    /* 0x38 */ struct GUARD *ploEnemy;  /* field: SafeHouse port */
};
#define SLYST_Dive 13
#include "clock.h"
extern qword D_002A2DA0;   /* (1, 0, 0): the direction when the enemy is on top */
extern float D_002BD360;   /* 450: close enough to strike */
extern float D_002BD368;   /* 400: approached */
extern float D_002BD36C;   /* 550: too far */
extern float D_002BD370;   /* 0.2: the rise before the dive */
void Update__5AIJOB(struct JOBSLYATTACK *pjob);
int FLoActive__FP2LO(struct GUARD *plo);
qword PosOfLo__FP2LO(void *p);
struct M3 *MatJtLo__FP2LO(void *p);
void SetState__12JOBSLYATTACKi(struct JOBSLYATTACK *pjob, int st);
float GRandInRange__Fff(float gMin, float gMax);

static __inline__ float Dot(qword a, qword b)
{
    qword r, t;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(r), "=j"(t) : "j"(a), "j"(b));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(r));
    return g;
}

static __inline__ float SafeNormalize(qword *pv, qword *pvDefault)
{
    register qword v __asm__("vf3") = *pv;
    qword t, l;
    float g;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(t), "=j"(l) : "j"(v));
    __asm__("vsqrt Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "=j"(l) : "j"(t), "0"(l));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(l));
    if (g < 0.0001f)
        *pv = *pvDefault;
    else
    {
        qword r;
        __asm__("vdiv Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, Q" : "=&j"(r) : "j"(l), "j"(v));
        *pv = r;
    }
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(l));
    return g;
}

// name: SafeHouse port (JOBSLYATTACK::Update)
void Update__12JOBSLYATTACK(struct JOBSLYATTACK *pjob)
{
    union { qword q; float f[4]; } d;   /* the enemy's xy direction */
    float g;   /* its xy distance */
    int stOld;
    Update__5AIJOB(pjob);
    if (pjob->st == -1)
        return;
    if (pjob->pactor->stDamage != -1 || !FLoActive__FP2LO(pjob->ploEnemy) || pjob->ploEnemy->f330) {
        SetState__12JOBSLYATTACKi(pjob, -1);
        return;
    }
    {
        qword a = PosOfLo__FP2LO(pjob->ploEnemy);
        qword b = PosOfLo__FP2LO(pjob->pactor);
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(d.q) : "j"(a), "j"(b));
        d.f[2] = 0.0f;
        g = SafeNormalize(&d.q, &D_002A2DA0);
    }
    do {
        stOld = pjob->st;
        switch (stOld) {
        case 0:
            if (g < D_002BD360) {
                struct M3 *pm = MatJtLo__FP2LO(pjob->pactor);
                if (0.8f < Dot(pm->r[0], d.q)) {
                    if (GRandInRange__Fff(0.0f, 1.0f) < 0.3f)
                        SetState__12JOBSLYATTACKi(pjob, 3);
                    else
                        SetState__12JOBSLYATTACKi(pjob, 2);
                }
            } else if (D_002BD36C < g) {
                SetState__12JOBSLYATTACKi(pjob, 1);
            }
            break;
        case 1:
            if (g < D_002BD368)
                SetState__12JOBSLYATTACKi(pjob, 0);
            break;
        case 2:
            if (pjob->pactor->mode == -1 && 0.1f < g_clock.t - pjob->tSt)
                SetState__12JOBSLYATTACKi(pjob, -1);
            break;
        case 3: {
            float t = g_clock.t;
            if (0.1f < t - pjob->tSt) {
                struct SLY *psly = pjob->pactor;
                if (psly->stJump != -1) {
                    if (psly->stJump == 1 && D_002BD370 < t - psly->tJump)
                        SetState__12JOBSLYATTACKi(pjob, 4);
                } else
                    SetState__12JOBSLYATTACKi(pjob, -1);
            }
            break;
        }
        case 4:
            if (0.1f < g_clock.t - pjob->tSt && pjob->pactor->state != SLYST_Dive)
                SetState__12JOBSLYATTACKi(pjob, -1);
            break;
        }
    } while (pjob->st != stOld);
}
