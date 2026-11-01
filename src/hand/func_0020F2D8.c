/* func_0020F2D8: sets the world light midtone and recomputes the lighting (func_0020F1C8). */
#include "sw.h"

void func_0020F1C8(SW *psw);

void func_0020F2D8(SW *psw, float gMidtone)
{
    psw->gMidtone = gMidtone;
    func_0020F1C8(psw);
}
