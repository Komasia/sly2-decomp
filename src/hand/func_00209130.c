/* ResolveKinde (0x209130): resolves a guard kind entry: a KIND2 / KIND3 resolves its clips; otherwise its oid is
 * looked up near the guard (FSO_FindNearest): an ASEG with a launch event 0x22 becomes a KIND2 around it, another ASEG stays
 * an ASEG entry, an SM an SM entry (unset ApplyAseg flags become 0); anything else, or nothing, no entry. */
#include "cid.h"
#include "h6_guard.h"
extern char g_sw[];
void func_0020BD88(KIND2 *pk2, void *pguard);                  /* resolves a KIND2 */
void ResolveK3__FP5KIND3P3ALO(KIND3 *pk3, void *pguard);
void *PloFindSwNearest__FP2LO3OIDii(void *psw, int grffso, int oid, void *ploNear);
#define FSO_FindNearest 4   /* GRFFSO find mode: the nearest object with the oid (Sly 1 so.h FSO_FindNearest) */
int func_00132EA0(void *plo);                                  /* the object's cid */
void *PeventLaunch__FP5KINDEi(void *paseg, int nEvent);
KIND2 *func_0020C010(int cb);                                  /* new KIND2 */
void func_0020BD78(KIND2 *pk2);                                /* KIND2 init */


// name: SafeHouse port (ResolveKinde)
void ResolveKinde__FP5KINDEP5GUARD(KINDE *pkinde, void *pguard)
{
    void *plo;
    if (pkinde->k != KINDK_Kind2) {
        if (pkinde->k == KINDK_Kind3) {
            ResolveK3__FP5KIND3P3ALO(pkinde->u.pk3, pguard);
            return;
        }
    } else {
        func_0020BD88(pkinde->u.pk2, pguard);
        return;
    }
    plo = PloFindSwNearest__FP2LO3OIDii(g_sw, FSO_FindNearest, pkinde->u.oid, pguard);
    if (!plo) {
        pkinde->k = KINDK_None;
        return;
    }
    switch (func_00132EA0(plo)) {
    case CID_ASEG:
        if (PeventLaunch__FP5KINDEi(plo, 0x22)) {
            pkinde->k = KINDK_Kind2;
            pkinde->u.pk2 = func_0020C010(sizeof(KIND2));
            func_0020BD78(pkinde->u.pk2);
            pkinde->u.pk2->paseg = plo;
            func_0020BD88(pkinde->u.pk2, pguard);
            if (pkinde->grf == -1)
                pkinde->grf = 0;
        } else {
            pkinde->u.plo = plo;
            pkinde->k = KINDK_Aseg;
        }
        break;
    case CID_SM:
        pkinde->k = KINDK_Sm;
        pkinde->u.plo = plo;
        if (pkinde->grf == -1)
            pkinde->grf = 0;
        break;
    default:
        pkinde->k = KINDK_None;
        break;
    }
}
