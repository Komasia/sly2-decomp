/* OverlapKindProjectile (class 0x4F, vt slot 61): the base overlap kind, at least 1 (no contact response) with
 * anything under the same root as the launcher that threw it (+0x200). */
#include "so.h"

struct PROJECTILE {
    /* 0x000 */ LO lo;
    /* 0x050 */ char pad50[0x200 - 0x50];
    /* 0x200 */ LO *plaunch;   /* field: SafeHouse port - the launcher */
};
int OverlapKindAlo(LO *pa, LO *pb) asm("OverlapKindAlo__FP3ALOT0");
int func_00134310(int a, int b);   /* the larger of two */

// name: SafeHouse port (OverlapKindProjectile)
int OverlapKindProjectile__FP3ALOT0(struct PROJECTILE *pproj, LO *plo)
{
    int k = OverlapKindAlo(&pproj->lo, plo);
    if (*(void **)plo->ploroot == *(void **)pproj->plaunch->ploroot)
        k = func_00134310(k, 1);
    return k;
}
