/* InitDamage (0x1A0B18): initialises an actor's damage controller (ACTOR +0xDF0): its owner, no reaction state, no
 * flashing, a 2 second flash and a capacity of 0x28. Layout: SafeHouse actor.h DAMAGE. */
struct DAMAGE {
    int pactor;          /* +0x0 the owning actor */
    int nState;          /* +0x4 the reaction state (ACTOR +0xDF4: -1 none, 0..12) */
    int tStart;          /* +0x8 field: SafeHouse port - the reaction's start */
    int cCapacity;       /* +0xC field: SafeHouse port */
    char pad10[0x80];
    int nFlash;          /* +0x90 field: SafeHouse port - the flashing (-1 none, 1 hit, 0 healing) */
    int pad94[2];
    float dtFlash;       /* +0x9C field: SafeHouse port - the flash's length */
};
// name: SafeHouse port (InitDamage)
void InitDamage__FP5ACTORi(struct DAMAGE *pdmg, int pactor)
{
    pdmg->pactor = pactor;
    pdmg->nState = -1;
    pdmg->nFlash = -1;
    pdmg->dtFlash = 2.0f;
    pdmg->cCapacity = 0x28;
}
