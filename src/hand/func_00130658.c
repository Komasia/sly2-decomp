#include "vtbl.h"
struct O { int pad[3]; VTENT *vt; };
void RetractAsega__FP5ASEGA(struct O *);
// name: SafeHouse port (RetractAsegaPp)
void RetractAsegaPp__FPP5ASEGA(struct O **pp) {
    if (*pp) {
        struct O *p; VTENT *vt;
        RetractAsega__FP5ASEGA(*pp);
        p = *pp; vt = p->vt; ((void (*)(void *))vt[2].pfn)(VT_THIS(p, &vt[2])); *pp = 0;
    }
}
