/* func_001A35F0 (0x1A35F0): set LIGHT::qwUnkF0 and rebuild the light. */
#include "light.h"

void func_001A35F0(LIGHT *plight, qword qw)
{
    plight->qwUnkF0 = qw;
    func_001A3968(plight);
}
