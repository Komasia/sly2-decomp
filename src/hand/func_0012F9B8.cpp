// MATCH (Claude agent, laneB6, 2026-10-23), from the 116/aligned-25 draft: (1) no f4/f2 locals (`(grfapl >> 2) & 1` and `grfapl & 2` at their uses), so the vtable address is hoisted into fp; (2) AddXfCtrl takes pnew as a 3rd argument; (3) pnew->xC before pnew->x14; (4) floats before ppasega in the prototype (prologue copy order).
#include "vtbl.h"
#include "dl.h"
struct POLY { float a, b, c; };
struct ASEGCHN { unsigned int grf; int ptrk; };   // {oid:20, isub:10, fDisabled (bit 30), fScalar (bit 31)}, track
struct ASEGCHG { int kind; int n; int ptrkg; };
struct ASEGEV { int a[4]; };
struct ASEG {
    int pframe; char pad4[0x50 - 4]; struct DL dlAsega; int cchn; struct ASEGCHN *achn; int cchg; struct ASEGCHG *achg; int prio;
    int fSound; int pad74; float svt; int pad7C; struct POLY polySuck; int pad8C; float gSuckMin; float gSuckMax; int cevStart; struct ASEGEV *aevStart; int cevTimed;
};
struct CTRLASEG { int kind; int palo; int pxf; int prio; int pnextXf; int mode; VTENT *pvt; int ptrkp; int ptrkg; struct ASEGA *pasega; struct CTRLASEG *pnext; };
struct ASEGAL { int ptrkg; int pg; int plo; int kind; struct ASEGAL *pnext; };
struct ASEGA {
    int pframe; int psidebag; int x8; VTENT *pvt; int cref; struct ASEG *paseg; int palo; float t; float tEvent; char pad24[0x34 - 0x24];
    struct CTRLASEG *pctrlFirst; struct ASEGAL *palink; int grfapl; float svt; float svtLocal; float svtAseg; float svtSuck; int iea; int pad54[2]; int n5C;
};
struct ASEGAREF { ASEGA *pasega; ASEGAREF(ASEGA *pasegaHeld) : pasega(pasegaHeld) { ((void (*)(ASEGA *))pasega->pvt[1].pfn)((ASEGA *)VT_THIS(pasega, &pasega->pvt[1])); }
    ~ASEGAREF() { ((void (*)(ASEGA *))pasega->pvt[2].pfn)((ASEGA *)VT_THIS(pasega, &pasega->pvt[2])); } };
extern "C" {
extern char D_003E1224[];
extern char D_003E1218[];
extern VTENT D_002CAF48[];
extern VTENT D_002CAF08[];
extern char D_002DE578[];
ASEGA *func_0011CCC0(void *);
void *s1_memset(void *, int, int) asm("memset");
float GSuck(void *) asm("GSuck__FPv");
void SetAsegaSpeed(ASEGA *, float) asm("SetAsegaSpeed__FP5ASEGAf");
void AppendDlEntry(void *, void *) asm("AppendDlEntry__FP2DLPv");
void func_00256EE0(ASEGA *, int);
void GetAsegChannelTarget(struct ASEG *, int, struct ASEGCHN *, int *, int *) asm("GetAsegChannelTarget__FP4ASEGP3ALOP7ASEGCHNPP3ALOPP2XF");
void SetAloIced(int, long) asm("SetAloIced__FP3ALOl");
void *func_0012E1F0(unsigned int);
void AddXfCtrl(int, int, void *) asm("AddXfCtrl__FP3ALOP2XFP4CTRL");
void func_00130010(struct ASEG *, int, struct ASEGCHG *, int *, int *);
void *func_0012CE50(unsigned int);
void SetAsegaEventSound(ASEGA *, int) asm("SetAsegaEventSound__FP5ASEGAi");
void FireAsegaEvent(ASEGA *, struct ASEGEV *) asm("FireAsegaEvent__FP5ASEGAP6ASEGEV");
void SnapAsegaXfs(ASEGA *, int) asm("SnapAsegaXfs__FP5ASEGAi");
void FireAsegaStartEvents(ASEGA *) asm("FireAsegaStartEvents__FP5ASEGA");
void UpdateAsegaIeaCur(ASEGA *) asm("UpdateAsegaIeaCur__FP5ASEGA");
}
static inline float GClamp(float g, float lo, float hi) { float r; if (g < lo) r = lo; else if (hi < g) r = hi; else r = g; return r; }
static inline float GEval(struct POLY *ppoly, float t) { return ppoly->a + t * (ppoly->b + t * ppoly->c); }

// Layout: SafeHouse port (asega.h ASEGA, sm.h ASEG, aseg.h ASEGCHN / ASEGCHG, xf.h CTRLASEG / asega.h ASEGAL).
// ASEGAREF holds a reference (vt slots 1 / 2) for the scope.
// ApplyAseg: a new ASEGA (an animation segment playing) for paseg on palo (null: the ASEG's own objects) from time t
// at speed svt: its speeds (the ASEG's, and the suck one from the suck history through the ASEG's clamped
// polynomial), into the global and the ASEG's lists; a controller (CTRLASEG, mode 7 seek when grfapl & 1, else 5
// snap) on the record of each enabled channel, a scalar link (ASEGAL) for each scalar channel; the start events,
// then the records snapped (grfapl & 4: seeking ones too) and the timed events from the start (grfapl & 2).
// name: SafeHouse port (ApplyAseg)
extern "C" void ApplyAseg__FP4ASEGiiffPP5ASEGA(struct ASEG *paseg, int palo, int grfapl, float t, float svt, ASEGA **ppasega)
{
    ASEGA *pasega = func_0011CCC0(D_003E1224);
    int i, j, k;
    s1_memset(pasega, 0, 0x60);
    pasega->pframe = 0;
    pasega->psidebag = 0;
    pasega->pvt = D_002CAF48;
    pasega->n5C = 0;
    pasega->paseg = paseg;
    pasega->palo = palo;
    pasega->t = t;
    pasega->grfapl = grfapl;
    pasega->svtAseg = paseg->svt;
    {
        pasega->svtSuck = GClamp(GEval(&paseg->polySuck, GSuck(D_002DE578)), paseg->gSuckMin, paseg->gSuckMax);
    }
    SetAsegaSpeed(pasega, svt);
    AppendDlEntry(D_003E1218, pasega);
    AppendDlEntry(&paseg->dlAsega, pasega);
    ((void (*)(ASEGA *))pasega->pvt[1].pfn)((ASEGA *)VT_THIS(pasega, &pasega->pvt[1]));
    ASEGAREF ref(pasega);
    func_00256EE0(pasega, paseg->pframe);   /* the ASEG's frame (handle set) */
    if (ppasega)
        *ppasega = pasega;
    for (i = 0; i < paseg->cchn; i++) {
        struct ASEGCHN *pe = &paseg->achn[i];
        if (!(pe->grf & 0x40000000)) {
            int a, b;
            GetAsegChannelTarget(paseg, palo, pe, &a, &b);
            if (b) {
                SetAloIced(a, 0);
                struct CTRLASEG *pnew = (struct CTRLASEG *)func_0012E1F0(0x2C);
                pnew->pvt = D_002CAF08;
                pnew->kind = 0;
                if (pe->grf & 0x80000000)
                    pnew->ptrkg = pe->ptrk;
                else
                    pnew->ptrkp = pe->ptrk;
                pnew->palo = a;
                pnew->pxf = b;
                pnew->prio = paseg->prio;
                pnew->mode = (grfapl & 1) ? 7 : 5;
                pnew->pasega = pasega;
                pnew->pnext = pasega->pctrlFirst;
                pasega->pctrlFirst = pnew;
                AddXfCtrl(a, b, pnew);
            }
        }
    }
    for (j = 0; j < paseg->cchg; j++) {
        struct ASEGCHG *pe = &paseg->achg[j];
        int a, b;
        func_00130010(paseg, palo, pe, &a, &b);
        if (b) {
            struct ASEGAL *pnew = (struct ASEGAL *)func_0012CE50(0x14);
            pnew->ptrkg = pe->ptrkg;
            pnew->pg = b;
            pnew->plo = a;
            pnew->kind = pe->kind;
            pnew->pnext = pasega->palink;
            pasega->palink = pnew;
            ASEGA *po = (ASEGA *)a;
            ((void (*)(ASEGA *, int))po->pvt[44].pfn)((ASEGA *)VT_THIS(po, &po->pvt[44]), pe->kind);
        }
    }
    SetAsegaEventSound(pasega, paseg->fSound);
    pasega->tEvent = t;
    for (k = 0; k < paseg->cevStart; k++)
        FireAsegaEvent(pasega, &paseg->aevStart[k]);
    pasega->t = pasega->tEvent;
    SnapAsegaXfs(pasega, (grfapl >> 2) & 1);
    if (grfapl & 2) {
        if (pasega->svt < 0.0f)
            pasega->iea = paseg->cevTimed;
        FireAsegaStartEvents(pasega);
    } else {
        UpdateAsegaIeaCur(pasega);
    }
    ((void (*)(ASEGA *, int, int, int, int, int))pasega->pvt[3].pfn)((ASEGA *)VT_THIS(pasega, &pasega->pvt[3]), 2, 0, 0, 0, 0);
}
