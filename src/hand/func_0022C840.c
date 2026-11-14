#include "vtbl.h"
struct O { int a[3]; VTENT *vt; };
struct Q { char pad[0x80]; float a, b; void *pa, *pb; char pad2[8]; short k; short l; };
extern float D_002A98D0;
extern char D_002C44E0[];
// name: SafeHouse port (InvalidateXfParams)
void InvalidateXfParams__FP3ALOP2XF(struct O *p, struct Q *q)
{
    switch (q->k) {
    case 0: case 1: case 2: case 3: case 13: case 14: case 15: case 16: case 20: case 21:
        break;
    default:
        q->b = D_002A98D0;
        q->a = D_002A98D0;
        q->pb = D_002C44E0;
        q->pa = D_002C44E0;
        break;
    }
    q->l = 0;
    ((void (*)())p->vt[47].pfn)(VT_THIS(p, &p->vt[47]), 4);
}
