/* MATCH (Claude agent laneB18, 2026-10-23): case 5 uses LenXY5, which adds allocation-only "r"(ppadctl) on the vsqrt asm and two "r"(pasega1030) on the qmfc2 asm (one "r"(pasega1030): 5). One register pin (MulT vf3). */
/* UpdateBentley: the actor update; then, in the world, the jump targets, the binoculars and the transitions, and the
 * state's own update: standing (the look mask; the log idle +0x181C keeps a heading), walking / running (the stick's
 * heading, the gait mixed by the stick), the jump, the interaction, near a target (state 5) and the mine (6, n16B0 1)
 * moving by the root blend and the stick, the animation-driven states (10 / 11 / 14) pulling the root's velocity,
 * the damage, the support. Layout: SafeHouse port (gang.h BENTLEY, actor.h ACTOR); offset names where SafeHouse has none. */
/* v6 (Claude agent laneB16, 2026-10-23): aligned 7 -> 1. Case 11 uses PullB: qmtc2 into a plain qword t, then VOLATILE stores pbentley->vel = r and u.q = t (keeps the vel store before the u store in sched1, so u lives longer and local-alloc gives r vf1 / u vf2 like the target; the lw pasega1030 now hoists too). Cases 10/14 keep Pull (their target order differs). Left: case 5 lw ppadctl before the LenXY vmul. */
/* v5 (Claude agent laneB11, 2026-10-23): aligned 16 -> 7. MulT: r pinned to vf3 (one commented pin) + inputs (r[1], r[2]) order. Left: case 5 LenXY lw ppadctl after vaddy (target before vmul), case 11 Pull: lw pasega1030 / u vs r VF swap (vf1/vf2) and sqc2 order. */
/* v4 (Claude agent, laneB5, 2026-10-23): aligned 17 -> 16. LenXY as asm1 = vmul.xy+vaddy.x fused, asm2 = vsqrt+vwaitq+vaddq.x (fixes case 6 lw pasega1030 placement). Case 5 lw ppadctl still after vmul. MulT r[0] vf1 (target vf3): "=j"(r)+"0"(r[0]) last, r[1]/r[2] operand swaps, r0 local: no change (16-17). Pull by-value VF helpers: 30. */
/* v3 (Claude agent, laneB4, 2026-10-23): aligned 37 -> 17. LenXY as two asms: vmul.xy alone, then vaddy.x+vsqrt+vwaitq+vaddq.x fused (fixes the extra-instruction offset). */
/* v2 (Claude agent, 2026-10-23): aligned 42 -> 37. MulT asm operand order: outputs (r, one, t0, t1, t2), inputs (v, r[2], r[1]) gives the target's temp VF numbers (t0 vf7, one vf8, t1 vf6, t2 vf5). Left: r = r[0] lands in vf1 (target vf3; "0"(r[0]) tie same), LenXY: target loads ppadctl before the vmul and pasega1030 after vaddq (fused LenXY asm worse, 46-54), the mtc1/add.s nop in case 6. */
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VUF;
struct M3 { qword r[3]; };
struct LM { float gMin; float gMax; };
struct POLY { float a; float b; float c; };
struct PADCTL { char pad[0x18]; float radStick; float uStick; };   /* the stick's direction and deflection */
struct ASEGA { char pad[0x1C]; float t; char pad20[0x20]; float svt; };   /* field: SafeHouse port (asega.h) */
struct BENTLEY {
    char pad0[0x28]; unsigned long grf; char pad30[0x150 - 0x30]; struct PADCTL *ppadctl; char pad154[0x190 - 0x154];
    qword vel; char pad1A0[8]; float radHeading; char pad1AC[4]; struct M3 matOrient; char pad1E0[0x2C0 - 0x1E0];
    char jump[0x4C0 - 0x2C0]; char interact[0xDF0 - 0x4C0]; char damage[0x1030 - 0xDF0]; struct ASEGA *pasega1030; int psma1034;
    int n1038; char pad103C[0x10DC - 0x103C]; int ploTarget; char pad10E0[0x1320 - 0x10E0]; char gaitWalk[0x13D0 - 0x1320];
    int state; char pad13D4[0x13E0 - 0x13D4]; char rb13E0[0x1410 - 0x13E0]; qword v1410; char pad1420[0x14E0 - 0x1420];
    int pblRb13E0; char pad14E4[0x14F0 - 0x14E4]; char rb14F0[0x1520 - 0x14F0]; qword v1520; char pad1530[0x15F0 - 0x1530];
    int pblRb14F0; char pad15F4[0x1600 - 0x15F4]; char gaitRun[0x16B0 - 0x1600]; int n16B0; char pad16B4[0x181C - 0x16B4]; int f181C;
};
#include "clock.h"
extern char g_sw[];
extern struct LM g_lmZeroOne;
extern struct POLY D_002BC940;
extern struct POLY D_002BC950;
extern float D_002BC960;
extern float D_002BC934;
void UpdateActor(struct BENTLEY *pbentley) asm("UpdateActor__FP5ACTOR");
void UpdateJtCandidates__FP5ACTORP10STEPPLAYERUi(void *pv, struct BENTLEY *pbentley, int n);
void UpdateBentleyBinoc__FP7BENTLEY(struct BENTLEY *pbentley);
void UpdateBentleyTransitions__FP7BENTLEY(struct BENTLEY *pbentley);
void SetStepPhysHeading__FP3ALOf(struct BENTLEY *pbentley, float g);
int GrfActorLookMask__FP5ACTOR(struct BENTLEY *pbentley);
void SetSmaMask__FP3SMAUi(int a, int b);
void SetGaitMix__FP4GAITf(void *pv, float g);
void UpdateGaitFeet__FP4GAIT(void *pv);
void UpdateJumpInput__FP4JUMP(void *pv);
void UpdateInteract__FP5ACTOR(void *pv);
void FaceObject__FP5ACTORP2LO(struct BENTLEY *pbentley, int n);
qword SetVectorCylind__Ffff(float a, float b, float c);
void SteerRootBlend__FP5ACTORP9ROOTBLENDPv(struct BENTLEY *pbentley, void *pv, int n);
qword VelActorAnimRoot__FP5ACTORPvf(struct BENTLEY *pbentley, struct ASEGA *px, float g);
void SetAsegaSpeed(struct ASEGA *px, float g) asm("SetAsegaSpeed__FP5ASEGAf");
float RadNormalize__Ff(float g);
float GLimitAbs(float g, float dg) asm("GLimitAbs__Fff");
void UpdateActorSupport__FP5ACTOR(struct BENTLEY *pbentley);
void UpdateDamage__FP5ACTOR(void *pv);

static __inline__ float GEval(struct POLY *pp, float t) { return pp->a + t * (pp->b + t * pp->c); }
static __inline__ float GClamp(float g, struct LM *plm)
{
    float lo = plm->gMin;
    float hi = plm->gMax;
    if (g < lo) return lo;
    if (hi < g) return hi;
    return g;
}
static __inline__ float LenXY(qword v)
{
    qword l;
    float g;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(l) : "j"(v));
    __asm__("vsqrt Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "=j"(l) : "j"(l));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(l));
    return g;
}
static __inline__ float LenXY5(qword v, struct PADCTL *ppadctl, struct ASEGA *pasega)
{
    qword l;
    float g;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(l) : "j"(v));
    __asm__("vsqrt Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "=j"(l) : "j"(l), "r"(ppadctl));  /* allocation-only "r"(ppadctl): raises the lw ppadctl sched priority so it issues before the vmul */
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(l), "r"(pasega), "r"(pasega));  /* allocation-only "r"(pasega) x2: raises pasega1030's local-alloc priority above ppadctl (pasega1030 $v0, ppadctl $v1) */
    return g;
}
static __inline__ qword MulT(struct M3 *pm, qword v)
{
    register qword r __asm__("vf3");  /* register pin: VF allocation tie, target keeps the result in vf3 */
    qword t0, t1, t2, one;
    r = pm->r[0];
    __asm__("vmul.xyzw %2, %0, %5\n\tvmaxw.xyzw %1, $vf0, $vf0w\n\tvmul.xyzw %3, %6, %5\n\tvmul.xyzw %4, %7, %5\n\tvadday.x $ACC, %2, %2y\n\tvmaddz.x %0, %1, %2z\n\tvaddax.y $ACC, %3, %3x\n\tvmaddz.y %0, %1, %3z\n\tvaddax.z $ACC, %4, %4x\n\tvmaddy.z %0, %1, %4y"
            : "+j"(r), "=&j"(one), "=&j"(t0), "=&j"(t1), "=&j"(t2) : "j"(v), "j"(pm->r[1]), "j"(pm->r[2]));
    return r;
}
static __inline__ void SetVel(struct BENTLEY *pbentley, qword v, void *pv, int n)
{
    pbentley->vel = v;
    pbentley->vel = MulT(&pbentley->matOrient, v);
    pbentley->n1038 = -1;
    SteerRootBlend__FP5ACTORP9ROOTBLENDPv(pbentley, pv, n);
}
static __inline__ void Pull(struct BENTLEY *pbentley)
{
    VUF u;
    qword v = VelActorAnimRoot__FP5ACTORPvf(pbentley, pbentley->pasega1030, pbentley->pasega1030->t);
    qword r;
    __asm__("qmtc2.ni %1, %0" : "=j"(u.q) : "r"(-1.0f));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(u.q));
    pbentley->vel = r;
}
static __inline__ void PullB(struct BENTLEY *pbentley)
{
    VUF u;
    qword v = VelActorAnimRoot__FP5ACTORPvf(pbentley, pbentley->pasega1030, pbentley->pasega1030->t);
    qword r, t;
    __asm__("qmtc2.ni %1, %0" : "=j"(t) : "r"(-1.0f));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(t));
    *(volatile qword *)&pbentley->vel = r;
    *(volatile qword *)&u.q = t;
}
static __inline__ void Kick(void *pv, float g)
{
    SetGaitMix__FP4GAITf(pv, g);
    UpdateGaitFeet__FP4GAIT(pv);
}

// name: SafeHouse port (UpdateBentley)
void UpdateBentley__FP7BENTLEY(struct BENTLEY *pbentley)
{
    UpdateActor(pbentley);
    if (((pbentley->grf >> 60) & 1) == 0)
        return;
    UpdateJtCandidates__FP5ACTORP10STEPPLAYERUi(g_sw, pbentley, 0xF8FE);
    UpdateBentleyBinoc__FP7BENTLEY(pbentley);
    UpdateBentleyTransitions__FP7BENTLEY(pbentley);
    switch (pbentley->state) {
    case 0:
        if (pbentley->f181C) {
            SetStepPhysHeading__FP3ALOf(pbentley, D_002BC934);
            break;
        }
        SetSmaMask__FP3SMAUi(pbentley->psma1034, GrfActorLookMask__FP5ACTOR(pbentley));
        break;
    case 1:
        SetStepPhysHeading__FP3ALOf(pbentley, pbentley->ppadctl->radStick);
        Kick(pbentley->gaitWalk, 1.0f);
        break;
    case 7:
        SetStepPhysHeading__FP3ALOf(pbentley, pbentley->ppadctl->radStick);
        Kick(pbentley->gaitRun, pbentley->ppadctl->uStick);
        break;
    case 2:
        UpdateJumpInput__FP4JUMP(pbentley->jump);
        break;
    case 3:
        UpdateInteract__FP5ACTOR(pbentley->interact);
        break;
    case 4:
    case 8:
    case 9:
    case 12:
    case 13:
        break;
    case 5:
        FaceObject__FP5ACTORP2LO(pbentley, pbentley->ploTarget);
        {
            struct PADCTL *ppadctl = pbentley->ppadctl;
            struct ASEGA *pasega = pbentley->pasega1030;
            SetVel(pbentley, SetVectorCylind__Ffff(ppadctl->radStick + 3.1415927f, ppadctl->uStick * LenXY5(pbentley->v1410, ppadctl, pasega) * pasega->svt, 0.0f), pbentley->rb13E0, pbentley->pblRb13E0);
        }
        break;
    case 6:
        if (pbentley->n16B0 == 1) {
            float g0 = GClamp(GEval(&D_002BC940, pbentley->ppadctl->uStick), &g_lmZeroOne);
            float g1 = GClamp(GEval(&D_002BC950, pbentley->ppadctl->uStick), &g_lmZeroOne);
            float z = 0.0f;
            if (z < pbentley->ppadctl->uStick) {
                float d = RadNormalize__Ff(pbentley->ppadctl->radStick - pbentley->radHeading);
                SetStepPhysHeading__FP3ALOf(pbentley, pbentley->radHeading + GLimitAbs(d, g1 * D_002BC960 * g_clock.dt));
            }
            SetVel(pbentley, SetVectorCylind__Ffff(pbentley->ppadctl->radStick + 3.1415927f, g0 * LenXY(pbentley->v1520) * pbentley->pasega1030->svt, z), pbentley->rb14F0, pbentley->pblRb14F0);
        }
        break;
    case 10:
        Pull(pbentley);
        break;
    case 11:
        PullB(pbentley);
        SetAsegaSpeed(pbentley->pasega1030, pbentley->ppadctl->uStick);
        SetStepPhysHeading__FP3ALOf(pbentley, pbentley->ppadctl->radStick);
        break;
    case 14:
        Pull(pbentley);
        SetStepPhysHeading__FP3ALOf(pbentley, pbentley->ppadctl->radStick);
        break;
    }
    UpdateActorSupport__FP5ACTOR(pbentley);
    UpdateDamage__FP5ACTOR(pbentley->damage);
}
