// PlanFollow MATCH (Claude agent for Lilly, T1647, 2026-10-25), from v6 (14).
// Branch 1: VU_FLOAT has a user copy ctor (so the temporary lives at 0x40) and its qmtc2 ctor writes a plain qword
// local first, then copies it into q (an asm output straight into the member goes through a second stack temp).
// Branch 2: the VU_FLOAT is loaded with an asm lw from "m"(f) (VU_FLOATM, as in SetSlyDodgeState), and AddScaled takes
// its operands in (a, s, b) order.
#include "cid.h"
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct M4 { qword r[4]; };
// JOBCOMPANION::PlanFollow: the path to the followed object. Its position is predicted dtPredict ahead (a step: back
// along its velocity in its heading's frame; another object: on by its velocity, in its joint frame), the companion's
// offset added in that frame; then the actor's shared path is a straight line to it (no navigation region), stays on
// the actor (the followed object is in another region, or the search fails) or is the path searched to it; the follow
// job follows it. Layout: SafeHouse port (actorai.h JOBCOMPANION, actorai.cpp PlanFollow).
struct NAVREGION;
struct REGENT { char pad[0x10]; NAVREGION *preg; };          // the actor's navigation region entry
struct SOST { char pad[0xDC]; REGENT *pregent; };
struct CRV { char pad[0xE8]; int cpoint; char pad2[0xF4 - 0xEC]; qword *apos; };   // crv.h: the points
struct ACTOR { char pad[0xE8]; SOST *psost; char pad2[0x294 - 0xEC]; CRV *pcrv; };  // +0x294 the path shared by actor jobs
struct LOFOLLOW;
struct LOFOLLOWVT { char pad[0x108]; short d; short pad2; qword (*pfn)(LOFOLLOW *); };  // vt slot 33: the velocity
// the followed object: a STEP's velocity (+0x190) and heading (+0x1A8)
struct LOFOLLOW { char pad[0xC]; LOFOLLOWVT *pvt; char pad2[0x190 - 0x10]; qword vecVel; char pad3[0x1A8 - 0x1A0]; float radHeading; };
struct JOBCOMPANION {
    char pad[0x10]; ACTOR *pactor; char pad1[4]; void *pchild; char pad2[0x30 - 0x1C]; LOFOLLOW *ploFollow; char pad3[0x40 - 0x34];
    qword offset;      // +0x40 field: SafeHouse port
    qword posFollow;   // +0x50 field: SafeHouse port
    char pad4[0x68 - 0x60];
    float dtPredict;   // +0x68 field: SafeHouse port
};
extern "C" {
extern qword g_normalZ;
qword PosOfLo(void *p) asm("PosOfLo__FP2LO");
M3 *MatJtLo(void *p) asm("MatJtLo__FP2LO");
M3 BuildRotateMatrixAxis(qword axis, float g) asm("BuildRotateMatrixAxis__FP7MATRIX3fG9VU_VECTOR");
int FIsBasicDerivedFrom(void *p, int k) asm("FIsBasicDerivedFrom__FP5BASIC3CID");
NAVREGION *func_00145AA8(JOBCOMPANION *pjob);   // the followed object's region
int FNavPathCrv(NAVREGION *preg, qword posFrom, qword posTo, CRV *pcrv) asm("FNavPathCrv__FP9NAVREGIONiiP3CRV");
void RecalcCrv(CRV *pcrv) asm("RecalcCrv__FP3CRV");
void Follow(void *pjob, CRV *pcrv, int n) asm("Follow__9JOBFOLLOWP3CRVi");
void PlanFollow(JOBCOMPANION *pjob) asm("PlanFollow__12JOBCOMPANION");
}
struct VU_FLOAT { qword q; VU_FLOAT(const VU_FLOAT &s) { q = s.q; } VU_FLOAT(float f) { qword t; __asm__("qmtc2.ni %1, %0" : "=j"(t) : "r"(f)); q = t; } };
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
struct VU_FLOATM { qword q; VU_FLOATM(const float &f) { __asm__("lw %0, %1" : "=r"(q) : "m"(f)); } };

static inline qword AddScaled(VU_VECTOR a, VU_FLOATM s, VU_VECTOR b)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %3, %2x" : "=j"(r) : "j"(a.q), "j"(s.q), "j"(b.q), "j"(s.q)); /* repeated "j"(s.q): allocation-only operand, keeps the lw value VF-class so it is spilled to 0x80 across the call */
    return r;
}

static inline qword AddScaled(VU_VECTOR a, VU_FLOAT s, VU_VECTOR b)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %3, %2x" : "=j"(r) : "j"(a.q), "j"(s.q), "j"(b.q));
    return r;
}

static inline qword MulM3(const M3 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
            : "=j"(r) : "j"(v), "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]));
    return r;
}

static inline qword Add(qword a, qword b)
{
    qword r;
    __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}

// name: SafeHouse port (JOBCOMPANION::PlanFollow)
void PlanFollow(JOBCOMPANION *pjob)
{
    union { M4 m4; struct { M3 m; qword pos; } s; } u;
    pjob->posFollow = PosOfLo(pjob->ploFollow);
    if (FIsBasicDerivedFrom(pjob->ploFollow, CID_STEP)) {
        LOFOLLOW *plo = pjob->ploFollow;
        u.s.m = BuildRotateMatrixAxis(g_normalZ, plo->radHeading);
        u.s.pos = AddScaled(pjob->posFollow, VU_FLOAT(-pjob->dtPredict), MulM3(u.s.m, plo->vecVel));
    } else {
        LOFOLLOW *plo;
        u.s.m = *MatJtLo(pjob->ploFollow);
        plo = pjob->ploFollow;
        u.s.pos = AddScaled(pjob->posFollow, VU_FLOATM(pjob->dtPredict), plo->pvt->pfn((LOFOLLOW *)((char *)plo + plo->pvt->d)));
    }
    u.s.pos = Add(u.s.pos, MulM3(u.s.m, pjob->offset));
    {
        ACTOR *pactor = pjob->pactor;
        CRV *pcrv = pactor->pcrv;
        REGENT *pregent = pactor->psost ? pactor->psost->pregent : 0;
        NAVREGION *preg = pregent ? pregent->preg : 0;
        qword posActor = PosOfLo(pactor);
        if (!preg) {
            pcrv->cpoint = 2;
            pcrv->apos[0] = posActor;
            pcrv->apos[1] = u.s.pos;
            RecalcCrv(pcrv);
        } else if (func_00145AA8(pjob) != preg) {
            FNavPathCrv(preg, posActor, posActor, pcrv);
        } else if (!FNavPathCrv(preg, posActor, u.s.pos, pcrv)) {
            FNavPathCrv(preg, posActor, posActor, pcrv);
        }
        Follow(pjob->pchild, pcrv, 0);
    }
}
