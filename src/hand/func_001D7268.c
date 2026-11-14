#include "vtbl.h"
struct S { int a, b, c; VTENT *vt; };
void func_001F36A8(struct S *p);
void func_001D7268(struct S *p) {
    VTENT *e;
    func_001F36A8(p);
    e = &p->vt[79];
    ((void (*)(void *, int))e->pfn)(VT_THIS(p, e), 0);
}
