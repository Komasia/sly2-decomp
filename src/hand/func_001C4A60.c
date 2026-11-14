#include "vtbl.h"
struct LO;
struct LO { char pad[0xC]; VTENT *vt; };
struct G { char pad[0x3EFC]; struct LO *plo3EFC; struct LO *plo3F00; };
struct LO *func_001C4A48(struct G *p);
#define VCALL(o, n, a) ((void (*)(void *, int))(o)->vt[n].pfn)(VT_THIS((o), &(o)->vt[n]), a)
// name: SafeHouse port (SetPoForced)
void SetPoForced__FP2SWP2LO(struct G *p, struct LO *plo)
{
    struct LO *cur = func_001C4A48(p);
    struct LO *nw = plo;
    if (!nw) nw = p->plo3EFC;
    if (cur != nw && cur) VCALL(cur, 78, 0);
    p->plo3F00 = plo;
    if (cur != nw && nw) VCALL(nw, 78, 1);
}
