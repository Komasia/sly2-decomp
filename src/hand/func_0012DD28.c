/* A new joint controller (kind 7) for one record of a two-bone joint (ALOPAIR, made by 0x186670): mode 14 for the
 * joint's lower bone (pair +0x8), 13 (XFM_Joint) otherwise; added to the record. SafeHouse port (ik.h, xf.h XFM). */
typedef struct CTRLJOINT { int pad[7]; void *ppair; } CTRLJOINT;
typedef struct ALOPAIR { int pad[2]; void *pxfLower; } ALOPAIR;   /* apxf[2]; field: SafeHouse port */
#define CTRLK_Joint 7
#define XFM_Joint 0xD
#define XFM_Joint14 0xE
CTRLJOINT *func_0012DB50(int kind, void *palo, void *pxf, void *prio, int mode);
void AddXfCtrl__FP3ALOP2XFP4CTRL(void *palo, void *pxf, CTRLJOINT *pctrl);
CTRLJOINT *func_0012DD28(void *palo, void *pxf, void *prio, ALOPAIR *ppair)
{
    CTRLJOINT *pctrl = func_0012DB50(CTRLK_Joint, palo, pxf, prio, pxf == ppair->pxfLower ? XFM_Joint14 : XFM_Joint);
    pctrl->ppair = ppair;
    AddXfCtrl__FP3ALOP2XFP4CTRL(palo, pxf, pctrl);
    return pctrl;
}
