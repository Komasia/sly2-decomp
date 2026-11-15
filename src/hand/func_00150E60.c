/* SetTargetObject__6CPFREEP2LO: CPZOOM: sets the focus object; a pose set with SetTargets__6CPFREEG9VU_VECTORT1f is dropped (Snap__6CPFREE). */
#include "cm.h"

void Snap__6CPFREE(CPZOOM *pcpzoom);

// name: SafeHouse port (cplcy.h CPZOOM::SetTargetObject 0x150E60; class as SetFocusObject__6CPFREEP2LO 0x150E20)
void SetTargetObject__6CPFREEP2LO(CPZOOM *pcpzoom, LO *plo)
{
    pcpzoom->ploFocus = plo;
    if (pcpzoom->fPose != 0) {
        Snap__6CPFREE(pcpzoom);
    }
    pcpzoom->fPose = 0;
}
