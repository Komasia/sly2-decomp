/* ExplodeExplsExplso: an explosion with sound bursts by firing (vtable slot 52, FireExplsExplso). */
#include "vtbl.h"
struct EXPLS { int a[3]; VTENT *vt; };
void ExplodeExplsExplso__FP5EXPLSP6EXPLSO(struct EXPLS *pexpls, struct EXPLSO *pexplso)
{
    VTENT *pvte = &pexpls->vt[52];
    ((void (*)())pvte->pfn)(VT_THIS(pexpls, pvte), pexplso);
}
