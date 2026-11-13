/* CTRL::Query (vt slot 5): the value / velocity a controller drives its record toward: the base gives the record's
 * own value (VecXfValue of its matrix) and no velocity (x, y, z cleared). Source: SafeHouse port (xf.cpp). */
#include "ctrl.h"

typedef int VU_VECTOR __attribute__((mode(TI)));   /* a 128-bit vector register */
struct MATRIX4;
struct VECTOR3 { float x, y, z; };
VU_VECTOR VecXfValue__FP2XFP7MATRIX4(struct XF *pxf, struct MATRIX4 *pmat);

// name: SafeHouse port (CTRL::Query)
void Query__4CTRLP7VECTOR4T1f(CTRL *pctrl, VU_VECTOR *ppos, struct VECTOR3 *pvel)
{
    if (ppos != 0) {
        struct XF *pxf = pctrl->pxf;
        *ppos = VecXfValue__FP2XFP7MATRIX4(pxf, (struct MATRIX4 *)pxf);   /* the record's matrix is its first field */
    }
    if (pvel != 0) {
        pvel->z = 0;
        pvel->y = 0;
        pvel->x = 0;
    }
}
