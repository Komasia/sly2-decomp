/* SetJoyPs2BtnHandled__FP6JOYPS2Ui: marks the given button presses handled (cf. Sly 1 SetJoyBtnHandled): they leave grfbtnPressed, and
 * those of them still held are latched until released. */
#include "joy.h"

// name: SafeHouse port (SetJoyPs2BtnHandled)
extern "C" void SetJoyPs2BtnHandled__FP6JOYPS2Ui(JOY *pjoy, uint grfbtn)
{
    pjoy->grfbtnPressed &= ~grfbtn;
    pjoy->grfbtnLatched |= pjoy->grfbtn & grfbtn;
}
