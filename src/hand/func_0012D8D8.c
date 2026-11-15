/* CTRLSOURCE::Refresh: when the next controller of the record changed, the record's parameters are invalidated,
 * the old source is ended and the new one started. Layout: SafeHouse port (xf.h CTRLSOURCE). */
#include "vtbl.h"
typedef struct CTRL { int pad[6]; VTENT *vt; } CTRL;   /* a controller: its vtable at +0x18 */
typedef struct CTRLSOURCE {
    /* 0x00 */ int kind;
    /* 0x04 */ void *palo;      /* field: SafeHouse port */
    /* 0x08 */ void *pxf;       /* field: SafeHouse port */
    /* 0x0c */ int prio;
    /* 0x10 */ CTRL *pnext;     /* field: SafeHouse port */
    /* 0x14 */ int pad2[2];
    /* 0x1c */ CTRL *psrcCur;   /* field: SafeHouse port */
} CTRLSOURCE;
void InvalidateXfParams__FP3ALOP2XF(void *palo, void *pxf);
// name: SafeHouse port (CTRLSOURCE::Refresh)
void Refresh__10CTRLSOURCE(CTRLSOURCE *pctrl)
{
    CTRL *psrc;
    if (pctrl->psrcCur != pctrl->pnext) {
        InvalidateXfParams__FP3ALOP2XF(pctrl->palo, pctrl->pxf);
        psrc = pctrl->psrcCur;
        if (psrc)
            ((void (*)(void *))psrc->vt[2].pfn)(VT_THIS(psrc, &psrc->vt[2]));   /* End */
        psrc = pctrl->pnext;
        pctrl->psrcCur = psrc;
        if (psrc)
            ((void (*)(void *))psrc->vt[1].pfn)(VT_THIS(psrc, &psrc->vt[1]));   /* Start */
    }
}
