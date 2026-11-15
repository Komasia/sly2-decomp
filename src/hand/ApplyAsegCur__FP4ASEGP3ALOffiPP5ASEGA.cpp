#include "vtbl.h"
struct ASEG; struct ALO;
struct ASEGA { int pad[3]; VTENT *vt; };
void RetractAsegaPp(ASEGA **);
void ApplyAseg(ASEG *paseg, ALO *paloRoot, float t, float svt, int grfapl, ASEGA **ppasega);
void ApplyAsegCur(ASEG *paseg, ALO *paloRoot, float t, float svt, int grfapl, ASEGA **ppasega)
{
    RetractAsegaPp(ppasega);
    if (paseg)
    {
        ApplyAseg(paseg, paloRoot, t, svt, grfapl, ppasega);
        ASEGA *pasega = *ppasega;
        ((void (*)(void *))pasega->vt[1].pfn)(VT_THIS(pasega, &pasega->vt[1]));
    }
}
