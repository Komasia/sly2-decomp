/* SetGuardStateMask: set a guard's state mask (GUARD +0x2C0, the animation choice's bits; each job sets the bits of
 * its states), then let the pocket mode follow. */
typedef unsigned long ulong;   /* 64 bits */
struct GUARD {
    /* 0x000 */ char pad0[0x2c0];
    /* 0x2c0 */ ulong grfState;   /* field: SafeHouse port */
};
void UpdatePocketMode(struct GUARD *pguard) asm("UpdatePocketMode__FP2LO");

// name: SafeHouse port (SetGuardStateMask)
void SetGuardStateMask__FP5GUARDUl(struct GUARD *pguard, ulong grfState)
{
    pguard->grfState = grfState;
    UpdatePocketMode(pguard);
}
