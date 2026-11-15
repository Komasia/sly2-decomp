/* CTRLASEG::Fetch: a position channel's controller gives its record the ASEGA's time as the parameter (pg = &t,
 * pdgScale = &svt) and lets the track set up the segment (TRKP vt slot 2 Setup); a controller without a position
 * track puts the record at rest (state 0, mode 0 XFM_Static, parameters reset). Layout: SafeHouse port (xf.h
 * CTRLASEG, lo.h XF, aseg.h TRKP). */
#include "vtbl.h"
struct XF { char pad[0x88]; int pg; int pdgScale; char pad2[0x9a - 0x90]; short state; };   /* field: SafeHouse port */
struct TRKP { VTENT *vt; };
struct CTRLASEG { int kind; int palo; struct XF *pxf; int pad[4]; struct TRKP *ptrkp; int ptrkg; int pasega; };   /* field: SafeHouse port */
void SetXfMode__FP3ALOP2XFi(int palo, struct XF *pxf, int mode);
void ResetXfParams__FP2XFPv(int palo, struct XF *pxf);
// name: SafeHouse port (CTRLASEG::Fetch)
void Fetch__8CTRLASEG(struct CTRLASEG *pctrl)
{
    if (pctrl->ptrkp) {
        struct TRKP *ptrkp;
        pctrl->pxf->pg = pctrl->pasega + 0x1c;         /* &pasega->t */
        pctrl->pxf->pdgScale = pctrl->pasega + 0x40;   /* &pasega->svt */
        ptrkp = pctrl->ptrkp;
        ((void (*)(void *, struct XF *))ptrkp->vt[2].pfn)(VT_THIS(ptrkp, &ptrkp->vt[2]), pctrl->pxf);   /* Setup */
    } else {
        pctrl->pxf->state = 0;
        SetXfMode__FP3ALOP2XFi(pctrl->palo, pctrl->pxf, 0);
        ResetXfParams__FP2XFPv(pctrl->palo, pctrl->pxf);
    }
}
