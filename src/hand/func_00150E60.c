/* func_00150E60: CPZOOM: sets the focus object; a pose set with SetTargets__6CPFREEG9VU_VECTORT1f is dropped (Snap__6CPFREE). */
#include "cm.h"

void Snap__6CPFREE(CPZOOM *pcpzoom);

void func_00150E60(CPZOOM *pcpzoom, LO *plo)
{
    pcpzoom->ploFocus = plo;
    if (pcpzoom->fPose != 0) {
        Snap__6CPFREE(pcpzoom);
    }
    pcpzoom->fPose = 0;
}
