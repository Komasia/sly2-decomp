/* ExplodeExplParams: burst an explosion with the given overrides (grfexplso says which apply), through vtable slot 51. */
#include "vtbl.h"
#include "h2_explso.h"
struct EXPL { int a[3]; VTENT *vt; };
void ExplodeExplParams__FP4EXPLUiP3ALOP6VECTORT3ff(struct EXPL *pexpl, int grfexplso, void *paloReference, float rScale,
                                                  float sRadius, qword vec, qword posOrigin)
{
    EXPLSO explso;
    VTENT *pvte;
    explso.grfexplso = grfexplso;
    explso.paloReference = paloReference;
    explso.rScale = rScale;
    explso.sRadius = sRadius;
    explso.vec = vec;
    explso.posOrigin = posOrigin;
    pvte = &pexpl->vt[51];
    ((void (*)())pvte->pfn)(VT_THIS(pexpl, pvte), &explso);
}
