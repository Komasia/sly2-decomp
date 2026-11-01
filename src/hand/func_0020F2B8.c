/* func_0020F2B8: sets the world light colour (HSV) and recomputes the lighting (func_0020F1C8). */
#include "sw.h"

void func_0020F1C8(SW *psw);

void func_0020F2B8(SW *psw, qword hsvLight)
{
    psw->hsvLight = hsvLight;
    func_0020F1C8(psw);
}
