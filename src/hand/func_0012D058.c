/* FXfHasCtrl: whether the controller is on its record's controller list (XF +0x90, linked by CTRL +0x10).
 * Layout: SafeHouse port (xf.h CTRL, lo.h XF). */
typedef struct CTRL { int pad[4]; struct CTRL *pnext; } CTRL;   /* +0x10; field: SafeHouse port */
typedef struct XF { int pad[0x24]; CTRL *pctrlFirst; } XF;     /* +0x90; field: SafeHouse port */
typedef struct CTRLX { int pad[2]; XF *pxf; } CTRLX;
// name: SafeHouse port (FXfHasCtrl)
int FXfHasCtrl__FP2XF(CTRLX *pctrl)
{
    CTRL *pctrlCur = pctrl->pxf->pctrlFirst;
    while (pctrlCur) {
        if (pctrlCur == (CTRL *)pctrl)
            return 1;
        pctrlCur = pctrlCur->pnext;
    }
    return 0;
}
