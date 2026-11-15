/* RetractAsegaPp: *ppasega (if any) is retracted, its reference released (vt slot 2) and the pointer cleared.
 * SafeHouse port (asega.h). */
#include "vtbl.h"
struct ASEGA { int pad[3]; VTENT *vt; };
void RetractAsega__FP5ASEGA(struct ASEGA *pasega);
// name: SafeHouse port (RetractAsegaPp)
void RetractAsegaPp__FPP5ASEGA(struct ASEGA **ppasega)
{
    if (*ppasega) {
        struct ASEGA *pasega;
        VTENT *vt;
        RetractAsega__FP5ASEGA(*ppasega);
        pasega = *ppasega; vt = pasega->vt; ((void (*)(void *))vt[2].pfn)(VT_THIS(pasega, &vt[2]));
        *ppasega = 0;
    }
}
