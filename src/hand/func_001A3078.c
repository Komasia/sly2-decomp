#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; };
struct S { struct O *po; };
extern char D_004435F0[];
void func_00227788(void *p);
// name: SafeHouse port (ShowSubtitleBox)
void ShowSubtitleBox__FP9DIALOGSUB(struct S *p)
{
    if (p->po) {
        struct O *o;
        VTENT *e;
        func_00227788(D_004435F0);
        o = p->po;
        e = &o->vt[49];
        ((void (*)(void *, int))e->pfn)(VT_THIS(o, e), -1);
    }
}
