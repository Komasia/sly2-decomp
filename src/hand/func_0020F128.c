/* func_0020F128: increments the world counter cUnk3d80; the first reference starts func_001A3078 on D_002E1E60. */
#include "sw.h"

extern char D_002E1E60[];
void func_001A3078(void *pv);

void func_0020F128(SW *psw)
{
    if (++psw->cUnk3d80 == 1) {
        func_001A3078(D_002E1E60);
    }
}
