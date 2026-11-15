/* AppendAloExtraDraws (0x1A5EE8): draws the object once more at a matrix given in world space: turns it into the
 * object's frame (the inverse of vt slot 31's world matrix) and appends the draw (vt slot 20) with (0, g1, g2). */
#include "vtbl.h"
#define VT_MAT_WORLD (0xF8 / 8)  /* slot 31 */
#define VT_APPEND_DRAW (0xA0 / 8) /* slot 20 */
typedef int qword __attribute__((mode(TI)));
typedef struct { qword q[4]; } M4;
struct O { int x0, x4, x8; VTENT *vt; };
void InverseAffineMatrix4__FP7MATRIX4(M4 *out, void *in);
void MulMatrix4__FP7MATRIX4T0Pv(M4 *out, void *a, M4 *b);
// name: SafeHouse port (AppendAloExtraDraws)
void AppendAloExtraDraws__FP5SCENEP3ALOff(struct O *palo, void *pmat, float g1, float g2)
{
    M4 mat;
    M4 matLocal;
    M4 matInv;
    M4 *pmatLocal = &matLocal;
    M4 *pmatInv = &matInv;
    VTENT *e = &palo->vt[VT_MAT_WORLD];
    InverseAffineMatrix4__FP7MATRIX4(pmatInv, ((void *(*)(void *))e->pfn)(VT_THIS(palo, e)));
    MulMatrix4__FP7MATRIX4T0Pv(pmatLocal, pmat, pmatInv);
    mat = matLocal;
    e = &palo->vt[VT_APPEND_DRAW];
    ((void (*)(void *, M4 *, int, float, float))e->pfn)(VT_THIS(palo, e), &mat, 0, g1, g2);
}
