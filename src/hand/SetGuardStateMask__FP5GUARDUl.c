/* SetGuardStateMask: set a guard's state mask (GUARD +0x2C0, the animation choice's bits; each job sets the bits of
 * its states), then let the pocket mode follow. */
#include "stepguard.h"
void UpdatePocketMode(struct GUARD *pguard) asm("UpdatePocketMode__FP2LO");

// name: SafeHouse port (SetGuardStateMask)
void SetGuardStateMask__FP5GUARDUl(struct GUARD *pguard, ulong grfState)
{
    pguard->grfState = grfState;
    UpdatePocketMode(pguard);
}
