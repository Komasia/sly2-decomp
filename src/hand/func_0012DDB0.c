/* A new attach controller (kind 6) that holds the record at another record (+0x1C) times an offset matrix
 * (+0x20); added to the record. Its Fetch is 0x12DEF0, its Query 0x12DFE0. */
typedef struct M4 { int q[16]; } __attribute__((aligned(16))) M4;
typedef struct CTRLATTACH { int pad[7]; int pxfOther; M4 mat; } CTRLATTACH;
#define CTRLK_Attach 6
CTRLATTACH *func_0012DB50(int kind, void *palo, void *pxf, void *prio, void *mode);
void AddXfCtrl__FP3ALOP2XFP4CTRL(void *palo, void *pxf, CTRLATTACH *pctrl);
CTRLATTACH *func_0012DDB0(void *palo, void *pxf, void *prio, void *mode, int pxfOther, M4 *pmat)
{
    CTRLATTACH *pctrl = func_0012DB50(CTRLK_Attach, palo, pxf, prio, mode);
    pctrl->pxfOther = pxfOther;
    pctrl->mat = *pmat;
    AddXfCtrl__FP3ALOP2XFP4CTRL(palo, pxf, pctrl);
    return pctrl;
}
