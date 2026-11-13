/* CTRLASEG::End: an animation channel's controller with a weight track (+0x20) clears its record's pair's weight
 * pointers (the record's +0xA8, +0xD0 / +0xD4); otherwise the base end. Layout: SafeHouse port (xf.h CTRLASEG). */
#include "ctrl.h"

struct ALOPAIR {
    /* 0x00 */ char pad0[0xd0];
    /* 0xd0 */ void *ptrkgWeight;   /* field: SafeHouse port */
    /* 0xd4 */ float *ptWeight;     /* field: SafeHouse port */
};
struct XF {
    /* 0x00 */ char pad0[0xa8];
    /* 0xa8 */ struct ALOPAIR *ppair;   /* field: SafeHouse port (pvA8) */
};
struct CTRLASEG {
    /* 0x00 */ CTRL ctrl;
    /* 0x18 */ char pad18[0x1c - 0x18];
    /* 0x1c */ void *ptrkp;         /* field: SafeHouse port */
    /* 0x20 */ void *ptrkg;         /* field: SafeHouse port */
};
void func_0012CED8(struct CTRLASEG *pctrl);   /* CTRL::End (empty) */

// name: SafeHouse port (CTRLASEG::End)
void End__8CTRLASEG(struct CTRLASEG *pctrl)
{
    if (pctrl->ptrkg) {
        pctrl->ctrl.pxf->ppair->ptrkgWeight = 0;
        pctrl->ctrl.pxf->ppair->ptWeight = 0;
        return;
    }
    func_0012CED8(pctrl);
}
