// Fetch__14CTRLLOOKMOTION (Claude agent, 2026-10-23): MATCH. From hand_wip v5; the virtual at vtable slot 5 takes a float 4th
// argument, and the caller passes pctrl->gHi (that is why the target loads gHi into $f12 for the 0 < gHi test).
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); }
};
static inline qword MulM3(const M3 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
        : "=j"(r) : "j"(v), "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]));
    return r;
}
static inline qword VLen(qword c)
{
    qword l, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(l), "=&j"(one) : "j"(c));
    __asm__("vsqrt Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "=j"(l) : "j"(l));
    return l;
}
static inline qword AddScaledDiff(qword a, qword b, qword c, VU_FLOAT f)
{
    qword r, d;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(b), "j"(c));
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(d), "j"(f.q));
    return r;
}
static inline float GetX(qword q)
{
    float f;
    __asm__("mtc1 %1, %0" : "=f"(f) : "r"(q));
    return f;
}

struct CTRL { int kind; void *palo; int pad[4]; VTENT *pvt; };
// Layout: SafeHouse port (lo.h XF, xf.h CTRLLOOKMOTION / CTRLJOB: gLo +0x1C and gHi +0x20 are the job's two floats,
// used as the lead: the mover's velocity gHi seconds ahead blends in by gLo / gHi).
// CTRLLOOKMOTION::Fetch: the record looks along the motion of the first translation record (kind 1) up its chain:
// that record's velocity (by its mode / state), in world space, through BuildLookAtMatrix into the segment; under
// 100 units/s it keeps the current world direction. No mover: the record's own matrix.
struct XF {
    M3 mat;
    qword pos;
    M3 matWorld;
    qword posWorld;
    float g0, g1;
    float *pg, *pdgScale;
    CTRL *pctrlFirst;
    int kind;
    unsigned short mode;
    short state;
    int x9C;
    XF *pxfRef;
    int padA4[3];
    qword vel;
    M3 aseg;
    qword vel1;
};
struct CTRLLOOKMOTION { int kind; void *palo; XF *pxf; int prio; int pad10[3]; float gLo; float gHi; XF *pxfMover; };

extern "C" {
extern qword D_002A2DD0, g_normalZ, D_002BC380;
void RefreshXf(void *pv, XF *pxfCur) asm("RefreshXf__FP3ALOP2XF");
void Hermite(qword a, qword da, qword b, qword db, float dt, float t, float dtScale, void *pv, void *pdv, int n) asm("Hermite__FG9VU_VECTORN30fffPG9VU_VECTORN27");
M3 BuildLookAtMatrix(qword a, qword b) asm("BuildLookAtMatrix__FP6VECTORG9VU_VECTORT1");
void MatConvertXfs(M3 *pm, int n, XF *pxfCur, M3 *pmSrc) asm("MatConvertXfs__FP2XFT0P7MATRIX3Pv");
}

static inline void SetMat(XF *pxfCur, const M3 &m)
{
    pxfCur->aseg = m;
    pxfCur->state = 5;
}

static inline void Fin(CTRLLOOKMOTION *pctrl, M3 &mT, M3 m)
{
    mT = m;
    XF *pxfCur = pctrl->pxf;
    M3 *pm = &pxfCur->aseg;
    MatConvertXfs(&m, 0, pxfCur->pxfRef, &mT);
    *pm = m;
    pctrl->pxf->state = 5;
}

// name: SafeHouse port (CTRLLOOKMOTION::Fetch)
extern "C" void Fetch__14CTRLLOOKMOTION(CTRLLOOKMOTION *pctrl)
{
    XF *pxfM;
    union { qword q; } vT;
    M3 mT;
    if (pctrl->pxfMover == 0) {
        XF *pxfCur = pctrl->pxf;
        XF *pxfUp;
        for (pxfUp = pxfCur->pxfRef; pxfUp != 0 && pxfUp->kind != 1; pxfUp = pxfUp->pxfRef)
            ;
        if (pxfUp == 0) {
            M3 *pm = &pctrl->pxf->aseg;
            *pm = pctrl->pxf->mat;
            pctrl->pxf->state = 5;
            return;
        }
        pctrl->pxfMover = pxfUp;
    }
    pxfM = pctrl->pxfMover;
    if (pxfM->pctrlFirst)
        RefreshXf(pxfM->pctrlFirst->palo, pxfM);
    qword v;
    switch ((short)(pctrl->pxfMover->mode - 1)) {
    case 0: case 1: case 6: case 7: case 8: case 10: case 16: case 17: case 19: case 20:
        v = pxfM->vel;
        break;
    case 4: case 5: {
        qword w;
        switch (pxfM->state) {
        case 3: case 4:
            w = pxfM->aseg.r[1];
            break;
        case 1:
            Hermite(pxfM->aseg.r[0], pxfM->aseg.r[1], pxfM->aseg.r[2], pxfM->vel1,
                pxfM->g1 - pxfM->g0, *pxfM->pg - pxfM->g0, *pxfM->pdgScale, 0, &vT.q, 0);
            w = vT.q;
            break;
        case 0: case 2: case 5:
        default:
            w = D_002A2DD0;
            break;
        }
        v = w;
        break;
    }
    default:
        __asm__("vsub.xyzw %0, $vf0, $vf0" : "=j"(v));
        break;
    }
    if (pxfM->pxfRef)
        v = MulM3(pxfM->pxfRef->matWorld, v);
    if (GetX(VLen(v)) < 100.0f) {
        Fin(pctrl, mT, BuildLookAtMatrix(pctrl->pxf->matWorld.r[0], g_normalZ));
    } else {
        qword u = D_002BC380;
        if (0.0f < pctrl->gHi && 0.0f < pctrl->gLo && pxfM->pctrlFirst) {
            CTRL *po = pxfM->pctrlFirst;
            VTENT *pe = &po->pvt[5];
            ((void (*)(void *, int, qword *, float))pe->pfn)(VT_THIS(po, pe), 0, &vT.q, pctrl->gHi);
            if (pxfM->pxfRef)
                vT.q = MulM3(pxfM->pxfRef->matWorld, vT.q);
            u = AddScaledDiff(u, vT.q, v, VU_FLOAT(pctrl->gLo / pctrl->gHi));
        }
        Fin(pctrl, mT, BuildLookAtMatrix(v, u));
    }
}
