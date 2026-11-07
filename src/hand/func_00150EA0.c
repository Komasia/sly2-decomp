/* SetTargets__6CPFREEG9VU_VECTORT1f: CPZOOM: sets an explicit target pose (position, euler angles, FOV); Snap__6CPFREE runs when the
 * policy was not posed yet. */
#include "cm.h"

void Snap__6CPFREE(CPZOOM *pcpzoom);

// name: SafeHouse port (CPFREE::SetTargets)
void SetTargets__6CPFREEG9VU_VECTORT1f(CPZOOM *pcpzoom, qword posTarget, qword eulTarget, float radFovTarget)
{
    pcpzoom->posTarget = posTarget;
    pcpzoom->eulTarget = eulTarget;
    pcpzoom->radFovTarget = radFovTarget;
    if (pcpzoom->fPose == 0) {
        Snap__6CPFREE(pcpzoom);
    }
    pcpzoom->fPose = 1;
}
