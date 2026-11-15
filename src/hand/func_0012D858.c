/* CTRLSOURCE::Start: the source controller starts forwarding to the next controller of its record's list
 * (+0x10), which is started too. Layout: SafeHouse port (xf.h CTRLSOURCE). */
#include "vtbl.h"
typedef struct CTRL { int pad[6]; VTENT *vt; } CTRL;   /* a controller: its vtable at +0x18 */
typedef struct CTRLSOURCE {
    /* 0x00 */ int pad[4];
    /* 0x10 */ CTRL *pnext;     /* field: SafeHouse port - the next controller of the record */
    /* 0x14 */ int pad2[2];
    /* 0x1c */ CTRL *psrcCur;   /* field: SafeHouse port - the controller it forwards to */
} CTRLSOURCE;
// name: SafeHouse port (CTRLSOURCE::Start)
void Start__10CTRLSOURCE(CTRLSOURCE *pctrl)
{
    CTRL *psrc = pctrl->pnext;
    pctrl->psrcCur = psrc;
    if (psrc)
        ((void (*)(void *))psrc->vt[1].pfn)(VT_THIS(psrc, &psrc->vt[1]));   /* Start */
}
