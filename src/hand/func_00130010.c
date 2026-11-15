/* A scalar channel's target (the ASEG's second channel list, ASEGCHG {kind, oid}): the object oid, looked up nearest
 * to palo, else to the ASEG, and the address of its parameter of the channel's kind (its vt slot 43: for the camera
 * object the lens, 0x12E738); null when the object is missing. Layout: SafeHouse port (aseg.h ASEGCHG). */
#include "vtbl.h"
struct LO { int pad[3]; VTENT *vt; };
struct ASEGCHG { int kind; int oid; };   /* field: SafeHouse port (kind, n) */
extern char g_sw[];
struct LO *PloFindSwNearest__FP2LO3OIDii(void *psw, int grfFind, int oid, void *ploNear);
void func_00130010(void *paseg, void *palo, struct ASEGCHG *pchg, struct LO **pplo, int *ppg)
{
    if (palo)
        *pplo = PloFindSwNearest__FP2LO3OIDii(g_sw, 1, pchg->oid, palo);
    else
        *pplo = PloFindSwNearest__FP2LO3OIDii(g_sw, 4, pchg->oid, paseg);
    if (!*pplo)
        *ppg = 0;
    else {
        struct LO *plo = *pplo;
        *ppg = ((int (*)(void *, int))plo->vt[43].pfn)(VT_THIS(plo, &plo->vt[43]), pchg->kind);
    }
}
