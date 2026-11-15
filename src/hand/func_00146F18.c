typedef int qword __attribute__((mode(TI)));
/* JOBMURRAYRAGE::Update (AIJOB vt slot 10): Murray's rage. In the charge's wind-up (0) he faces Sly and keeps that
 * heading; in the charge (1) he turns toward Sly at 15 rad/s at most, while Sly is within 0.5 rad of the heading the
 * charge started on. Layout: SafeHouse port (actorai.h JOBMURRAYRAGE, actorai.cpp). */
struct MURRAY {
    /* 0x0000 */ char pad[0x1A8];
    /* 0x01a8 */ float radHeading;   /* the step's heading */
    /* 0x01ac */ char pad2[0x1840 - 0x1AC];
    /* 0x1840 */ int n1840;          /* field: SafeHouse port - the charge's phase (0 wind-up, 1 charge) */
};
struct JOBMURRAYRAGE {
    /* 0x00 */ char pad[0x10];
    /* 0x10 */ struct MURRAY *pactor;   /* field: SafeHouse port (AIJOB) */
    /* 0x14 */ char pad2[0x30 - 0x14];
    /* 0x30 */ float radCharge;         /* field: SafeHouse port - the heading the charge started on */
};
#include "clock.h"
extern void *D_002E1E40;   /* Sly (the first object of class 0x35 that is not a clone) */
extern float D_002BD374, D_002BD378;   /* 0.5 rad: Sly ahead; 15 rad/s: the turn */
void Update__5AIJOB(struct JOBMURRAYRAGE *pjob);
qword PosOfLo__FP2LO(void *p);
void SetStepPhysHeadingToward__FP3ALOG9VU_VECTOR(struct MURRAY *pmurray, qword vec);
float atan2f(float y, float x);
float RadNormalize__Ff(float rad);
float RadStepHeading__FP4STEP(struct MURRAY *pmurray);
float GLimitAbs(float g, float gLimit) asm("GLimitAbs__Fff");
void SetStepPhysHeading__FP3ALOf(struct MURRAY *pmurray, float rad);
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
// name: SafeHouse port (JOBMURRAYRAGE::Update)
void Update__13JOBMURRAYRAGE(struct JOBMURRAYRAGE *pjob)
{
    Update__5AIJOB(pjob);
    switch (pjob->pactor->n1840) {
    case 0:
        if (D_002E1E40) {
            qword a, b, d;
            a = PosOfLo__FP2LO(D_002E1E40);
            b = PosOfLo__FP2LO(pjob->pactor);
            __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
            SetStepPhysHeadingToward__FP3ALOG9VU_VECTOR(pjob->pactor, d);
        }
        pjob->radCharge = pjob->pactor->radHeading;
        break;
    case 1:
        if (D_002E1E40) {
            qword a, b, d;
            float rad, radCur;   /* toward Sly, the current heading */
            a = PosOfLo__FP2LO(D_002E1E40);
            b = PosOfLo__FP2LO(pjob->pactor);
            __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
            rad = atan2f(GetY(d), GetX(d));
            if (__builtin_fabsf(RadNormalize__Ff(rad - pjob->radCharge)) < D_002BD374) {
                radCur = RadStepHeading__FP4STEP(pjob->pactor);
                { float drad = RadNormalize__Ff(rad - radCur); float dt = g_clock.dt; float svrad = D_002BD378; SetStepPhysHeading__FP3ALOf(pjob->pactor, radCur + GLimitAbs(drad, svrad * dt)); }
            }
        }
        break;
    }
}
