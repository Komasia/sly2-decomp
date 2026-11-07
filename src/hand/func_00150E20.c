/* SetFocusObject__6CPFREEP2LO: CPZOOM: sets the owner; a pose set with SetTargets__6CPFREEG9VU_VECTORT1f is dropped (Snap__6CPFREE). */
#include "cm.h"

void Snap__6CPFREE(CPZOOM *pcpzoom);

// name: SafeHouse port (CPFREE::SetFocusObject)
void SetFocusObject__6CPFREEP2LO(CPZOOM *pcpzoom, LO *plo)
{
    pcpzoom->ploOwner = plo;
    if (pcpzoom->fPose != 0) {
        Snap__6CPFREE(pcpzoom);
    }
    pcpzoom->fPose = 0;
}
