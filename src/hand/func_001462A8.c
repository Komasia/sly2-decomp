/* JOBBENTLEYATTACK::Update (AIJOB vt slot 10): Bentley's attack, as Murray's with his own ranges. It ends (-1) when
 * Bentley is reacting to damage or the enemy is gone (inactive, or its +0x330 set). Otherwise by the enemy's xy
 * distance: 0 approach slowly, swinging (2) once within 350 and facing it (within acos 0.8), or 1 approach once beyond
 * 350, back to 0 within 250; 2 swing, ending when his swing (the sub-object state +0x1714) is over, 0.1 s on.
 * Layout: SafeHouse port (actorai.cpp JOBBENTLEYATTACK::Update). */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
#include "clock.h"
extern float D_002BD350;   /* 350: close enough to swing */
extern struct { float sNear; float sFar; } D_002BD358;   /* 250 / 350: the approach range */
extern qword D_002A2DA0;   /* (1, 0, 0): the direction when the enemy is on top */
struct GUARD { char pad[0x330]; int f330; };   /* the enemy (SafeHouse GUARD f330: out of the fight) */
struct BENTLEY {
    /* 0x0000 */ char pad[0xDF4];
    /* 0x0df4 */ int stDamage;    /* the damage reaction's state (SafeHouse nSubDF4; -1 none) */
    /* 0x0df8 */ char pad2[0x1714 - 0xDF8];
    /* 0x1714 */ int stSub;       /* the sub-object's state (SafeHouse BENTLEY sub.state: his swing, -1 over) */
};
struct JOBBENTLEYATTACK {
    /* 0x00 */ char pad[0x10];
    /* 0x10 */ struct BENTLEY *pactor;  /* field: SafeHouse port (AIJOB) */
    /* 0x14 */ char pad2[0x30 - 0x14];
    /* 0x30 */ int st;                  /* field: SafeHouse port */
    /* 0x34 */ float tSt;               /* field: SafeHouse port */
    /* 0x38 */ struct GUARD *ploEnemy;  /* field: SafeHouse port */
};
void Update__5AIJOB(struct JOBBENTLEYATTACK *pjob);
int FLoActive__FP2LO(struct GUARD *plo);
qword PosOfLo__FP2LO(void *);
qword *MatJtLo__FP2LO(void *);
void SetState__16JOBBENTLEYATTACKi(struct JOBBENTLEYATTACK *pjob, int st);

// name: SafeHouse port (JOBBENTLEYATTACK::Update)
void Update__16JOBBENTLEYATTACK(struct JOBBENTLEYATTACK *pjob)
{
    VU d;   /* the enemy's xy direction */
    qword a, b, c, l, one, n;
    float g;   /* its xy distance */
    Update__5AIJOB(pjob);
    if (pjob->st == -1)
        return;
    if (pjob->pactor->stDamage != -1 || !FLoActive__FP2LO(pjob->ploEnemy) || pjob->ploEnemy->f330) {
        SetState__16JOBBENTLEYATTACKi(pjob, -1);
        return;
    }
    a = PosOfLo__FP2LO(pjob->ploEnemy);
    b = PosOfLo__FP2LO(pjob->pactor);
    { qword *pk = &D_002A2DA0;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(c) : "j"(a), "j"(b));
    d.q = c;
    d.f[2] = 0.0f;
    {
        register qword l1 __asm__("vf1");
        register qword r2 __asm__("vf2");
        float gl;
        __asm__("vmul.xyz %0, %1, %1" : "=j"(l1) : "j"(d.q));
        __asm__("vaddw.x %0, $vf0, $vf0w\n\tvadday.x ACC, %1, %1y\n\tvmaddz.x %1, %0, %1z" : "=&j"(r2), "+j"(l1));
        __asm__("vsqrt Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "=j"(r2) : "j"(l1));
        l = r2;
        __asm__("qmfc2.ni %0, %1" : "=r"(gl) : "j"(l));
        if (gl < 1e-4f) {
        d.q = *pk;
    } else {
        __asm__("vdiv Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, Q" : "=j"(n) : "j"(d.q), "j"(l));
        d.q = n;
    }
    }
    }
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(l)); /* gcc emits the qmfc2 and schedules it */
    for (;;) {
        int stOld = pjob->st;
        switch (stOld) {
        case 0:
            if (g < D_002BD350) {
                qword *pm = MatJtLo__FP2LO(pjob->pactor);
                register qword t __asm__("vf2");
                qword one2;
                float dot;   /* the facing along the direction */
                t = *pm;
                __asm__("vmul.xyz %0, %0, %1" : "+j"(t) : "j"(d.q));
                __asm__("vaddw.x %0, $vf0, $vf0w\n\tvadday.x ACC, %1, %1y\n\tvmaddz.x %1, %0, %1z" : "=&j"(one2), "+j"(t));
                __asm__("qmfc2.ni %0, %1" : "=r"(dot) : "j"(t));
                if (0.8f < dot)
                    SetState__16JOBBENTLEYATTACKi(pjob, 2);
            } else if (D_002BD358.sFar < g) {
                SetState__16JOBBENTLEYATTACKi(pjob, 1);
            }
            break;
        case 1:
            if (g < D_002BD358.sNear)
                SetState__16JOBBENTLEYATTACKi(pjob, 0);
            break;
        case 2:
            if (pjob->pactor->stSub == -1 && 0.1f < g_clock.t - pjob->tSt)
                SetState__16JOBBENTLEYATTACKi(pjob, -1);
            break;
        }
        if (pjob->st == stOld)
            break;
    }
}
