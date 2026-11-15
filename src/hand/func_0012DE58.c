/* PctrlNewTarget: a new target controller (kind 8, mode 0x11 XFM_Spline) with the arrival time, position and
 * velocity, added to the record. Layout: SafeHouse port (xf.h CTRLTARGET). */
typedef int qword __attribute__((mode(TI)));
typedef struct CTRLTARGET {
    /* 0x00 */ char pad[0x1C];
    /* 0x1c */ float tArrive;   /* field: SafeHouse port */
    /* 0x20 */ qword pos;       /* field: SafeHouse port */
    /* 0x30 */ qword vel;       /* field: SafeHouse port */
} CTRLTARGET;
#define CTRLK_Target 8
#define XFM_Spline 0x11
CTRLTARGET *func_0012DB50(int kind, void *palo, void *pxf, void *prio, int mode);
void AddXfCtrl__FP3ALOP2XFP4CTRL(void *palo, void *pxf, void *pctrl);
// name: SafeHouse port (PctrlNewTarget)
CTRLTARGET *PctrlNewTarget__FP3ALOP2XFPvfG9VU_VECTORT4(void *palo, void *pxf, void *prio, float tArrive, qword pos, qword vel)
{
    CTRLTARGET *pctrl = func_0012DB50(CTRLK_Target, palo, pxf, prio, XFM_Spline);
    pctrl->tArrive = tArrive;
    pctrl->pos = pos;
    pctrl->vel = vel;
    AddXfCtrl__FP3ALOP2XFP4CTRL(palo, pxf, pctrl);
    return pctrl;
}
