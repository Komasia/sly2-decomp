/* CTRLTARGET::Fetch: a fixed target with velocity: the record's segment becomes {pos, vel} (+0xC0 / +0xD0) with the
 * arrival time (+0xA8), state 2 (fixed), and the record's parameters are reset. Layout: SafeHouse port (xf.h
 * CTRLTARGET, lo.h XF). */
#include "ctrl.h"
#include "vec.h"

struct XF {
    /* 0x00 */ char pad0[0x9a];
    /* 0x9a */ short state;            /* field: SafeHouse port - the target's source (2: fixed) */
    /* 0x9c */ char pad9c[0xa8 - 0x9c];
    /* 0xa8 */ float tTarget;          /* field: SafeHouse port - the arrival time */
    /* 0xac */ char padac[0xc0 - 0xac];
    /* 0xc0 */ struct VECTOR4 aseg[2]; /* field: SafeHouse port - value 0, slope 0 */
};
struct CTRLTARGET {
    /* 0x00 */ CTRL ctrl;
    /* 0x18 */ char pad18[0x1c - 0x18];
    /* 0x1c */ float tArrive;          /* field: SafeHouse port */
    /* 0x20 */ struct VECTOR4 pos;     /* field: SafeHouse port */
    /* 0x30 */ struct VECTOR4 vel;     /* field: SafeHouse port */
};
void ResetXfParams(struct ALO *palo, struct XF *pxf) asm("ResetXfParams__FP2XFPv");

// name: SafeHouse port (CTRLTARGET::Fetch)
void Fetch__10CTRLTARGET(struct CTRLTARGET *pctrl)
{
    pctrl->ctrl.pxf->tTarget = pctrl->tArrive;
    pctrl->ctrl.pxf->aseg[0] = pctrl->pos;
    pctrl->ctrl.pxf->aseg[1] = pctrl->vel;
    pctrl->ctrl.pxf->state = 2;
    ResetXfParams(pctrl->ctrl.palo, pctrl->ctrl.pxf);
}
