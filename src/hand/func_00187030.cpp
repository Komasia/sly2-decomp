/* StartupJoy (Sly 1 joy.c): pad library start-up and the one joypad. Sly 2 then also starts func_0014C2D8 on the
 * object at D_002DDEC0. */
#include "joy.h"

extern "C" int scePadInit(int mode);
extern "C" void func_0014C2D8(void *pv);
extern int D_002DDEC0;

void StartupJoy()
{
    UpdateGrfjoytFromGrfusr();
    scePadInit(0);
    InitJoy(&g_joy, 0, 0);
    func_0014C2D8(&D_002DDEC0);
}
