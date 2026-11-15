/* SetBentleySubMode: the square's swing (-1 none, 0..2 by the state): a new swing from none picks a target point
 * (mask 2, near the sub's vector 0.15 s ahead, within 1.5 rad of the heading, 3.15 for mode 0) whose height within
 * [+0x30, +0x34] weights the pair of clips (0.5 without a target), the side of +0xE4 chooses the pair, and mode 0 turns
 * Bentley toward the target; the blend applied over the swing (seeking, 1/15 s), its hand record demoted after the
 * release (+0x10). Layout: SafeHouse port (gang.cpp SetBentleySubMode, gang.h BENTLEYSUB). */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float a[4]; } QF;
struct BENTLEY { char pad[0x1A8]; float radHeading; char pad1[0x10B8 - 0x1AC]; int pxf10B8; };   /* field: SafeHouse port */
struct BLENDE { float g0; int pad[2]; float g1; int pad2[2]; void *pbl; };   /* a blend of two: the two weights (+0, +0xC), the blend */
struct BENTLEYSUB { struct BENTLEY *pbentley; int state; int n8; int nC; int n10; int n14; float t18; float g1C; char v20[0x10]; float g30; float g34;
    struct BLENDE ae[6]; char pad[0xE0 - 0x38 - 6 * 28]; void *pasega; void *ploE4; };   /* field: SafeHouse port (gang.h BENTLEYSUB) */
#include "clock.h"
extern qword D_002A2DD0;
void ChooseAttackTarget__FP5ACTORfUifP6VECTORPvPG9VU_VECTORf(struct BENTLEY *, int, void *, int *, QF *, float, float, float);
qword ConvertPos__FP2LOT0G9VU_VECTOR(void *, struct BENTLEY *, qword);
void SetStepPhysHeadingToward__FP3ALOG9VU_VECTOR(struct BENTLEY *, qword);
void TurnActorNow__FP5ACTOR(struct BENTLEY *);
void RecalcBlend__FP6ASEGBL(void *);
void ApplyAsegCur(void *, struct BENTLEY *, int, void **, float, float) asm("ApplyAsegCur__FP4ASEGP3ALOffiPP5ASEGA");
void DemoteAsegaOnXf__FiiP2XF(void *, struct BENTLEY *, int);
void SetAsegaSeekTime__FP5ASEGAf(void *, float);
static __inline__ float Clamp(float radRange, float gMin, float gMax)
{
    if (radRange < gMin)
        return gMin;
    if (gMax < radRange)
        return gMax;
    return radRange;
}
// name: SafeHouse port (SetBentleySubMode)
void SetBentleySubMode__FP7BENTLEYi(struct BENTLEYSUB *psub, int state)
{
    void *pbl;
    float dt;
    if (state == psub->state)
        return;
    if (psub->state == -1) {
        int fTarget;
        QF posTarget;
        QF r;
        float radRange;
        psub->t18 = g_clock.t;
        psub->nC = 0;
        psub->n10 = 0;
        psub->n14 = 0;
        radRange = 1.5f;
        if (state == 0)
            radRange = 3.15f;
        ChooseAttackTarget__FP5ACTORfUifP6VECTORPvPG9VU_VECTORf(psub->pbentley, 2, psub->v20, &fTarget, &posTarget, psub->pbentley->radHeading, 0.15f, radRange);
        if (fTarget) {
            psub->g1C = Clamp((posTarget.a[2] - psub->g30) / (psub->g34 - psub->g30), 0.0f, 1.0f);
        } else {
            psub->g1C = 0.5f;
        }
        r.q = ConvertPos__FP2LOT0G9VU_VECTOR(psub->ploE4, psub->pbentley, D_002A2DD0);
        psub->n8 = 0.0f < r.a[1] ? 1 : 0;
        if (state == 0 && fTarget) {
            SetStepPhysHeadingToward__FP3ALOG9VU_VECTOR(psub->pbentley, posTarget.q);
            TurnActorNow__FP5ACTOR(psub->pbentley);
        }
    }
    psub->state = state;
    dt = 0.0f;
    switch (state) {
    case -1:
        pbl = 0;
        break;
    case 0:
    case 1:
    case 2: {
        struct BLENDE *pblende = &psub->ae[state * 2 + psub->n8];
        pblende->g0 = 1.0f - psub->g1C;
        pbl = pblende->pbl;
        pblende->g1 = psub->g1C;
        dt = 0.06666667f;
        RecalcBlend__FP6ASEGBL(pbl);
        break;
    }
    }
    ApplyAsegCur(pbl, psub->pbentley, 1, &psub->pasega, g_clock.t - psub->t18, 1.0f);
    if (!psub->pasega)
        return;
    if (psub->n10)
        DemoteAsegaOnXf__FiiP2XF(psub->pasega, psub->pbentley, psub->pbentley->pxf10B8);
    if (psub->pasega && dt != 0.0f)
        SetAsegaSeekTime__FP5ASEGAf(psub->pasega, g_clock.t + dt);
}
