#include "cid.h"
#include "vtbl.h"
struct O { int a, b, c; VTENT *vt; };
struct G;
extern struct G g_sw;
int CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(struct G *, int, int, int, int, struct O **);
// name: SafeHouse port (NotifyPlayersPowerups)
void NotifyPlayersPowerups__Fv(void) {
    struct O *ap[8];
    int c, i;
    c = CFindObjectsByClass__FP5BASICiiPP5BASICiPP2LO(&g_sw, 5, CID_ACTOR, 0, 8, ap);
    for (i = 0; i < c; i++) { struct O *o = ap[i]; VTENT *e = &o->vt[104]; ((void (*)(void *))e->pfn)(VT_THIS(o, e)); }
}
