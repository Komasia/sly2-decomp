/* func_00187E08: forgets the given buttons: they count as neither down nor latched. */
#include "joy.h"

extern "C" void func_00187E08(JOY *pjoy, uint grfbtn)
{
    uint grfbtnKeep = ~grfbtn;
    pjoy->grfbtn &= grfbtnKeep;
    pjoy->grfbtnLatched &= grfbtnKeep;
}
