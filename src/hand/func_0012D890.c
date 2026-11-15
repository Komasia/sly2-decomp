/* CTRLSOURCE::End: the controller it forwards to is ended and forgotten. Layout: SafeHouse port (xf.h). */
#include "vtbl.h"
typedef struct CTRL { int pad[6]; VTENT *vt; } CTRL;   /* a controller: its vtable at +0x18 */
typedef struct CTRLSOURCE { int pad[7]; CTRL *psrcCur; } CTRLSOURCE;   /* +0x1C; field: SafeHouse port */
// name: SafeHouse port (CTRLSOURCE::End)
void End__10CTRLSOURCE(CTRLSOURCE *pctrl)
{
    CTRL *psrc = pctrl->psrcCur;
    if (psrc) {
        ((void (*)(void *))psrc->vt[2].pfn)(VT_THIS(psrc, &psrc->vt[2]));   /* End */
        pctrl->psrcCur = 0;
    }
}
