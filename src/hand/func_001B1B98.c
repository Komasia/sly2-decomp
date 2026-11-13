/* class: ACTOR (SafeHouse actanim.h, orig 0x1B1B98: the segment by id found under the actor (kind-1 find), removed
 * from the world - its vt slot 9). */
#include "vtbl.h"
struct SW;
struct LO {
    /* 0x00 */ char pad0[0xc];
    /* 0x0c */ VTENT *pvt;
};
extern struct SW g_sw;
struct LO *PloFindSwNearest__FP2LO3OIDii(struct SW *psw, int grf, int oid, struct LO *ploContext);

struct LO *func_001B1B98(struct LO *pactor, int oid)
{
    struct LO *plo = PloFindSwNearest__FP2LO3OIDii(&g_sw, 1, oid, pactor);
    if (plo != 0) {
        VTENT *pvte = &plo->pvt[9];
        ((void (*)(void *))pvte->pfn)(VT_THIS(plo, pvte));
    }
    return plo;
}
