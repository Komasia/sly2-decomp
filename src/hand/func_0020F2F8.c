/* func_0020F2F8: sets the world light scale and recomputes the lighting (func_0020F1C8). */
#include "sw.h"

void func_0020F1C8(SW *psw);

void func_0020F2F8(SW *psw, float gLightScale)
{
    psw->gLightScale = gLightScale;
    func_0020F1C8(psw);
}
