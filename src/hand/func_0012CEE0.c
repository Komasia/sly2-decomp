/* CTRL::FFirst: whether this controller drives its record: it is the record's head controller, or the head is a
 * source controller (kind 5, CTRLSOURCE) forwarding to it. Layout: SafeHouse port (xf.h CTRL / CTRLSOURCE, lo.h XF). */
typedef struct CTRL {
    /* 0x00 */ int kind;                 /* field: SafeHouse port */
    /* 0x04 */ int pad4[6];
    /* 0x1c */ struct CTRL *psrcCur;     /* field: SafeHouse port - CTRLSOURCE: the controller it forwards to */
} CTRL;
typedef struct XF { int pad[0x24]; CTRL *pctrlFirst; } XF;   /* +0x90; field: SafeHouse port */
typedef struct CTRLX { int pad[2]; XF *pxf; } CTRLX;
#define CTRLK_Source 5
// name: SafeHouse port (CTRL::FFirst)
int FFirst__4CTRL(CTRLX *pctrl)
{
    CTRL *pctrlHead = pctrl->pxf->pctrlFirst;
    if (pctrlHead == (CTRL *)pctrl)
        return 1;
    if (pctrlHead && pctrlHead->kind == CTRLK_Source && pctrlHead->psrcCur == (CTRL *)pctrl)
        return 1;
    return 0;
}
