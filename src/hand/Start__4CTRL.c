/* CTRL::Start: a controller that becomes the head of its record sets the record's mode, then the record's
 * parameters are recomputed. */
#include "ctrl.h"

void SetXfMode(struct ALO *palo, struct XF *pxf, int mode) asm("SetXfMode__FP3ALOP2XFi");
void InvalidateXfParams(struct ALO *palo, struct XF *pxf) asm("InvalidateXfParams__FP3ALOP2XF");

// name: SafeHouse port (CTRL::Start)
void Start__4CTRL(CTRL *pctrl)
{
    SetXfMode(pctrl->palo, pctrl->pxf, pctrl->mode);
    InvalidateXfParams(pctrl->palo, pctrl->pxf);
}
