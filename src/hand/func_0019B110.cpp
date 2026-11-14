// ChooseJumpTarget__FP4JUMPP2LO: chooses the jump target of the player (JTAIR, the family of Lilly's jtair.c: VelJumpLaunch is
// JtPlanLaunchVz). Every candidate list (D_003E13B4..D_003E142C are 12-byte DL heads) is scanned; a candidate is
// scored with MinimizeRange (a 1-D minimizer over the matched func_0019AA58/ABB8/ABF0/AC88/AAB8/AB38 callbacks),
// biased by FUN_001cf138 and checked for a clear path with FJumpPathBlocked unless it is the forced target. The best one
// is published in pstepplayer->pxf (+0xA8 landing time, +0xC0 position, +0xD0 velocity) and SetJumpAnimState starts the
// jump of that kind (9 shapes, 10 curves, 14 hooks, 16 meshes, 18 the partner's target, 15/11 curves, 12/13 shapes).
//
// Notes on the shape of the source (each was needed for the match):
//  - The VECTOR locals are declared together at the top (the frame is in declaration order); the callback contexts are
//    per-loop locals that share 0xA0..0xDF; the address-taken floats get their slots when their address is first taken.
//  - FitJumpToPoint takes VU_VECTOR by value (constructed from the VECTOR locals): the conversion copies make the two
//    small shape loops big enough that loop.c leaves sp+0x50 and the hi of D_002BF8E0 inside them.
//  - `g >= D_002BF8E0` (not `D_002BF8E0 <= g`) everywhere except the 13C0 curves: the operand order decides whether
//    the hi of D_002BF8E0 is hoisted (and later rematerialized by reload in round-robin registers).
//  - The search bounds are the literals -FLT_MAX/FLT_MAX (this function's constant pool at 0x2A65B8).
//  - GMinOf(a, b) = a < b ? a : b comes out as min.s with the operands swapped, so the order varies per loop.
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
#define FLT_MAX 3.40282347e+38f

union VECTOR { qword q; float f[4]; };
struct VU_VECTOR
{
    qword q;
    VU_VECTOR() {}
    VU_VECTOR(qword a) { q = a; }
    VU_VECTOR(const VECTOR &v) { q = v.q; }
};
struct TRI { int itri; float u, v; };

struct SOPHYS { char pad0[0x80]; VECTOR dvGravity; };
struct XF { char pad0[0xA8]; float tGoal; char padAC[0xC0 - 0xAC]; qword posGoal; qword vGoal; };

class LO
{
public:
    int pad0, pad4, pad8;
    virtual void V01(); virtual void V02(); virtual void V03(); virtual void V04(); virtual void V05();
    virtual void V06(); virtual void V07(); virtual void V08(); virtual void V09(); virtual void V10();
    virtual void V11(); virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19(); virtual void V20();
    virtual void V21(); virtual void V22(); virtual void V23(); virtual void V24(); virtual void V25();
    virtual void V26(); virtual void V27(); virtual void V28(); virtual void V29(); virtual void V30();
    virtual void V31(); virtual void V32();
    virtual qword GetVelocity();                // slot 33
};

struct STEPPLAYER : LO
{
    char pad10[0x58 - 0x10];
    XF *pxf;                    // 0x58
    char pad5C[0xE8 - 0x5C];
    SOPHYS *psophys;            // 0xE8
    void *psoCollide;           // 0xEC (filter argument of FJumpPathBlocked)
    char padF0[0x218 - 0xF0];
    qword *pqwUnk218;           // 0x218
    char pad21C[0x240 - 0x21C];
    qword qwUnk240;             // 0x240 offset between the targets' frame and the goal
    char pad250[0x2C0 - 0x250];
    char jtair[0x200];          // 0x2C0
    char jtcontrol[0xB40];      // 0x4C0 (first argument of RailPointVelocity)
    uint grfTarget;             // 0x1000 target kinds this player can use
    char pad1004[0x13D0 - 0x1004];
    int nPartnerState;          // 0x13D0
    char pad13D4[0x1914 - 0x13D4];
    int fPartnerBusy;           // 0x1914
    char pad1918[4];
    LO *ploPartnerTarget;       // 0x191C
    char pad1920[0x1F30 - 0x1920];
    float sRadius;              // 0x1F30
};

struct JTAIR
{
    STEPPLAYER *pstepplayer;
    char pad4[0x10 - 0x4];
    float uTarget;              // 0x10
    float sTarget;              // 0x14
};

// Mix-in shared by the target objects (at 0xE0 in a SHAPE, at 0x190 in a CURVE).
class TARGET
{
public:
    int pad0, pad4;
    float sHeight;              // 0x08 how far below the player it may be
    int padC[4];
    uint grf;                   // 0x1C
    virtual void V01(); virtual void V02();
    virtual void GetPoint(STEPPLAYER *pstepplayer, VECTOR *ppos, void *pv, float u);
};
class PAD_E0 { public: char ab[0xE0]; };
class PAD_190 { public: char ab[0x190]; };
struct SHAPE : PAD_E0, TARGET { SHAPE *pshapeNext; int pad108; float rAngle; };
struct CURVE : PAD_190, TARGET { CURVE *pcurveNext; };
struct HOOK
{
    char pad0[0xE0];
    HOOK *phookNext;            // 0xE0
    int padE4;
    uint grfHook;               // 0xE8
    char padEC[0x108 - 0xEC];
    float sHeight;              // 0x108
    char pad10C[0x11C - 0x10C];
    uint grf;                   // 0x11C
};
struct MESH { char pad0[0x100]; MESH *pmeshNext; int pad104; float sHeight; };

// Callback contexts (layouts from the matched callbacks).
struct CURVECTX { void *pjtcontrol; void *pjtair; CURVE *pcurve; int pad; qword v; };    // func_0019AA58
struct OBJCTX { JTAIR *pjtair; void *plo; int pad[2]; qword v; };                         // ABB8, AC88, AAB8, AB38
struct PAIR { JTAIR *pjtair; void *plo; };                                               // GScorePipeS
struct SOLIST { int cpso; void **apso; };                                                // func_0019B0A8

#include "clock.h"
typedef float (*PFNSCORE)(void *, float);

extern "C" {
extern SHAPE *D_003E13D8, *D_003E13FC, *D_003E1408;
extern CURVE *D_003E13CC, *D_003E13C0, *D_003E13F0;
extern HOOK *D_003E13B4;
extern MESH *D_003E142C;
extern STEPPLAYER *D_002F7900;      // the partner
extern qword D_002A2DD0;            // zero vector
extern float D_002BF8E0;            // score limit
extern float D_002BF8E4, D_002BF8E8, D_002BF8EC, D_002BF8F0, D_002BF8F4, D_002BF8F8, D_002BF8FC, D_002BF904, D_002BF908;
extern float D_002BF90C, D_002BF914, D_002BF918;

qword PosOfLo(void *plo) asm("PosOfLo__FP2LO");                                         // PosLoWorld
void *s1_memset(void *pv, int b, uint cb) asm("memset");                         // memset
qword VelJumpLaunch(JTAIR *pjtair, int nKind) asm("VelJumpLaunch__FP4JUMPi");                         // JtPlanLaunchVz
int FIsBasicDerivedFrom(void *plo, int cid) asm("FIsBasicDerivedFrom__FP5BASIC3CID");
void FitJumpToPoint(JTAIR *pjtair, VU_VECTOR v, void *plo, VU_VECTOR pos, VU_VECTOR dpos, float *pt, float *pg,
                   VECTOR *ppos, VECTOR *pv) asm("FitJumpToPoint__FP4JUMPG9VU_VECTORP2LON21PfT5P6VECTORT7");
float FUN_001cf138(JTAIR *pjtair, void *plo, float g, float dg);
int FJumpPathBlocked(JTAIR *pjtair, void *pfnFilter, void *pvFilter, float t, qword pos, qword v, qword posEnd, qword vEnd,
                  VECTOR *ppos) asm("FJumpPathBlocked__FP5ACTORP6VECTORT1fG9VU_VECTORN34T1");
void NOverlapKind() asm("NOverlapKind__FP3ALOT0");
void func_0019B0A8();
void NearestCrvAll(CURVE *pcurve, qword pos, void *pv, VECTOR *ppos, VECTOR *pdir, float *pu, float *ps) asm("NearestCrvAll__FP3CRVG9VU_VECTORP6VECTORT2PfT4T2");
void func_001E7410(CURVE *pcurve, PFNSCORE pfn, void *pv, int a, int b, float *pg, float *pgOut);
float DgStepCrv(CURVE *pcurve) asm("DgStepCrv__FP3CRV");
float GFromCrvS(CURVE *pcurve, float s) asm("GFromCrvS__FP3CRVf");
float SMaxCrv(CURVE *pcurve) asm("SMaxCrv__FP3CRV");
float SFromCrvG(CURVE *pcurve, float u) asm("SFromCrvG__FP3CRV");
void MinimizeRange(PFNSCORE pfn, void *pv, float g0, float g1, float gMin, float gMax, float *px, float *pg) asm("MinimizeRange__FPFPvf_fPvffffPfT6");
float func_0019AA58(void *pv, float u);
float func_0019ABB8(void *pv, float u);
float GScorePipeS(void *pv, float u) asm("GScorePipeS__FP5ACTORf");
float func_0019AC88(void *pv, float u);
float func_0019AAB8(void *pv, float u);
float func_0019AB38(void *pv, float u);
void RailPointVelocity(void *pjtcontrol, CURVE *pcurve, VECTOR *ppos, VECTOR *pv, float u) asm("RailPointVelocity__FP5ACTORP2LOPG9VU_VECTORP6VECTORf");
void GFitJump(JTAIR *pjtair, void *plo, qword pos, float *pg, VECTOR *ppos, VECTOR *pv, float t) asm("GFitJump__FP5ACTORP2LOG9VU_VECTORP6VECTORN23f");
void FindClimbSurfClosestPoint(MESH *pmesh, qword pos, void *pv, TRI *ptri, VECTOR *ppos, VECTOR *pnormal) asm("FindClimbSurfClosestPoint__FP2LOG9VU_VECTORP6VECTORP7SURFLOCN22");
int ClimbSurfLanding(MESH *pmesh, qword pos, qword v, qword dv, float s, float t, TRI *ptri, VECTOR *ppos, VECTOR *pv) asm("ClimbSurfLanding__FP2LOG9VU_VECTORN21P6TRIREFPG9VU_VECTORP7SURFLOCff");
void EvalCrvS(CURVE *pcurve, float s, VECTOR *ppos, VECTOR *pnormal) asm("EvalCrvS__FP3CRVfP6VECTORT2");
qword ConvertPos(void *pvFrom, void *pvTo, qword pos) asm("ConvertPos__FP2LOT0G9VU_VECTOR");
float atan2f(float y, float x) asm("atan2f");                                 // atan2f
void SetJumpAnimState(JTAIR *pjtair, int nKind, void *plo) asm("SetJumpAnimState__FP4JUMPiP2LO");
}

static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float LengthSquared(qword v)
{
    qword l, one; float r;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(l), "=&j"(one) : "0"(v));
    __asm__("qmfc2.ni %0,%1" : "=r"(r) : "j"(l));
    return r;
}
static inline float Length(qword v)
{
    qword l, one; float r;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(l), "=&j"(one) : "0"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(l) : "0"(l));
    __asm__("qmfc2.ni %0,%1" : "=r"(r) : "j"(l));
    return r;
}
static inline float GMinOf(float a, float b) { return a < b ? a : b; }

// name: SafeHouse port (ChooseJumpTarget)
extern "C" void ChooseJumpTarget__FP4JUMPP2LO(JTAIR *pjtair, void *ploForce)
{
    void *ploBest = 0;
    int nKind = -1;
    float sBest = 0.0f, uBest = 0.0f;
    VECTOR pos, v, posHit, posBest, vHit, vBest;
    TRI tri;
    VECTOR vLaunch, posTarget;
    float t, g;

    pos.q = PosOfLo(pjtair->pstepplayer);
    v.q = pjtair->pstepplayer->GetVelocity();
    uint grf = pjtair->pstepplayer->grfTarget;
    s1_memset(&tri, 0, sizeof(tri));
    float gBest = ploForce ? -FLT_MAX : FLT_MAX;
    vLaunch.q = VelJumpLaunch(pjtair, 4);
    float tBest = 0.0f;

    if (FIsBasicDerivedFrom(pjtair->pstepplayer, 0x35)) {
        for (SHAPE *pshape = D_003E13D8; pshape; pshape = pshape->pshapeNext) {
            if (!(pshape->grf & grf))
                continue;
            pshape->GetPoint(pjtair->pstepplayer, &posTarget, 0, 0.0f);
            if (pshape != ploForce && pshape->sHeight < pos.f[2] - posTarget.f[2])
                continue;
            FitJumpToPoint(pjtair, vLaunch, pshape, posTarget, D_002A2DD0, &t, &g, &posHit, &vHit);
            vHit.f[2] = vLaunch.f[2] + t * pjtair->pstepplayer->psophys->dvGravity.f[2];
            if (pshape != ploForce) {
                if (g >= D_002BF8E0)
                    continue;
                g = FUN_001cf138(pjtair, pshape, g, D_002BF8E4);
                if (gBest <= g)
                    continue;
                if (FJumpPathBlocked(pjtair, (void *)NOverlapKind, pjtair->pstepplayer->psoCollide, t, pos.q, vLaunch.q,
                                  posHit.q, vHit.q, 0))
                    continue;
            }
            posBest = posHit;
            vBest = vHit;
            nKind = 9;
            ploBest = pshape;
            gBest = GMinOf(g, gBest);
            tBest = t;
        }

        for (CURVE *pcurve = D_003E13CC; pcurve; pcurve = pcurve->pcurveNext) {
            if (!(pcurve->grf & grf))
                continue;
            if (pcurve != ploForce) {
                NearestCrvAll(pcurve, *pjtair->pstepplayer->pqwUnk218, 0, &posTarget, 0, 0, 0);
                if (pcurve->sHeight < pos.f[2] - posTarget.f[2])
                    continue;
            }
            CURVECTX ctx;
            float uStart, u;
            ctx.pjtcontrol = pjtair->pstepplayer->jtcontrol;
            ctx.pjtair = pjtair->pstepplayer->jtair;
            ctx.pcurve = pcurve;
            ctx.v = vLaunch.q;
            func_001E7410(pcurve, func_0019AA58, &ctx, 0, 0, &uStart, 0);
            MinimizeRange(func_0019AA58, &ctx, uStart, DgStepCrv(pcurve), GFromCrvS(pcurve, 50.0f),
                          GFromCrvS(pcurve, SMaxCrv(pcurve) - 50.0f), &u, &g);
            if (pcurve != ploForce) {
                if (g >= D_002BF8E0)
                    continue;
                g = FUN_001cf138(pjtair, pcurve, g, D_002BF8E8);
                if (gBest <= g)
                    continue;
            }
            VECTOR dpos;
            RailPointVelocity(ctx.pjtcontrol, pcurve, &posTarget, &dpos, u);
            FitJumpToPoint(pjtair, vLaunch, pcurve, posTarget, dpos, &t, 0, &posHit, &vHit);
            vHit.f[2] = vLaunch.f[2] + t * pjtair->pstepplayer->psophys->dvGravity.f[2];
            if (pcurve != ploForce &&
                FJumpPathBlocked(pjtair, (void *)NOverlapKind, pjtair->pstepplayer->psoCollide, t, pos.q, vLaunch.q,
                              posHit.q, vHit.q, 0))
                continue;
            ploBest = pcurve;
            gBest = GMinOf(g, gBest);
            nKind = 10;
            posBest = posHit;
            vBest = vHit;
            uBest = u;
            tBest = t;
            sBest = SFromCrvG(pcurve, uBest);
        }

        for (HOOK *phook = D_003E13B4; phook; phook = phook->phookNext) {
            if (phook != ploForce) {
                if (ploForce)
                    continue;
                if ((phook->grfHook & 1) == 0)
                    continue;
                if (!FIsBasicDerivedFrom(phook, 0x13))
                    continue;
            }
            if (!(phook->grf & grf))
                continue;
            qword posHook = PosOfLo(phook);
            posTarget.q = posHook;
            if (phook != ploForce) {
                if (phook->sHeight < pos.f[2] - posTarget.f[2])
                    continue;
                if (1000000.0f < LengthSquared(Sub(posHook, pos.q)))
                    continue;
            }
            OBJCTX ctx;
            ctx.v = D_002A2DD0;
            ctx.pjtair = pjtair;
            ctx.plo = phook;
            MinimizeRange(func_0019ABB8, &ctx, 0.5f, 0.25f, 0.25f, 3.0f, &t, &g);
            GFitJump(ctx.pjtair, ctx.plo, ctx.v, 0, &posHit, &vHit, t);
            if (phook != ploForce) {
                if (g >= D_002BF8E0)
                    continue;
                g = FUN_001cf138(pjtair, phook, g, D_002BF8EC);
                if (gBest <= g)
                    continue;
                if (FJumpPathBlocked(pjtair, (void *)NOverlapKind, pjtair->pstepplayer->psoCollide, t, pos.q, v.q,
                                  posHit.q, vHit.q, &posTarget))
                    continue;
            }
            nKind = 14;
            ploBest = phook;
            posBest.q = Add(posHit.q, pjtair->pstepplayer->qwUnk240);
            vBest = vHit;
            gBest = GMinOf(gBest, g);
            tBest = t;
        }

        for (MESH *pmesh = D_003E142C; pmesh; pmesh = pmesh->pmeshNext) {
            FindClimbSurfClosestPoint(pmesh, pos.q, 0, 0, &posTarget, 0);
            if (pmesh != ploForce) {
                if (pmesh->sHeight < pos.f[2] - posTarget.f[2])
                    continue;
                if (1000.0f < Length(Sub(posTarget.q, pos.q)))
                    continue;
            }
            TRI triHit;
            OBJCTX ctx;
            float gMesh;
            ctx.v = vLaunch.q;
            ctx.pjtair = pjtair;
            ctx.plo = pmesh;
            MinimizeRange(func_0019AC88, &ctx, 1.0f, 0.25f, 0.25f, 2.0f, &t, &gMesh);
            if (pmesh != ploForce) {
                if (gMesh >= D_002BF8E0)
                    continue;
                gMesh = FUN_001cf138(pjtair, pmesh, gMesh, D_002BF908);
                if (gBest <= gMesh)
                    continue;
            }
            ClimbSurfLanding(pmesh, pos.q, vLaunch.q, pjtair->pstepplayer->psophys->dvGravity.q, pjtair->pstepplayer->sRadius,
                          t, &triHit, &posHit, &vHit);
            if (pmesh != ploForce &&
                FJumpPathBlocked(pjtair, (void *)NOverlapKind, pjtair->pstepplayer->psoCollide, t, pos.q, v.q, posHit.q,
                              vHit.q, 0))
                continue;
            nKind = 16;
            ploBest = pmesh;
            posBest.q = Add(posHit.q, pjtair->pstepplayer->qwUnk240);
            vBest = vHit;
            gBest = GMinOf(gBest, gMesh);
            tBest = t;
            tri = triHit;
        }
    }

    if (FIsBasicDerivedFrom(pjtair->pstepplayer, 0x37) && D_002F7900 && D_002F7900->nPartnerState == 15 &&
        !D_002F7900->fPartnerBusy) {
        posTarget.q = PosOfLo(D_002F7900->ploPartnerTarget);
        FitJumpToPoint(pjtair, vLaunch, D_002F7900->ploPartnerTarget, posTarget, D_002A2DD0, &t, &g, &posHit, &vHit);
        vHit.f[2] = vLaunch.f[2] + t * pjtair->pstepplayer->psophys->dvGravity.f[2];
        if (D_002F7900->ploPartnerTarget != ploForce) {
            if (g >= D_002BF8E0)
                goto LPartnerDone;
            g = FUN_001cf138(pjtair, D_002F7900, g, D_002BF904);
            if (gBest <= g)
                goto LPartnerDone;
            void *apso[2];
            SOLIST solist;
            apso[0] = pjtair->pstepplayer->psoCollide;
            apso[1] = D_002F7900->psoCollide;
            solist.cpso = 2;
            solist.apso = apso;
            if (FJumpPathBlocked(pjtair, (void *)func_0019B0A8, &solist, t, pos.q, vLaunch.q, posHit.q, vHit.q, 0))
                goto LPartnerDone;
        }
        posBest = posHit;
        vBest = vHit;
        nKind = 18;
        ploBest = D_002F7900->ploPartnerTarget;
        tBest = t;
        gBest = GMinOf(g, gBest);
    }
LPartnerDone:

    for (CURVE *pcurve = D_003E13C0; pcurve; pcurve = pcurve->pcurveNext) {
        if (!(pcurve->grf & pjtair->pstepplayer->grfTarget))
            continue;
        float sCur;
        NearestCrvAll(pcurve, pos.q, 0, &posTarget, 0, 0, &sCur);
        if (pcurve != ploForce) {
            if (pcurve->sHeight < pos.f[2] - posTarget.f[2])
                continue;
            if (1000.0f < Length(Sub(posTarget.q, pos.q)))
                continue;
        }
        PAIR pair;
        float s, gCurve;
        pair.pjtair = pjtair;
        pair.plo = pcurve;
        MinimizeRange(GScorePipeS, &pair, sCur, 100.0f, 50.0f, SMaxCrv(pcurve) - 50.0f, &s, &gCurve);
        if (pcurve != ploForce) {
            if (D_002BF8E0 <= gCurve)
                continue;
            gCurve = FUN_001cf138(pjtair, pcurve, gCurve, D_002BF8F0);
            if (gBest <= gCurve)
                continue;
        }
        OBJCTX ctx;
        ctx.pjtair = pjtair;
        ctx.plo = pcurve;
        EvalCrvS(pcurve, s, &posTarget, 0);
        ctx.v = ConvertPos(0, pcurve, posTarget.q);
        MinimizeRange(func_0019ABB8, &ctx, 0.5f, 0.25f, 0.25f, 3.0f, &t, 0);
        GFitJump(ctx.pjtair, ctx.plo, ctx.v, 0, &posHit, &vHit, t);
        if (pcurve != ploForce &&
            FJumpPathBlocked(pjtair, (void *)NOverlapKind, pjtair->pstepplayer->psoCollide, t, pos.q, v.q, posHit.q,
                          vHit.q, &posTarget))
            continue;
        nKind = 15;
        ploBest = pcurve;
        posBest.q = Add(posHit.q, pjtair->pstepplayer->qwUnk240);
        vBest = vHit;
        gBest = GMinOf(gBest, gCurve);
        tBest = t;
        sBest = s;
    }

    for (SHAPE *pshape = D_003E13FC; pshape; pshape = pshape->pshapeNext) {
        if (!(pshape->grf & grf))
            continue;
        qword posShape = PosOfLo(pshape);
        posTarget.q = posShape;
        if (pshape->sHeight < pos.f[2] - posTarget.f[2])
            continue;
        OBJCTX ctx;
        VECTOR dpos;
        float u;
        dpos.q = Sub(pos.q, posShape);
        ctx.v = v.q;
        ctx.pjtair = pjtair;
        ctx.plo = pshape;
        MinimizeRange(func_0019AAB8, &ctx, atan2f(dpos.f[1], dpos.f[0]) * pshape->rAngle, D_002BF914, -FLT_MAX,
                      FLT_MAX, &u, &g);
        g = g * D_002BF90C;
        if (pshape != ploForce) {
            if (g >= D_002BF8E0)
                continue;
            g = FUN_001cf138(pjtair, pshape, g, D_002BF8F8);
            if (gBest <= g)
                continue;
        }
        VECTOR posPoint;
        pshape->GetPoint(pjtair->pstepplayer, &posPoint, 0, u);
        FitJumpToPoint(pjtair, v, pshape, posPoint, D_002A2DD0, &t, 0, &posHit, &vHit);
        vHit.f[2] = v.f[2] + t * pjtair->pstepplayer->psophys->dvGravity.f[2];
        if (pshape != ploForce &&
            FJumpPathBlocked(pjtair, (void *)NOverlapKind, pjtair->pstepplayer->psoCollide, t, pos.q, v.q, posHit.q,
                          vHit.q, 0))
            continue;
        nKind = 12;
        ploBest = pshape;
        posBest = posHit;
        vBest = vHit;
        gBest = GMinOf(gBest, g);
        tBest = t;
        sBest = u;
    }

    for (CURVE *pcurve = D_003E13F0; pcurve; pcurve = pcurve->pcurveNext) {
        if (!(pcurve->grf & grf))
            continue;
        float sCur;
        NearestCrvAll(pcurve, pos.q, 0, &posTarget, 0, 0, &sCur);
        if (pcurve->sHeight < pos.f[2] - posTarget.f[2])
            continue;
        OBJCTX ctx;
        float u;
        ctx.v = v.q;
        ctx.pjtair = pjtair;
        ctx.plo = pcurve;
        MinimizeRange(func_0019AB38, &ctx, sCur, D_002BF918, 30.0f, SMaxCrv(pcurve) - 30.0f, &u, &g);
        g = g * D_002BF90C;
        if (pcurve != ploForce) {
            if (g >= D_002BF8E0)
                continue;
            g = FUN_001cf138(pjtair, pcurve, g, D_002BF8F4);
            if (gBest <= g)
                continue;
        }
        VECTOR posPoint;
        pcurve->GetPoint(pjtair->pstepplayer, &posPoint, 0, u);
        FitJumpToPoint(pjtair, v, pcurve, posPoint, D_002A2DD0, &t, 0, &posHit, &vHit);
        vHit.f[2] = v.f[2] + t * pjtair->pstepplayer->psophys->dvGravity.f[2];
        if (pcurve != ploForce &&
            FJumpPathBlocked(pjtair, (void *)NOverlapKind, pjtair->pstepplayer->psoCollide, t, pos.q, v.q, posHit.q,
                          vHit.q, 0))
            continue;
        nKind = 11;
        ploBest = pcurve;
        posBest = posHit;
        vBest = vHit;
        gBest = GMinOf(gBest, g);
        tBest = t;
        sBest = u;
    }

    for (SHAPE *pshape = D_003E1408; pshape; pshape = pshape->pshapeNext) {
        if (!(pshape->grf & grf))
            continue;
        pshape->GetPoint(pjtair->pstepplayer, &posTarget, 0, 0.0f);
        if (pshape != ploForce && pshape->sHeight < pos.f[2] - posTarget.f[2])
            continue;
        FitJumpToPoint(pjtair, v, pshape, posTarget, D_002A2DD0, &t, &g, &posHit, &vHit);
        vHit.f[2] = v.f[2] + t * pjtair->pstepplayer->psophys->dvGravity.f[2];
        if (pshape != ploForce) {
            if (g >= D_002BF8E0)
                continue;
            g = FUN_001cf138(pjtair, pshape, g, D_002BF8FC);
            if (gBest <= g)
                continue;
            if (FJumpPathBlocked(pjtair, (void *)NOverlapKind, pjtair->pstepplayer->psoCollide, t, pos.q, v.q, posHit.q,
                              vHit.q, 0))
                continue;
        }
        nKind = 13;
        ploBest = pshape;
        gBest = GMinOf(g, gBest);
        posBest = posHit;
        vBest = vHit;
        tBest = t;
    }

    if (nKind != -1) {
        XF *pxf = pjtair->pstepplayer->pxf;
        pxf->tGoal = g_clock.t + tBest;
        pxf->posGoal = Sub(posBest.q, pjtair->pstepplayer->qwUnk240);
        pxf->vGoal = vBest.q;
        pjtair->uTarget = uBest;
        pjtair->sTarget = sBest;
        SetJumpAnimState(pjtair, nKind, ploBest);
    }
}
