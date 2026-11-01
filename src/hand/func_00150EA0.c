/* func_00150EA0: CPZOOM: sets an explicit target pose (position, euler angles, FOV); func_00150EF0 runs when the
 * policy was not posed yet. */
#include "cm.h"

void func_00150EF0(CPZOOM *pcpzoom);

void func_00150EA0(CPZOOM *pcpzoom, qword posTarget, qword eulTarget, float radFovTarget)
{
    pcpzoom->posTarget = posTarget;
    pcpzoom->eulTarget = eulTarget;
    pcpzoom->radFovTarget = radFovTarget;
    if (pcpzoom->fPose == 0) {
        func_00150EF0(pcpzoom);
    }
    pcpzoom->fPose = 1;
}
