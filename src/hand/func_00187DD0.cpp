/* func_00187DD0: which of the given buttons went down this frame. */
#include "joy.h"

extern "C" uint func_00187DD0(JOY *pjoy, uint grfbtn)
{
    return pjoy->grfbtnPressed & grfbtn;
}
