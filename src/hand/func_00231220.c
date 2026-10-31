/* func_00231220 (0x231220): XFM virtual slot 49: translate a link to one of pxfmBase's parent SO's XFs into the
 * XF with the same index in pxfm's parent SO (XF arrays are 0x100 bytes per entry), keeping its self-pointer
 * fields pointing into the new XF. */
#include "so.h"

void func_00231220(XFM *pxfm, XFM *pxfmBase, XF **ppxf)
{
    XF *pxfOld = *ppxf;
    SO *psoBase;
    XF *pxf;
    int ixf;

    if (pxfOld != NULL) {
        psoBase = pxfmBase->lo.psoParent;
        ixf = (int)((char *)pxfOld - (char *)psoBase->axf) >> 8;
        pxf = NULL;
        if (ixf >= 0 && ixf < psoBase->cxf)
            pxf = pxfm->lo.psoParent->axf + ixf;
        if (pxf->pnUnk88 == &pxfOld->nUnk80)
            pxf->pnUnk88 = &pxf->nUnk80;
        if (pxf->pnUnk8C == &pxfOld->nUnk84)
            pxf->pnUnk88 = &pxf->nUnk84;   /* sic: the game stores to pnUnk88 here too */
        *ppxf = pxf;
    }
}
