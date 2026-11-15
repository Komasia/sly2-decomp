#include "cid.h"
#include "vtbl.h"
struct O { char pad[0xC]; VTENT *vt; };
struct T { char pad[0x180]; struct O *po; };
struct P { char pad[0xF1C]; struct O *xF1C; char pad2[0x13F0 - 0xF20]; struct T *x13F0; };
void func_00205D10(struct P *p, int b);
int FIsBasicDerivedFrom__FP5BASIC3CID(struct O *p, int n);
#define VCALL(o, n, ...) ((void (*)())(o)->vt[n].pfn)(VT_THIS((o), &(o)->vt[n]), __VA_ARGS__)
void func_001B81B8(struct P *p, int b)
{
    struct O *o;
    func_00205D10(p, b);
    if (b) {
        if (!p->x13F0) return;
        o = p->x13F0->po;
        if (!o) return;
        p->xF1C = o;
        VCALL(o, 21, 0);
        if (FIsBasicDerivedFrom__FP5BASIC3CID(p->xF1C, CID_STEP)) VCALL(p->xF1C, 87, b);
    } else {
        o = p->xF1C;
        if (!o) return;
        VCALL(o, 21, 1);
        if (FIsBasicDerivedFrom__FP5BASIC3CID(p->xF1C, CID_STEP)) VCALL(p->xF1C, 87, 0);
        p->xF1C = 0;
    }
}
