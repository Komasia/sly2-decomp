/* FStickyProjectileParent: whether a sticky projectile may stick to palo: none of palo and its parents derives from one
 * of the four classes D_002BC9D0. */
struct ALO { char pad[0x10]; struct ALO *paloParent; };   /* field: SafeHouse port (LO +0x10) */
extern int D_002BC9D0[4];   /* the classes a projectile does not stick to */
int FIsBasicDerivedFrom__FP5BASIC3CID(struct ALO *, int);
// name: SafeHouse port (FStickyProjectileParent)
int FStickyProjectileParent__FP3ALOPv(void *unused, struct ALO *palo) {
    unsigned int i;
    for (; palo; palo = palo->paloParent) {
        for (i = 0; i < 4; i++) {
            if (FIsBasicDerivedFrom__FP5BASIC3CID(palo, D_002BC9D0[i])) return 0;
        }
    }
    return 1;
}
