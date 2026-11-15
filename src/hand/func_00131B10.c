/* DemoteAsegaOnXf: the ASEGA's controller (kind 0, CTRLASEG, whose +0x24 is pasega) on the record gets priority -1
 * and the record's controllers are re-sorted. Layout: SafeHouse port (xf.h CTRLASEG, lo.h XF). */
struct CTRL { int kind; int pad[2]; int prio; struct CTRL *pnext; int pad2[4]; int pasega; };   /* field: SafeHouse port */
struct XF { char pad[0x90]; struct CTRL *pctrlFirst; };   /* field: SafeHouse port */
void SortXfCtrls__FP3ALOP2XF(int palo, struct XF *pxf);
// name: SafeHouse port (DemoteAsegaOnXf)
void DemoteAsegaOnXf__FiiP2XF(int pasega, int palo, struct XF *pxf)
{
    struct CTRL *pctrl = pxf->pctrlFirst;
    for (;;) {
        if (!pctrl)
            return;
        if (pctrl->kind == 0 && pctrl->pasega == pasega) {
            pctrl->prio = -1;
            SortXfCtrls__FP3ALOP2XF(palo, pxf);
            return;
        }
        pctrl = pctrl->pnext;
    }
}
