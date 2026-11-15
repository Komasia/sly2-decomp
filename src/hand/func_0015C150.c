/* ExplodeExpl: burst an explosion with its own settings (an empty EXPLSO through vtable slot 51, ExplodeXxxExplso). */
#include "vtbl.h"
#include "h2_explso.h"
struct EXPL { int a[3]; VTENT *vt; };
void s1_memset(void *pv, int b, int cb) asm("memset");
void ExplodeExpl__FP4EXPL(struct EXPL *pexpl)
{
    EXPLSO explso = {0};
    VTENT *pvte;

    pvte = pexpl->vt;
    ((void (*)())pvte[51].pfn)(VT_THIS(pexpl, &pvte[51]), &explso);
}
