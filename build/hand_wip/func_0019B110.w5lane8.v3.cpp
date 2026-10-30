// func_0019B110: picks the best jump target for the hero (JTAIR, Lilly's jtair.c) from ten candidate lists.
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;

union VEC { qword q; float f[4]; };
struct VU_VECTOR { qword q; VU_VECTOR() {} VU_VECTOR(qword a) { q = a; } VU_VECTOR(const VEC &v) { q = v.q; } };
struct TRI { int itri; float u, v; };

struct SOPHYS { char pad0[0x80]; VEC dvGravity; };
struct JTGOAL { char pad0[0xA8]; float tDeadline; char padAC[0x14]; qword posGoal; qword vGoal; };

class LO {
public:
    int pad0, pad4, pad8;
    virtual void V01(); virtual void V02(); virtual void V03(); virtual void V04(); virtual void V05();
    virtual void V06(); virtual void V07(); virtual void V08(); virtual void V09(); virtual void V10();
    virtual void V11(); virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19(); virtual void V20();
    virtual void V21(); virtual void V22(); virtual void V23(); virtual void V24(); virtual void V25();
    virtual void V26(); virtual void V27(); virtual void V28(); virtual void V29(); virtual void V30();
    virtual void V31(); virtual void V32();
    virtual qword GetVelocity();
};

struct STEPPLAYER : LO {
    char pad10[0x58 - 0x10];
    JTGOAL *pjtgoal;            // 0x58
    char pad5C[0xE8 - 0x5C];
    SOPHYS *psophys;            // 0xE8
    void *pvCollide;            // 0xEC
    char padF0[0x218 - 0xF0];
    qword *pqwUnk218;           // 0x218
    char pad21C[0x240 - 0x21C];
    qword dposTarget;           // 0x240
    char pad250[0x2C0 - 0x250];
    char jtair[0x200];          // 0x2C0
    char jtcontrol[0xB40];      // 0x4C0
    uint grfTarget;             // 0x1000
    char pad1004[0x13D0 - 0x1004];
    int nPartnerState;          // 0x13D0
    char pad13D4[0x1914 - 0x13D4];
    int fPartnerBusy;           // 0x1914
    char pad1918[4];
    LO *ploPartnerTarget;       // 0x191C
    char pad1920[0x1F30 - 0x1920];
    float sRadius;              // 0x1F30
};

struct JTAIR {
    STEPPLAYER *pstepplayer;
    char pad4[0xC];
    float uTarget;              // 0x10
    float sTarget;              // 0x14
    char pad18[0xBC - 0x18];
    LO *ploPrev;                // 0xBC
};

// Mix-in shared by every target kind (at 0xE0 or 0x190 in the object).
class TARGET {
public:
    int pad0, pad4;
    float sHeight;              // 0x08
    int padC[4];
    uint grf;                   // 0x1C
    virtual void V01(); virtual void V02();
    virtual void GetPoint(STEPPLAYER *pstepplayer, VEC *ppos, void *pv, float u);
};
class PAD_E0 { public: char ab[0xE0]; };
class PAD_190 { public: char ab[0x190]; };
struct SHAPE : PAD_E0, TARGET { SHAPE *pshapeNext; float g108; float rAngle; };
struct CURVE : PAD_190, TARGET { CURVE *pcurveNext; };
struct HOOK { char pad0[0xE0]; HOOK *phookNext; int padE4; uint grfHook; char padEC[0x108 - 0xEC]; float sHeight; char pad10C[0x11C - 0x10C]; uint grf; };
struct MESH { char pad0[0x100]; MESH *pmeshNext; int pad104; float sHeight; };

struct CLOCK { float t, dt; };
struct CURVECTX { void *pjtcontrol; void *pjtair; CURVE *pcurve; int pad; qword v; };
struct OBJCTX { JTAIR *pjtair; void *plo; int pad[2]; qword v; };
struct PAIR { JTAIR *pjtair; void *plo; };
struct SOLIST { int cpso; void **apso; };

typedef float (*PFNSCORE)(void *, float);

extern "C" {
extern SHAPE *D_003E13D8, *D_003E13FC, *D_003E1408;
extern CURVE *D_003E13CC, *D_003E13C0, *D_003E13F0;
extern HOOK *D_003E13B4;
extern MESH *D_003E142C;
extern STEPPLAYER *D_002F7900;
extern CLOCK D_002DDED0;
extern qword D_002A2DD0;
extern float D_002A65B8, D_002A65BC;
extern float D_002BF8E0, D_002BF8E4, D_002BF8E8, D_002BF8EC, D_002BF8F0, D_002BF8F4, D_002BF8F8, D_002BF8FC;
extern float D_002BF904, D_002BF908, D_002BF90C, D_002BF914, D_002BF918;

qword func_001A62E8(void *plo);
void *func_002333B4(void *pv, int b, uint cb);
qword func_0019A750(JTAIR *pjtair, int nKind);
int func_00132B10(void *plo, int cid);
void func_0019A4A0(JTAIR *pjtair, VU_VECTOR v, void *plo, VU_VECTOR pos, VU_VECTOR dpos, float *pt, float *pg, VEC *ppos, VEC *pv);
float FUN_001cf138(JTAIR *pjtair, void *plo, float g, float dg);
int func_0019AE00(JTAIR *pjtair, void *pfnFilter, void *pvFilter, float t, qword pos, qword v, qword posEnd, qword vEnd, VEC *ppos);
void func_0020F948();
void func_0019B0A8();
void func_001E6F60(CURVE *pcurve, qword pos, void *pv, VEC *ppos, VEC *pdir, float *pu, float *ps);
void func_001E7410(CURVE *pcurve, PFNSCORE pfn, void *pv, int a, int b, float *pg, float *pgOut);
float func_001E77E8(CURVE *pcurve);
float func_001E64C8(CURVE *pcurve, float s);
float func_001E6648(CURVE *pcurve);
float func_001E63C0(CURVE *pcurve, float u);
void func_0011D9E0(PFNSCORE pfn, void *pv, float g0, float g1, float g2, float g3, float *px, float *pg);
float func_0019AA58(void *pv, float u);
float func_0019ABB8(void *pv, float u);
float func_0019ABF0(void *pv, float u);
float func_0019AC88(void *pv, float u);
float func_0019AAB8(void *pv, float u);
float func_0019AB38(void *pv, float u);
void func_00193A68(void *pjtcontrol, CURVE *pcurve, VEC *ppos, VEC *pv, float u);
void func_0019C300(JTAIR *pjtair, void *plo, qword pos, float *pg, VEC *ppos, VEC *pv, float t);
void func_00185310(MESH *pmesh, qword pos, void *pv, TRI *ptri, VEC *ppos, VEC *pnormal);
int func_00185D18(MESH *pmesh, qword pos, qword v, qword dv, float s, float t, TRI *ptri, VEC *ppos, VEC *pv);
void func_001E6F10(CURVE *pcurve, float s, VEC *ppos, VEC *pnormal);
qword func_001A6F00(void *pvFrom, void *pvTo, qword pos);
float func_002458F0(float y, float x);
void func_00195FB8(JTAIR *pjtair, int nKind, void *plo);
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

extern "C" void func_0019B110(JTAIR *pjtair, void *ploForce)
{
    void *ploBest = 0;
    int nKind = -1;
    float sBest = 0.0f, uBest = 0.0f;
    VEC pos, v, posHit, posBest, vHit, vBest;
    TRI tri;
    VEC vLaunch, posTarget;
    float t, g;

    pos.q = func_001A62E8(pjtair->pstepplayer);
    v.q = pjtair->pstepplayer->GetVelocity();
    uint grf = pjtair->pstepplayer->grfTarget;
    func_002333B4(&tri, 0, sizeof(tri));
    float gBest = ploForce ? D_002A65B8 : D_002A65BC;
    vLaunch.q = func_0019A750(pjtair, 4);
    float tBest = 0.0f;

    if (func_00132B10(pjtair->pstepplayer, 0x35)) {
        for (SHAPE *pshape = D_003E13D8; pshape; pshape = pshape->pshapeNext) {
            if (!(pshape->grf & grf))
                continue;
            pshape->GetPoint(pjtair->pstepplayer, &posTarget, 0, 0.0f);
            if (pshape != ploForce && pshape->sHeight < pos.f[2] - posTarget.f[2])
                continue;
            func_0019A4A0(pjtair, vLaunch, pshape, posTarget, D_002A2DD0, &t, &g, &posHit, &vHit);
            vHit.f[2] = vLaunch.f[2] + t * pjtair->pstepplayer->psophys->dvGravity.f[2];
            if (pshape != ploForce) {
                if (g >= D_002BF8E0)
                    continue;
                g = FUN_001cf138(pjtair, pshape, g, D_002BF8E4);
                if (gBest <= g)
                    continue;
                if (func_0019AE00(pjtair, (void *)func_0020F948, pjtair->pstepplayer->pvCollide, t, pos.q, vLaunch.q, posHit.q, vHit.q, 0))
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
                func_001E6F60(pcurve, *pjtair->pstepplayer->pqwUnk218, 0, &posTarget, 0, 0, 0);
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
            func_0011D9E0(func_0019AA58, &ctx, uStart, func_001E77E8(pcurve), func_001E64C8(pcurve, 50.0f),
                          func_001E64C8(pcurve, func_001E6648(pcurve) - 50.0f), &u, &g);
            if (pcurve != ploForce) {
                if (g >= D_002BF8E0)
                    continue;
                g = FUN_001cf138(pjtair, pcurve, g, D_002BF8E8);
                if (gBest <= g)
                    continue;
            }
            VEC dpos;
            func_00193A68(ctx.pjtcontrol, pcurve, &posTarget, &dpos, u);
            func_0019A4A0(pjtair, vLaunch, pcurve, posTarget, dpos, &t, 0, &posHit, &vHit);
            vHit.f[2] = vLaunch.f[2] + t * pjtair->pstepplayer->psophys->dvGravity.f[2];
            if (pcurve != ploForce &&
                func_0019AE00(pjtair, (void *)func_0020F948, pjtair->pstepplayer->pvCollide, t, pos.q, vLaunch.q, posHit.q, vHit.q, 0))
                continue;
            ploBest = pcurve;
            gBest = GMinOf(g, gBest);
            uBest = u;
            nKind = 10;
            posBest = posHit;
            vBest = vHit;
            tBest = t;
            sBest = func_001E63C0(pcurve, uBest);
        }

        for (HOOK *phook = D_003E13B4; phook; phook = phook->phookNext) {
            if (phook != ploForce) {
                if (ploForce)
                    continue;
                if ((phook->grfHook & 1) == 0)
                    continue;
                if (!func_00132B10(phook, 0x13))
                    continue;
            }
            if (!(phook->grf & grf))
                continue;
            qword posHook = func_001A62E8(phook);
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
            func_0011D9E0(func_0019ABB8, &ctx, 0.5f, 0.25f, 0.25f, 3.0f, &t, &g);
            func_0019C300(ctx.pjtair, ctx.plo, ctx.v, 0, &posHit, &vHit, t);
            if (phook != ploForce) {
                if (g >= D_002BF8E0)
                    continue;
                g = FUN_001cf138(pjtair, phook, g, D_002BF8EC);
                if (gBest <= g)
                    continue;
                if (func_0019AE00(pjtair, (void *)func_0020F948, pjtair->pstepplayer->pvCollide, t, pos.q, v.q, posHit.q, vHit.q, &posTarget))
                    continue;
            }
            nKind = 14;
            ploBest = phook;
            posBest.q = Add(posHit.q, pjtair->pstepplayer->dposTarget);
            vBest = vHit;
            gBest = GMinOf(gBest, g);
            tBest = t;
        }

        for (MESH *pmesh = D_003E142C; pmesh; pmesh = pmesh->pmeshNext) {
            func_00185310(pmesh, pos.q, 0, 0, &posTarget, 0);
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
            func_0011D9E0(func_0019AC88, &ctx, 1.0f, 0.25f, 0.25f, 2.0f, &t, &gMesh);
            if (pmesh != ploForce) {
                if (gMesh >= D_002BF8E0)
                    continue;
                gMesh = FUN_001cf138(pjtair, pmesh, gMesh, D_002BF908);
                if (gBest <= gMesh)
                    continue;
            }
            func_00185D18(pmesh, pos.q, vLaunch.q, pjtair->pstepplayer->psophys->dvGravity.q, pjtair->pstepplayer->sRadius, t,
                          &triHit, &posHit, &vHit);
            if (pmesh != ploForce &&
                func_0019AE00(pjtair, (void *)func_0020F948, pjtair->pstepplayer->pvCollide, t, pos.q, v.q, posHit.q, vHit.q, 0))
                continue;
            nKind = 16;
            ploBest = pmesh;
            posBest.q = Add(posHit.q, pjtair->pstepplayer->dposTarget);
            vBest = vHit;
            gBest = GMinOf(gBest, gMesh);
            tBest = t;
            tri = triHit;
        }
    }

    if (func_00132B10(pjtair->pstepplayer, 0x37) && D_002F7900 && D_002F7900->nPartnerState == 15 && !D_002F7900->fPartnerBusy) {
        posTarget.q = func_001A62E8(D_002F7900->ploPartnerTarget);
        func_0019A4A0(pjtair, vLaunch, D_002F7900->ploPartnerTarget, posTarget, D_002A2DD0, &t, &g, &posHit, &vHit);
        vHit.f[2] = vLaunch.f[2] + t * pjtair->pstepplayer->psophys->dvGravity.f[2];
        if (D_002F7900->ploPartnerTarget != ploForce) {
            if (g >= D_002BF8E0)
                goto LPartnerDone;
            g = FUN_001cf138(pjtair, D_002F7900, g, D_002BF904);
            if (gBest <= g)
                goto LPartnerDone;
            void *apso[2];
            SOLIST solist;
            apso[0] = pjtair->pstepplayer->pvCollide;
            apso[1] = D_002F7900->pvCollide;
            solist.cpso = 2;
            solist.apso = apso;
            if (func_0019AE00(pjtair, (void *)func_0019B0A8, &solist, t, pos.q, vLaunch.q, posHit.q, vHit.q, 0))
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
        func_001E6F60(pcurve, pos.q, 0, &posTarget, 0, 0, &sCur);
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
        func_0011D9E0(func_0019ABF0, &pair, sCur, 100.0f, 50.0f, func_001E6648(pcurve) - 50.0f, &s, &gCurve);
        if (pcurve != ploForce) {
            if (gCurve >= D_002BF8E0)
                continue;
            gCurve = FUN_001cf138(pjtair, pcurve, gCurve, D_002BF8F0);
            if (gBest <= gCurve)
                continue;
        }
        OBJCTX ctx;
        func_001E6F10(pcurve, s, &posTarget, 0);
        ctx.pjtair = pjtair;
        ctx.plo = pcurve;
        ctx.v = func_001A6F00(0, pcurve, posTarget.q);
        func_0011D9E0(func_0019ABB8, &ctx, 0.5f, 0.25f, 0.25f, 3.0f, &t, 0);
        func_0019C300(ctx.pjtair, ctx.plo, ctx.v, 0, &posHit, &vHit, t);
        if (pcurve != ploForce &&
            func_0019AE00(pjtair, (void *)func_0020F948, pjtair->pstepplayer->pvCollide, t, pos.q, v.q, posHit.q, vHit.q, &posTarget))
            continue;
        nKind = 15;
        ploBest = pcurve;
        posBest.q = Add(posHit.q, pjtair->pstepplayer->dposTarget);
        vBest = vHit;
        gBest = GMinOf(gBest, gCurve);
        tBest = t;
        sBest = s;
    }

    for (SHAPE *pshape = D_003E13FC; pshape; pshape = pshape->pshapeNext) {
        if (!(pshape->grf & grf))
            continue;
        qword posShape = func_001A62E8(pshape);
        posTarget.q = posShape;
        if (pshape->sHeight < pos.f[2] - posTarget.f[2])
            continue;
        OBJCTX ctx;
        VEC dpos;
        float u;
        dpos.q = Sub(pos.q, posShape);
        ctx.v = v.q;
        ctx.pjtair = pjtair;
        ctx.plo = pshape;
        func_0011D9E0(func_0019AAB8, &ctx, func_002458F0(dpos.f[1], dpos.f[0]) * pshape->rAngle, D_002BF914, D_002A65B8, D_002A65BC, &u, &g);
        g = g * D_002BF90C;
        if (pshape != ploForce) {
            if (g >= D_002BF8E0)
                continue;
            g = FUN_001cf138(pjtair, pshape, g, D_002BF8F8);
            if (gBest <= g)
                continue;
        }
        VEC posPoint;
        pshape->GetPoint(pjtair->pstepplayer, &posPoint, 0, u);
        func_0019A4A0(pjtair, v, pshape, posPoint, D_002A2DD0, &t, 0, &posHit, &vHit);
        vHit.f[2] = v.f[2] + t * pjtair->pstepplayer->psophys->dvGravity.f[2];
        if (pshape != ploForce &&
            func_0019AE00(pjtair, (void *)func_0020F948, pjtair->pstepplayer->pvCollide, t, pos.q, v.q, posHit.q, vHit.q, 0))
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
        func_001E6F60(pcurve, pos.q, 0, &posTarget, 0, 0, &sCur);
        if (pcurve->sHeight < pos.f[2] - posTarget.f[2])
            continue;
        OBJCTX ctx;
        float u;
        ctx.v = v.q;
        ctx.pjtair = pjtair;
        ctx.plo = pcurve;
        func_0011D9E0(func_0019AB38, &ctx, sCur, D_002BF918, 30.0f, func_001E6648(pcurve) - 30.0f, &u, &g);
        g = g * D_002BF90C;
        if (pcurve != ploForce) {
            if (g >= D_002BF8E0)
                continue;
            g = FUN_001cf138(pjtair, pcurve, g, D_002BF8F4);
            if (gBest <= g)
                continue;
        }
        VEC posPoint;
        pcurve->GetPoint(pjtair->pstepplayer, &posPoint, 0, u);
        func_0019A4A0(pjtair, v, pcurve, posPoint, D_002A2DD0, &t, 0, &posHit, &vHit);
        vHit.f[2] = v.f[2] + t * pjtair->pstepplayer->psophys->dvGravity.f[2];
        if (pcurve != ploForce &&
            func_0019AE00(pjtair, (void *)func_0020F948, pjtair->pstepplayer->pvCollide, t, pos.q, v.q, posHit.q, vHit.q, 0))
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
        func_0019A4A0(pjtair, v, pshape, posTarget, D_002A2DD0, &t, &g, &posHit, &vHit);
        vHit.f[2] = v.f[2] + t * pjtair->pstepplayer->psophys->dvGravity.f[2];
        if (pshape != ploForce) {
            if (g >= D_002BF8E0)
                continue;
            g = FUN_001cf138(pjtair, pshape, g, D_002BF8FC);
            if (gBest <= g)
                continue;
            if (func_0019AE00(pjtair, (void *)func_0020F948, pjtair->pstepplayer->pvCollide, t, pos.q, v.q, posHit.q, vHit.q, 0))
                continue;
        }
        nKind = 13;
        posBest = posHit;
        vBest = vHit;
        ploBest = pshape;
        gBest = GMinOf(g, gBest);
        tBest = t;
    }

    if (nKind != -1) {
        JTGOAL *pjtgoal = pjtair->pstepplayer->pjtgoal;
        pjtgoal->tDeadline = D_002DDED0.t + tBest;
        pjtgoal->posGoal = Sub(posBest.q, pjtair->pstepplayer->dposTarget);
        pjtgoal->vGoal = vBest.q;
        pjtair->uTarget = uBest;
        pjtair->sTarget = sBest;
        func_00195FB8(pjtair, nKind, ploBest);
    }
}
