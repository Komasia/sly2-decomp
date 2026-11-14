#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; };
struct E { struct O *po; int pad[3]; };
struct P { char pad[0x30C]; int c; int pad2; struct E ae[1]; };
// name: SafeHouse port (ResetCm)
void ResetCm__FP2CM(struct P *p)
{
    int i;
    for (i = 0; i < p->c; i++) {
        struct O *o = p->ae[i].po;
        VTENT *e = &o->vt[7];
        ((void (*)(void *))e->pfn)(VT_THIS(o, e));
    }
    *(int *)((char *)p + 0x620) = 0;
    *(float *)((char *)p + 0x624) = 10.0f;
}
