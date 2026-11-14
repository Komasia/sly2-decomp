#include "vtbl.h"
struct O { int pad[3]; VTENT *vt; };
void func_001306A8(struct O **pp) {
    struct O *p = *pp;
    if (p) { VTENT *vt = p->vt; ((void (*)(void *))vt[2].pfn)(VT_THIS(p, &vt[2])); *pp = 0; }
}
