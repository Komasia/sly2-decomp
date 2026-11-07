/* func_00187D80: tests the given buttons for a press this frame (func_00187DD0) and marks them handled
 * (SetJoyPs2BtnHandled); returns the presses found. */
#include "joy.h"

extern "C" uint func_00187DD0(JOY *pjoy, uint grfbtn);
extern "C" void SetJoyPs2BtnHandled(JOY *pjoy, uint grfbtn) asm("SetJoyPs2BtnHandled__FP6JOYPS2Ui");

extern "C" uint func_00187D80(JOY *pjoy, uint grfbtn)
{
    uint grfbtnPressed = func_00187DD0(pjoy, grfbtn);
    SetJoyPs2BtnHandled(pjoy, grfbtn);
    return grfbtnPressed;
}
