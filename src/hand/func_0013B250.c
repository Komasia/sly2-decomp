/* AttachStickyProjectile: the projectile sticks to palo (+0x1E8): reparented under it (to none when its oid is 1),
 * no velocity, its motion constrained, then its splice event 0x1B. Layout: SafeHouse port (projectile.cpp). */
#include "vtbl.h"
typedef int ti128 __attribute__((mode(TI)));
struct ALO { char pad[0x18]; int oid; };
struct BOMB { int pad[3]; VTENT *vt; char pad2[0x1e8 - 0x10]; struct ALO *paloAttach; };   /* field: SafeHouse port */
extern ti128 D_002A2DD0;
void ReparentBooty__FP3ALOii(struct BOMB *, struct ALO *, int);
void SetAloVelocity__FP3ALOG9VU_VECTOR(struct BOMB *, ti128);
void SetAloAngVelocity__FP3ALOG9VU_VECTOR(struct BOMB *, ti128);
void SetAloCnstrLin__FP3ALOi(struct BOMB *, int);
void SetAloCnstrAng__FP3ALOi(struct BOMB *, int);
// name: SafeHouse port (AttachStickyProjectile)
void AttachStickyProjectile__FPvT0(struct BOMB *pbomb, struct ALO *palo) {
    pbomb->paloAttach = palo;
    ReparentBooty__FP3ALOii(pbomb, palo->oid != 1 ? palo : 0, 3);
    SetAloVelocity__FP3ALOG9VU_VECTOR(pbomb, D_002A2DD0);
    SetAloAngVelocity__FP3ALOG9VU_VECTOR(pbomb, D_002A2DD0);
    SetAloCnstrLin__FP3ALOi(pbomb, 1);
    SetAloCnstrAng__FP3ALOi(pbomb, 1);
    ((void (*)(void *, int, int, int, int, int))pbomb->vt[3].pfn)(VT_THIS(pbomb, &pbomb->vt[3]), 0x1b, 0, 0, 0, 0);
}
