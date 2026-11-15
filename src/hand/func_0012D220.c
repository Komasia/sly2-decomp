/* MATCH (Claude agent laneB22, 2026-10-23): from v8 (3). 2nd block: dt read as the scalar D_002DDED4 (g_clock.dt) through an "rV" asm input: expand keeps the MEM (V allows memory) but only r fits at reload, so reload loads it at the asm through the dying %hi reg (target lw v0,lo(v0) after the lqc2s); vsub then pin-free as "+j"(d = s.pos). */
/* CTRLLOOKAT::Fetch: the record turns toward its target (the object oidTarget, else the nearest player): out of range
 * (sRange) it rests at posRest and the controller takes its far priority (a new head then fetches instead); in range
 * the direction's pan / tilt go through two clamped polynomials into the record's segment value, with a velocity by
 * finite difference over the frame. Layout: SafeHouse port (xf.h CTRLLOOKAT, lo.h XF); radPan/Tilt names from use. */
/* v8 (Claude agent laneB21, 2026-10-23): aligned 7 -> 3. posT load: pxf ($v0) and a dummy z ($v1) kept live across it by two commented empty allocation-only asms, so the reload reg for the spilled posT is $a1 like the target (find_reg takes the first free reg in alloc order); the keep-alive asm has an output (+r po) so it is not volatile and reload_cse removes the a1 reload. Left: 2nd-block dt load (target: lui early + lw v0,lo(v0) right before the vsub = reload of a MEM). */
/* v7 (Claude agent laneB19, 2026-10-23): aligned 8 -> 7. Allocation-only "r"(pctrl->pxf) on the 2nd-block vsub/qmtc2 asm gives pxf $v1. Left: posT lq v0+por (target lq a1), lw dt scheduled before the lqc2s and dt in $a0 (target: reload-style lw v0,lo(v0) right before the vsub). */
/* v6 (Claude agent laneB15, 2026-10-23): aligned 9 -> 8. dv is a plain qword (spilled across the calls, so the dot reads its reload: lqc2 vf3) kept apart from d by a commented empty asm on d; posT a plain qword too (spill slots dv 0x40 / posT 0x50 in pseudo order). Left: posT load lq v0 + por a1 (target lq a1 directly), second block lw pxf/dt regs. */
/* v5 (Claude agent laneB11, 2026-10-23): aligned 11 -> 9. One commented pin: d (second-block vsub output) to vf2. Left: first block dot VF numbers (dv reload vf3 / one vf2 swapped; output-order swap 16, =&j same), second block lw pxf -> v1 and lw dt scheduled before the lqc2s (target after). */
/* v4 (Claude agent laneB8, 2026-10-23): aligned 12 -> 11. Second block: vsub and the dt qmtc2 fused in ONE asm (pos0 as first input), plus a "memory" clobber on the vdiv asm (keeps the dt sqc2 before it, out of the b delay slot). Left: pos/pos0 VF regs swapped and lw dt scheduled early; first block unchanged. */
/* v3 (Claude agent laneB7, 2026-10-23): aligned 13 -> 12. PloNearestPlayer__FP6VECTORG9VU_VECTOR takes a 2nd qword arg (posT; it sq a1 to its stack); posT as a U memory local so the load goes straight into a1. */
/* v2 (Claude agent, 2026-10-23): aligned 15 -> 13: qmtc2 asm before the vsub, vsub as "=j"(d) : s.pos, pos0 (gets dt vf3). Left: target schedules vsub before qmtc2 with s.pos vf2/pos0 vf1, output vf2. */
// WIP (Claude agent): 15 diffs - VU reg numbering only: dv reload should be vf3 / one-vector vf2 (ours swapped), second block wants lw of g_clock.dt after the lqc2s and vsub in vf2; posT lq via $a1.
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct POLY { float a, b, c; };
struct CTRL { int pad[6]; VTENT *pvt; };   /* a controller: its vtable at +0x18 */
struct XF { char pad[0x70]; qword posWorld; char pad80[0x90 - 0x80]; struct CTRLLOOKAT *pctrlFirst; short pad94[3]; short state; int pad9C; int pxfRef;
    char padA4[0xC0 - 0xA4]; qword pos0; qword vel0; };
struct CTRLLOOKAT {
    int kind; void *palo; struct XF *pxf; int prio; int pad10[4]; qword posRest; struct POLY polyPan; int pad3C; struct POLY polyTilt; int pad4C;
    float radPanMin; float radPanMax; float radTiltMin; float radTiltMax; float sRange; int prioNear; int prioFar; int oidTarget; void *plo; int fPrev;
};
extern char g_sw[];
extern qword D_002A2DD0;
extern float D_002A45A8;
struct CLOCK { float t; int dt; };
// layout note: CLOCK is include/clock.h's g_clock (t +0x0, dt +0x4); this copy reads dt as an int / union bit pattern, which the header's float field does not reproduce.
extern struct CLOCK g_clock;
extern int D_002DDED4;  /* g_clock.dt */
void *PloFindSwNearest__FP2LO3OIDii(void *pg, int k, int n, void *pv);
void *PloNearestPlayer__FP6VECTORG9VU_VECTOR(void *pg, qword pos);
qword PosOfLo__FP2LO(void *po);
void SortXfCtrls__FP3ALOP2XF(void *a, struct XF *b);
qword VecConvertXfs__FP2XFT0G9VU_VECTOR(int n, int k, qword v);
void PanTiltFromVector__FG9VU_VECTORPfT1(qword q, float *pa, float *pb);
static __inline__ float GEval(struct POLY *pp, float t) { return pp->a + t * (pp->b + t * pp->c); }
static __inline__ float GClamp(float g, float lo, float hi) { float r; if (g < lo) r = lo; else if (hi < g) r = hi; else r = g; return r; }
static __inline__ float GLength(U *pv, qword a)
{
    qword t;
    float g;
    __asm__("vmul.xyz %0, %0, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "+j"(a), "=j"(t) : "j"(pv->q));
    __asm__("vsqrt Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "+j"(a));
    __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(a));
    return g;
}

// name: SafeHouse port (CTRLLOOKAT::Fetch)
void Fetch__10CTRLLOOKAT(struct CTRLLOOKAT *pctrl)
{
    struct { qword pos; qword vel; } s;
    U dt;
    float ag[2];
    qword dv;
    qword posT;
    void *po;
    float g;
    int k;
    qword vel;

    if (pctrl->plo == 0 && pctrl->oidTarget != -1)
        pctrl->plo = PloFindSwNearest__FP2LO3OIDii(g_sw, 0x104, pctrl->oidTarget, pctrl->palo);
    {
        struct XF *pxf = pctrl->pxf;
        int z;
        __asm__("" : "=r"(z));  /* empty asm, allocation only: z occupies $v1 across the posT load */
        posT = pxf->posWorld;
        po = pctrl->plo;
        __asm__("" : "+r"(po) : "r"(pxf), "r"(z));  /* empty asm, allocation only: pxf ($v0) and z ($v1) stay live past the posT load, so reload picks $a1 for it (non-volatile: has an output, so reload_cse can drop the later a1 reload) */
    }
    if (!po)
        po = PloNearestPlayer__FP6VECTORG9VU_VECTOR(g_sw, posT);
    if (po) {
        qword d, t;
        d = PosOfLo__FP2LO(po);
        __asm__("vsub.xyzw %0, %0, %1" : "+j"(d) : "j"(posT));
        dv = d;
        __asm__("" : "+j"(d));  /* empty asm: keeps d and dv separate pseudos */
        __asm__("vmul.xyz %0, %0, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "+j"(d), "=j"(t) : "j"(dv));
        __asm__("vsqrt Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "+j"(d));
        __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(d));
    } else {
        g = D_002A45A8;
    }
    k = (pctrl->sRange < g) ? pctrl->prioFar : pctrl->prioNear;
    if (k != pctrl->prio) {
        struct CTRLLOOKAT *pctrlFirst;
        pctrl->prio = k;
        SortXfCtrls__FP3ALOP2XF(pctrl->palo, pctrl->pxf);
        pctrlFirst = pctrl->pxf->pctrlFirst;
        if (pctrlFirst != pctrl) {
            struct CTRL *pctrlHead = (struct CTRL *)pctrlFirst;
            ((void (*)(struct CTRL *))pctrlHead->pvt[4].pfn)((struct CTRL *)VT_THIS(pctrlHead, &pctrlHead->pvt[4]));
            return;
        }
    }
    if (pctrl->sRange < g) {
        s.pos = pctrl->posRest;
        s.vel = D_002A2DD0;
        pctrl->fPrev = 0;
    } else {
        PanTiltFromVector__FG9VU_VECTORPfT1(VecConvertXfs__FP2XFT0G9VU_VECTOR(0, pctrl->pxf->pxfRef, dv), &ag[0], &ag[1]);
        ag[0] = GClamp(GEval(&pctrl->polyPan, ag[0]), pctrl->radPanMin, pctrl->radPanMax);
        ag[1] = GClamp(GEval(&pctrl->polyTilt, ag[1]), pctrl->radTiltMin, pctrl->radTiltMax);
        ((float *)&s.pos)[2] = ag[0];
        ((float *)&s.pos)[1] = -ag[1];
        ((int *)&s.pos)[0] = 0;
        if (pctrl->fPrev) {
            qword d = s.pos;
            __asm__("vsub.xyzw %0, %0, %2\n\tqmtc2.ni %3, %1" : "+j"(d), "=j"(dt.q) : "j"(pctrl->pxf->pos0), "rV"(D_002DDED4));  /* "rV": MEM kept to reload, which loads it into the dying %hi reg */
            __asm__("vdiv Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, Q" : "=j"(vel) : "j"(dt.q), "j"(d) : "memory");
        } else {
            vel = D_002A2DD0;
        }
        s.vel = vel;
        pctrl->fPrev = 1;
    }
    pctrl->pxf->pos0 = s.pos;
    pctrl->pxf->vel0 = s.vel;
    pctrl->pxf->state = 3;
}
