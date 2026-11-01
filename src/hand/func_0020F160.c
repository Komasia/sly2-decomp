/* func_0020F160: decrements the world counter cUnk3d80; the last reference runs func_001A30D0 on D_002E1E60. */
#include "sw.h"

extern char D_002E1E60[];
void func_001A30D0(void *pv);

void func_0020F160(SW *psw)
{
    if (--psw->cUnk3d80 == 0) {
        func_001A30D0(D_002E1E60);
    }
}
