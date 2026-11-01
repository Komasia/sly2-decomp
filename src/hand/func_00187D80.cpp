/* func_00187D80: tests the given buttons for a press this frame (func_00187DD0) and marks them handled
 * (func_00187DE0); returns the presses found. */
#include "joy.h"

extern "C" uint func_00187DD0(JOY *pjoy, uint grfbtn);
extern "C" void func_00187DE0(JOY *pjoy, uint grfbtn);

extern "C" uint func_00187D80(JOY *pjoy, uint grfbtn)
{
    uint grfbtnPressed = func_00187DD0(pjoy, grfbtn);
    func_00187DE0(pjoy, grfbtn);
    return grfbtnPressed;
}
