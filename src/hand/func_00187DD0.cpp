/* GrfbtnPressed__FP6JOYPS2Ui: which of the given buttons went down this frame. */
#include "joy.h"

// name: SafeHouse port (frontend.h GrfbtnPressed, orig 0x187DD0)
extern "C" uint GrfbtnPressed__FP6JOYPS2Ui(JOY *pjoy, uint grfbtn)
{
    return pjoy->grfbtnPressed & grfbtn;
}
