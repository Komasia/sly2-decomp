/* SetBentleyCarried: Bentley's carried state (+0x1800: -1 none, 0 held by Murray's throw controller, 1 thrown).
 * Leaving 0 he is reparented back and his position / rotation controllers are deleted; leaving 1 he faces his step
 * heading. Entering -1 Murray's throw (when Murray is in state 15) goes back to 0; entering 0 he is attached to Murray
 * at the matrix his throw controller gives (vt slot 32) with no velocity and kept there by two position controllers (0x12DC18); then
 * the state's animation. Layout: SafeHouse port (gang.h BENTLEY / MURRAY). */
#include "vtbl.h"
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; qword pos; } M4;
struct XF { char pad[0xA0]; void *pxfRef; };   /* field: SafeHouse port */
struct MURRAY { char pad[0x13D0]; int state; char pad2[0x1910 - 0x13D4]; int jtthrow1910; int nJtthrowState; char pad3[4]; struct Q *pq; };   /* field: SafeHouse port (gang.h MURRAY jtthrow1910) */
struct Q { char pad[0xC]; VTENT *vt; };
struct BENTLEY {
    char pad[0xC]; VTENT *vt; char pad1[0x54 - 0x10]; struct XF *pxfP54; struct XF *pxfPos; struct XF *pxfRot;
    char pad2[0x1A4 - 0x60]; int n1A4; char pad3[0x9E4 - 0x1A8]; int n9E4;
    char pad4[0x1030 - 0x9E8]; int pasega1030; int psma1034; char pad5[0x1800 - 0x1038];
    int n1800; float t1804; void *apasegCarried[2]; void *pctrlPos; void *pctrlRot;
};
extern struct MURRAY *D_002F7900;   /* the world's Murray */
#include "clock.h"
extern qword D_002A2DD0;
void ReparentBooty__FP3ALOii(struct BENTLEY *, int, int);
void DeleteCtrl__FPP4CTRL(void *);
void SetXfMode__FP3ALOP2XFi(struct BENTLEY *, struct XF *, int);
float RadStepHeading__FP4STEP(struct BENTLEY *);
void SetStepPhysHeading__FP3ALOf(struct BENTLEY *, float);
void TurnActorNow__FP5ACTOR(struct BENTLEY *);
void SetJtThrowState__FP7JTTHROWi(void *, int);
M4 func_0022FF40(void *, void *, M4 *);
void *PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR(struct BENTLEY *pbentley, struct XF *pso, int a, int b, int c, qword q);
qword DecomposeEulerMatrix__FP7MATRIX3(M4 *pm);
void ClearSmaHandle__FPP3SMA(void *);
void ApplyAsegCur(void *, struct BENTLEY *, int, void *, float, float) asm("ApplyAsegCur__FP4ASEGP3ALOffiPP5ASEGA");

// name: SafeHouse port (SetBentleyCarried)
void SetBentleyCarried__FP7BENTLEYi(struct BENTLEY *pbentley, int n)
{
    void *paseg;
    if (n == pbentley->n1800)
        return;
    switch (pbentley->n1800) {
    case 0: {
        int save = pbentley->n9E4;
        ReparentBooty__FP3ALOii(pbentley, 0, 0xF);
        pbentley->n9E4 = save;
        DeleteCtrl__FPP4CTRL(&pbentley->pctrlPos);
        DeleteCtrl__FPP4CTRL(&pbentley->pctrlRot);
        SetXfMode__FP3ALOP2XFi(pbentley, pbentley->pxfPos, 2);
        SetXfMode__FP3ALOP2XFi(pbentley, pbentley->pxfRot, 2);
        break;
    }
    case 1:
        SetStepPhysHeading__FP3ALOf(pbentley, RadStepHeading__FP4STEP(pbentley));
        pbentley->n1A4 = 0;
        TurnActorNow__FP5ACTOR(pbentley);
        break;
    }
    pbentley->n1800 = n;
    pbentley->t1804 = g_clock.t;
    paseg = pbentley->apasegCarried[n];
    switch (n) {
    case -1: {
        struct MURRAY *pmurray = D_002F7900;
        if (pmurray->state != 0xF)
            return;
        if (pmurray->nJtthrowState == 7)
            return;
        SetJtThrowState__FP7JTTHROWi(&pmurray->jtthrow1910, 0);
        return;
    }
    case 0: {
        M4 m;
        int n;
        struct Q *pq = D_002F7900->pq;
        n = ((int (*)(void *, M4 *))pq->vt[32].pfn)(VT_THIS(pq, &pq->vt[32]), &m);
        { M4 t = func_0022FF40(pbentley->pxfP54->pxfRef, pbentley->pxfPos->pxfRef, &m); m = t; }
        {
            int save = pbentley->n9E4;
            ((void (*)(void *, struct MURRAY *, int, int))pbentley->vt[10].pfn)(VT_THIS(pbentley, &pbentley->vt[10]), D_002F7900, n, 3);
            pbentley->n9E4 = save;
        }
        ((void (*)(void *, qword))pbentley->vt[35].pfn)(VT_THIS(pbentley, &pbentley->vt[35]), D_002A2DD0);
        ((void (*)(void *, qword))pbentley->vt[36].pfn)(VT_THIS(pbentley, &pbentley->vt[36]), D_002A2DD0);
        pbentley->pctrlPos = PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR(pbentley, pbentley->pxfPos, 1, 7, 2, m.pos);
        pbentley->pctrlRot = PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR(pbentley, pbentley->pxfRot, 1, 7, 2, DecomposeEulerMatrix__FP7MATRIX3(&m));
        break;
    }
    case 1:
        pbentley->n1A4 = -1;
        break;
    }
    ClearSmaHandle__FPP3SMA(&pbentley->psma1034);
    ApplyAsegCur(paseg, pbentley, 9, &pbentley->pasega1030, 0.0f, 1.0f);
    ((void (*)(void *))pbentley->vt[90].pfn)(VT_THIS(pbentley, &pbentley->vt[90]));
}
