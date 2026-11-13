/* CTRLTARGET::SetGoal: a new target position and velocity (VU_VECTORs passed by value in quadword registers); when
 * this controller is the record's first, the record's live segment (+0xC0 / +0xD0) is refreshed too.
 * Layout: SafeHouse port (xf.h CTRLTARGET, lo.h XF). */
#include "ctrl.h"

typedef int VU_VECTOR __attribute__((mode(TI)));   /* a 128-bit vector register */
struct XF {
    /* 0x00 */ char pad0[0x90];
    /* 0x90 */ CTRL *pctrlFirst;       /* field: SafeHouse port */
    /* 0x94 */ char pad94[0xc0 - 0x94];
    /* 0xc0 */ VU_VECTOR aseg[2];      /* field: SafeHouse port - value 0, slope 0 */
};
struct CTRLTARGET {
    /* 0x00 */ CTRL ctrl;
    /* 0x18 */ char pad18[0x20 - 0x18];
    /* 0x20 */ VU_VECTOR pos;          /* field: SafeHouse port */
    /* 0x30 */ VU_VECTOR vel;          /* field: SafeHouse port */
};

// name: SafeHouse port (CTRLTARGET::SetGoal)
void SetGoal__10CTRLTARGETG9VU_VECTORT1(struct CTRLTARGET *pctrl, VU_VECTOR pos, VU_VECTOR vel)
{
    struct XF *pxf = pctrl->ctrl.pxf;
    pctrl->pos = pos;
    pctrl->vel = vel;
    if ((CTRL *)pctrl == pxf->pctrlFirst) {
        pxf->aseg[0] = pos;
        pctrl->ctrl.pxf->aseg[1] = vel;
    }
}
