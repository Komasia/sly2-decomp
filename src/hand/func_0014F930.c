/* func_0014F930 (0x14F930): g++ static initialisation / destruction of cm.c's translation unit
 * (__static_initialization_and_destruction_0; func_0014FA88 / func_0014FAA8 run it with 1 / 0 and priority 0xFFFF).
 * Initialising constructs the camera g_cm (func_0014D3D8) and the unit's CStructTypeFactory<T>::s_slotheap
 * template statics, each guarded by its g++ sentry counter; destroying runs the camera's destructor. */
#include "cm.h"
#include "slotheap.h"

extern int D_002DD2E0;
extern int D_002DD2E4;
extern int D_002DD2E8;
extern int D_002DD2EC;
extern int D_002DD2F0;
extern int D_002DD2F4;
extern SLOTHEAP D_004520A8;
extern SLOTHEAP D_004520D0;
extern SLOTHEAP D_004520F8;
extern SLOTHEAP D_00452120;
extern SLOTHEAP D_00452148;
extern SLOTHEAP D_00452170;

CM *func_0014D3D8(CM *pcm);                 /* CM constructor */
void func_00258290(CM *pcm, int grfDelete);  /* CM destructor */

void func_0014F930(int fInitialize, int nPriority)
{
    if (nPriority == 0xFFFF) {
        if (fInitialize) {
            func_0014D3D8(&g_cm);
            if (++D_002DD2E0 == 1)
                func_0011CCA8(&D_004520A8, 0x14, 0x2000, 0x10);
            if (++D_002DD2E4 == 1)
                func_0011CCA8(&D_004520D0, 0x18, 0x800, 0x10);
            if (++D_002DD2E8 == 1)
                func_0011CCA8(&D_004520F8, 0x28, 0x200, 0x10);
            if (++D_002DD2EC == 1)
                func_0011CCA8(&D_00452120, 0x1C, 0x800, 0x10);
            if (++D_002DD2F0 == 1)
                func_0011CCA8(&D_00452148, 0xC, 0xC8, 0x10);
            if (++D_002DD2F4 == 1)
                func_0011CCA8(&D_00452170, 0x14, 0x100, 0x10);
        } else {
            func_00258290(&g_cm, 2);
        }
    }
}
