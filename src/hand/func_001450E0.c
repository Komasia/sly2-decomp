typedef int qword __attribute__((mode(TI)));
typedef unsigned long ulong;
/* JOBCOMPANION::FindEnemy: the companion's best enemy: of the guards in the actor's target record and then the
 * followed object's (scored +200), those not in states 7 / 0x10 / 0x16 / 0x17 / 0x2A / 0x2B, the one with the lowest
 * score - the distance from the followed object, favouring the current enemy (-200 + 0.8 d) and guards in state 3
 * (-400). Layout: SafeHouse port (actorai.cpp FindEnemy, target.h TARGETREC). */
/* a quadratic g0 + g1 x + g2 x^2 (Sly 1 CLQ) */
struct CLQ { float g0, g1, g2, gPad; };
struct GUARD { char pad[0x2C0]; ulong grfState; };      /* +0x2C0 the guard's state bits */
/* the guards targeting an object (SafeHouse target.h TARGETREC) */
struct TARGETREC { char pad[0x28]; int cguard; struct GUARD *apguard[1]; };
struct ACTOR { char pad[0x1088]; struct TARGETREC *ptargetrec; };
struct JOBCOMPANION {
    /* 0x00 */ char pad[0x10];
    /* 0x10 */ struct ACTOR *pactor;     /* field: SafeHouse port (AIJOB) */
    /* 0x14 */ char pad2[0x30 - 0x14];
    /* 0x30 */ void *ploFollow;          /* field: SafeHouse port */
    /* 0x34 */ char pad3[0x90 - 0x34];
    /* 0x90 */ struct GUARD *ploEnemy;   /* field: SafeHouse port */
};
extern float D_002A4E30;          /* FLT_MAX */
extern struct CLQ D_002BD300;     /* the current enemy: -200 + 0.8 d */
extern struct CLQ D_002BD310;     /* a guard of the followed object's: 200 + d */
extern struct CLQ D_002BD320;     /* a guard in state 3: -400 + d */
qword PosOfLo__FP2LO(void *p);
ulong func_00207A20(int st);   /* the bit of a guard state (SafeHouse GrfStateBit) */
int FGuardState(struct GUARD *pguard, int st) asm("FGuardState__FP5GUARDi");
struct TARGETREC *func_001F8240(void *plo);   /* an object's target record (SafeHouse PtargetrecFind) */

static __inline__ float GDist(qword a, qword b)
{
    qword d, t;
    float g;   /* the score */
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xyz %0, %0, %0\n"
        "vaddw.x %1, $vf0, $vf0w\n"
        "vadday.x ACC, %0, %0y\n"
        "vmaddz.x %0, %1, %0z" : "+j"(d), "=j"(t));
    __asm__("vsqrt Q, %0x\n"
        "vwaitq\n"
        "vaddq.x %0, $vf0, Q" : "+j"(d));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    return g;
}
static __inline__ float GFromClq(float g, struct CLQ *pclq) { return pclq->g0 + g * (pclq->g1 + g * pclq->g2); }

// name: SafeHouse port (JOBCOMPANION::FindEnemy)
struct GUARD *FindEnemy__12JOBCOMPANION(struct JOBCOMPANION *pjob)
{
    struct GUARD *pguardBest = 0;
    float gBest = D_002A4E30;
    qword pos;
    ulong grfSkip;
    struct TARGETREC *ptargetrec;
    int i;
    PosOfLo__FP2LO(pjob->pactor);
    pos = PosOfLo__FP2LO(pjob->ploFollow);
    grfSkip = func_00207A20(7) | func_00207A20(0x10) | func_00207A20(0x16) | func_00207A20(0x17) |
          func_00207A20(0x2A) | func_00207A20(0x2B);
    ptargetrec = pjob->pactor->ptargetrec;
    for (i = 0; i < ptargetrec->cguard; i++) {
        struct GUARD *pguard = ptargetrec->apguard[i];
        float g;   /* the score */
        if (grfSkip & pguard->grfState)
            continue;
        g = GDist(pos, PosOfLo__FP2LO(pguard));
        if (pguard == pjob->ploEnemy)
            g = GFromClq(g, &D_002BD300);
        if (FGuardState(pguard, 3))
            g = GFromClq(g, &D_002BD320);
        if (g < gBest) {
            pguardBest = pguard;
            gBest = g;
        }
    }
    ptargetrec = func_001F8240(pjob->ploFollow);
    if (ptargetrec) {
        for (i = 0; i < ptargetrec->cguard; i++) {
            struct GUARD *pguard = ptargetrec->apguard[i];
            float g;   /* the score */
            if (grfSkip & pguard->grfState)
                continue;
            g = GDist(pos, PosOfLo__FP2LO(pguard));
            g = GFromClq(g, &D_002BD310);
            if (pguard == pjob->ploEnemy)
                g = GFromClq(g, &D_002BD300);
            if (FGuardState(pguard, 3))
                g = GFromClq(g, &D_002BD320);
            if (g < gBest) {
                pguardBest = pguard;
                gBest = g;
            }
        }
    }
    return pguardBest;
}
