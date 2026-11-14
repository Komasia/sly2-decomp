/* class: a CTRL kind (ctrl.h; SafeHouse xf.h: vtable 0x2CA720, between CTRLTARGET 0x2CA6E0 and CTRLSOURCE 0x2CA760;
 * Fetch 0x12DEF0 computes the record's value from a matrix chain): its Query (vtable slot 5) - the record's value
 * (XF +0xC0), no velocity. */
#include "ctrl.h"

#ifndef SLY2_QWORD
#define SLY2_QWORD
typedef int qword __attribute__((mode(TI)));
#endif

typedef struct XFV {
    /* 0x00 */ char pad0[0xc0];
    /* 0xc0 */ qword qwValue;   /* the record's value */
} XFV;

typedef struct VEL3 { float x, y, z; } VEL3;

void func_0012DFE0(CTRL *pctrl, qword *ppos, VEL3 *pvel)
{
    if (ppos != 0) {
        *ppos = ((XFV *)pctrl->pxf)->qwValue;
    }
    if (pvel != 0) {
        pvel->z = 0.0f;
        pvel->y = 0.0f;
        pvel->x = 0.0f;
    }
}
