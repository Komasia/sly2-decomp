/* OverlapKindBooty (vt slot 61): a thrown booty (5) passes through actors (3; by the other's root object); else the ALO's overlap kind. */
#include "cid.h"
struct NODE { int ploRoot; };   /* LO +0x14: the root's node, its first word the root */
struct ALO { char pad[0x14]; struct NODE *pnode; };
struct BOOTY { char pad[0x184]; int state; };
int FIsBasicDerivedFrom__FP5BASIC3CID(int, int);
int OverlapKindAlo__FP3ALOT0(struct BOOTY *, struct ALO *);
// name: SafeHouse port (OverlapKindBooty)
int OverlapKindBooty__FP3ALOT0(struct BOOTY *pbooty, struct ALO *palo) {
    if (pbooty->state == 5 && FIsBasicDerivedFrom__FP5BASIC3CID(palo->pnode->ploRoot, CID_ACTOR)) return 3;
    return OverlapKindAlo__FP3ALOT0(pbooty, palo);
}
