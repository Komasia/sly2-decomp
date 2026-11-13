/* CTRLPOS::Fetch: the record rests at a value: the segment becomes {pos, 0} with the controller's state, and the
 * record's parameters are reset. Layout: SafeHouse port (xf.h CTRLPOS, lo.h XF). */
#include "ctrl.h"
#include "vec.h"

struct XF {
    /* 0x00 */ char pad0[0x9a];
    /* 0x9a */ unsigned short state;   /* field: SafeHouse port - the target's source */
    /* 0x9c */ char pad9c[0xc0 - 0x9c];
    /* 0xc0 */ struct VECTOR4 aseg[2]; /* field: SafeHouse port - value 0, slope 0 */
};
struct CTRLPOS {
    /* 0x00 */ CTRL ctrl;
    /* 0x18 */ char pad18[0x1c - 0x18];
    /* 0x1c */ unsigned short state;   /* field: SafeHouse port */
    /* 0x1e */ char pad1e[0x20 - 0x1e];
    /* 0x20 */ struct VECTOR4 pos;     /* field: SafeHouse port */
};
extern struct VECTOR4 D_002A2DD0;   /* the zero vector */
void ResetXfParams(struct ALO *palo, struct XF *pxf) asm("ResetXfParams__FP2XFPv");

// name: SafeHouse port (CTRLPOS::Fetch)
void Fetch__7CTRLPOS(struct CTRLPOS *pctrl)
{
    pctrl->ctrl.pxf->aseg[0] = pctrl->pos;
    pctrl->ctrl.pxf->aseg[1] = D_002A2DD0;
    pctrl->ctrl.pxf->state = pctrl->state;
    ResetXfParams(pctrl->ctrl.palo, pctrl->ctrl.pxf);
}
