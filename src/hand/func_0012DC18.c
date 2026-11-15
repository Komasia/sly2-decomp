/* PctrlNewPos: a new position controller (kind 1) with its mode, state and resting position, added to the
 * record. Layout: SafeHouse port (xf.h CTRLPOS). */
typedef int qword __attribute__((mode(TI)));
typedef struct CTRLPOS {
    /* 0x00 */ char pad[0x1C];
    /* 0x1c */ int state;   /* field: SafeHouse port */
    /* 0x20 */ qword pos;   /* field: SafeHouse port */
} CTRLPOS;
#define CTRLK_Pos 1
CTRLPOS *func_0012DB50(int kind, void *palo, void *pxf, void *prio, int mode);
void AddXfCtrl__FP3ALOP2XFP4CTRL(void *palo, void *pxf, void *pctrl);
// name: SafeHouse port (PctrlNewPos)
CTRLPOS *PctrlNewPos__FP3ALOP2XFPviiG9VU_VECTOR(void *palo, void *pxf, void *prio, int mode, int state, qword pos)
{
    CTRLPOS *pctrl = func_0012DB50(CTRLK_Pos, palo, pxf, prio, mode);
    pctrl->state = state;
    pctrl->pos = pos;
    AddXfCtrl__FP3ALOP2XFP4CTRL(palo, pxf, pctrl);
    return pctrl;
}
