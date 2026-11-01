/* func_00187DE0: marks the given button presses handled (cf. Sly 1 SetJoyBtnHandled): they leave grfbtnPressed, and
 * those of them still held are latched until released. */
#include "joy.h"

extern "C" void func_00187DE0(JOY *pjoy, uint grfbtn)
{
    pjoy->grfbtnPressed &= ~grfbtn;
    pjoy->grfbtnLatched |= pjoy->grfbtn & grfbtn;
}
