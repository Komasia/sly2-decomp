/* func_00150E60: CPZOOM: sets the focus object; a pose set with func_00150EA0 is dropped (func_00150EF0). */
#include "cm.h"

void func_00150EF0(CPZOOM *pcpzoom);

void func_00150E60(CPZOOM *pcpzoom, LO *plo)
{
    pcpzoom->ploFocus = plo;
    if (pcpzoom->fPose != 0) {
        func_00150EF0(pcpzoom);
    }
    pcpzoom->fPose = 0;
}
