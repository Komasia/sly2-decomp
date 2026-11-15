/* SetAsegaTime: an animation segment's speed (svt times its ASEG and suck speeds) and time: seek 0 absolute, 1
 * relative to now, 2 from the ASEG's end (tMax + g). A new time wraps, the timed event index follows, and each of its
 * controllers that drives its record re-fetches the record's segment when the record's parameter left [g0, g1] and
 * holds the record's mode; then the records snap. Layout: SafeHouse port (asega.h ASEGA, xf.h CTRLASEG, lo.h XF). */
#include "vtbl.h"
struct XF { char pad[0x80]; float g0; float g1; float *pg; };
struct CTRLASEG { int kind; void *palo; struct XF *pxf; int prio; int pnext; int mode; VTENT *vt; int ptrkp; int ptrkg; int pasega; struct CTRLASEG *pnextAsega; };
struct ASEG { char pad[0x74]; float tMax; };
struct ASEGA { int pad[5]; struct ASEG *paseg; int palo; float t; float tEvent; char pad1[0x34 - 0x24]; struct CTRLASEG *pctrlFirst; char pad2[0x40 - 0x38];
    float svt; float svtLocal; float svtAseg; float svtSuck; };
int FAsegaRetracted(struct ASEGA *pasega) asm("FAsegaRetracted__FP5ASEGA");
void FWrapAsegaTime__FP5ASEGAPfT1(struct ASEGA *pasega, float *pt, float *psvt);
void UpdateAsegaIeaCur(struct ASEGA *pasega) asm("UpdateAsegaIeaCur__FP5ASEGA");
int FFirst__4CTRL(struct CTRLASEG *pctrl);
void HoldXfMode(void *palo, struct XF *pxf);
void SnapAsegaXfs__FP5ASEGAi(struct ASEGA *pasega, int n);
// name: SafeHouse port (SetAsegaTime)
void SetAsegaTime__FP5ASEGAiff(struct ASEGA *pasega, int seek, float g, float svt)
{
    float t;
    if (FAsegaRetracted(pasega))
        return;
    pasega->svtLocal = svt;
    pasega->svt = svt * pasega->svtAseg * pasega->svtSuck;
    switch (seek) {
    case 0: t = g; break;
    case 1: t = pasega->t + g; break;
    case 2: t = pasega->paseg->tMax + g; break;
    }
    if (t != pasega->t) {
        struct CTRLASEG *pctrl;
        pasega->t = t;
        FWrapAsegaTime__FP5ASEGAPfT1(pasega, &pasega->t, &pasega->svt);
        UpdateAsegaIeaCur(pasega);
        for (pctrl = pasega->pctrlFirst; pctrl; pctrl = pctrl->pnextAsega) {
            if (FFirst__4CTRL(pctrl)) {
                struct XF *pxf = pctrl->pxf;
                float gXf = *pxf->pg;
                if (gXf < pxf->g0 || pxf->g1 < gXf)
                    ((void (*)(void *))pctrl->vt[4].pfn)(VT_THIS(pctrl, &pctrl->vt[4]));
                HoldXfMode(pctrl->palo, pctrl->pxf);
            }
        }
        SnapAsegaXfs__FP5ASEGAi(pasega, 0);
    }
    pasega->tEvent = pasega->t;
}
