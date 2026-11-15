/* JOBHIT::Enter (0xA0, the base of the hit jobs 0xA1..0xA3): the move starts, the guard turns away from the hit's push
 * (or keeps its facing when there is none, or for a 0x40000 hit), a kind-2 entry gets its landing target behind the
 * guard, the guard's response is cleared, its held noise placed; a hit by the current player (when that is Murray, or for a 0x40000
 * hit) rumbles the pad and jolts the camera shortly after. */
#include "clock.h"
#include "h2_aijobs.h"

struct SW;
struct NOISE;
extern struct SW g_sw;
extern qword D_002A2DD0;                /* a zero vector */
extern float D_002A5584;                /* FLT_MAX */
extern struct LO *D_002F7900;           /* Murray */
extern char g_joy[];

/* the guard's move (+0xFD0); field: SafeHouse port (guard.h MOVEREF) */
struct MOVEREF { struct AIJOB *pjob; int fHeadingLocked; int n8; struct GUARD *pguard; };
struct GUARD {
    /* 0x000 */ char pad0[0x1A8];
    /* 0x1a8 */ float radHeading;       /* field: SafeHouse port (STEP) */
    /* 0x1ac */ char pad1AC[0x334 - 0x1AC];
    /* 0x334 */ int n334;               /* field: SafeHouse port - a player's hits rumble the pad */
    /* 0x338 */ char pad338[0x35C - 0x338];
    /* 0x35c */ struct NOISE *pnoise;   /* field: SafeHouse port - the guard's held noise */
    /* 0x360 */ char pad360[0xF04 - 0x360];
    /* 0xf04 */ int tF04;               /* field: SafeHouse port - the next action's time (cleared) */
    /* 0xf08 */ char padF08[0xFD0 - 0xF08];
    /* 0xfd0 */ struct MOVEREF move;    /* field: SafeHouse port */
};
struct KIND2 { char pad0[0x1C]; float sRoot; };   /* sRoot: field: SafeHouse port (s1C) - the root's distance */
struct KINDE { int k; struct KIND2 *pk2; void *pvState; int grf; };
#define KINDK_Kind2 2

void Enter__7JOBMOVE(JOBHIT *pjob);
float atan2f(float y, float x);
float *MatJtLo__FP2LO(struct GUARD *pguard);
void SetMoveHeading__FP7MOVEREF(struct MOVEREF *pmove, float rad);
float RadNormalize__Ff(float rad);
qword SetVectorCylind__Ffff(float rad, float s, float z);
qword PosOfLo__FP2LO(struct GUARD *pguard);
void SetK2Target__FP6K2PLAYG9VU_VECTOR(void *pk2play, qword pos);
void SetGuardResponse__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(struct GUARD *pguard, int paction, int n, qword vec);
void LockJob__FP5AIJOB(JOBHIT *pjob);
void func_00156C80(struct SW *psw, int fOn, qword pos, struct GUARD *pguard, struct NOISE **ppnoise);
struct LO *PloPlayerPo__FP2SW(struct SW *psw);
int FLoInParentChain__FP2LOT0(struct LO *plo, struct LO *ploParent);
void TriggerJoyRumbleRumk__FP3JOY4RUMKf(void *pjoy, int rumk, float dt);

// name: SafeHouse port (JOBHIT::Enter)
void Enter__6JOBHIT(JOBHIT *pjob) {
    int fPushed;
    float rad;
    struct KINDE *pkinde;
    Enter__7JOBMOVE(pjob);
    {
        /* the push's length (x, y, z) */
        qword d, one, l;
        float g;
        __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(pjob->vec.q));
        __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
        __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(l));
        fPushed = 0;
        if (g > 1.0e-4f) fPushed = pjob->grfKind != 0x40000;
    }
    if (fPushed) {
        rad = atan2f(-pjob->vec.f[1], -pjob->vec.f[0]);
    } else {
        float *mat = MatJtLo__FP2LO(pjob->jobmove.aijob.pguard);
        rad = atan2f(mat[1], MatJtLo__FP2LO(pjob->jobmove.aijob.pguard)[0]);
    }
    SetMoveHeading__FP7MOVEREF(&pjob->jobmove.aijob.pguard->move, rad);
    pkinde = pjob->jobmove.pkinde;
    if (pkinde && pkinde->k == KINDK_Kind2) {
        /* land the root's distance behind the guard */
        qword offset = SetVectorCylind__Ffff(RadNormalize__Ff(pjob->jobmove.aijob.pguard->radHeading + 3.14159274101257324219e+00f), pjob->jobmove.pkinde->pk2->sRoot, 0.0f);
        qword pos = PosOfLo__FP2LO(pjob->jobmove.aijob.pguard);
        qword posTarget;
        __asm__("vadd.xyzw %0, %1, %2" : "=j"(posTarget) : "j"(pos), "j"(offset));
        SetK2Target__FP6K2PLAYG9VU_VECTOR(pjob->jobmove.pkinde->pvState, posTarget);
    }
    SetGuardResponse__FP5GUARDP9ACTIONOBJiG9VU_VECTOR(pjob->jobmove.aijob.pguard, 0, 0, D_002A2DD0);
    if (pjob->jobmove.st == 0) LockJob__FP5AIJOB(pjob);
    func_00156C80(&g_sw, 1, PosOfLo__FP2LO(pjob->jobmove.aijob.pguard), pjob->jobmove.aijob.pguard, &pjob->jobmove.aijob.pguard->pnoise);
    pjob->tJolt = pjob->tEntryHit = D_002A5584;
    pjob->jobmove.aijob.pguard->tF04 = 0;
    if (pjob->jobmove.aijob.pguard->n334) {
        struct LO *ploPlayer = PloPlayerPo__FP2SW(&g_sw);
        if (ploPlayer && FLoInParentChain__FP2LOT0(pjob->psource, ploPlayer) && (ploPlayer == D_002F7900 || (pjob->grfKind & 0x40000))) {
            TriggerJoyRumbleRumk__FP3JOY4RUMKf(g_joy, 3, 1.50000005960464477539e-01f);
            pjob->tJolt = g_clock.t + 5.00000044703483581543e-02f;
        }
        pjob->tEntryHit = g_clock.t + 1.33333340287208557129e-01f;
    }
}
