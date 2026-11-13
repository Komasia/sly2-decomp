/* PloDanceAseg: an object of the dancer's by oid (PloFindSwNearest kind 4 from the dancer, the last three arguments
 * passed on), taken out of the world (its virtual at vt slot 9). Source: SafeHouse port (dance.cpp). */
#include "vtbl.h"

struct LO {
    /* 0x00 */ char pad0[0xc];
    /* 0x0c */ VTENT *pvt;
};
extern char g_sw[];
struct LO *PloFindSwNearest__FP2LO3OIDii(void *psw, int kind, int oid, struct LO *plo, int n4, int n5, int n6);

// name: SafeHouse port (PloDanceAseg)
struct LO *PloDanceAseg__FP2LO3OIDiiiii(struct LO *plo, int oid, int n2, int n3, int n4, int n5, int n6)
{
    struct LO *ploFound = PloFindSwNearest__FP2LO3OIDii(g_sw, 4, oid, plo, n4, n5, n6);
    if (ploFound != 0) {
        VTENT *pvte = &ploFound->pvt[0x48 / 8];
        ((void (*)(void *))pvte->pfn)(VT_THIS(ploFound, pvte));
    }
    return ploFound;
}
