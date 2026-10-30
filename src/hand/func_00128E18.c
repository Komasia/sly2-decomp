/* func_00128E18 (0x128E18): g++ static initialisation of its translation unit (__static_initialization_and_destruction_0),
 * run with __initialize_p = 1 and __priority = 0xFFFF. It constructs the slot heaps of the unit's
 * CStructTypeFactory<T>::s_slotheap template statics (args: slot size, slot count, alignment); each one is
 * guarded by its g++ sentry counter so a heap shared with other units is built only once. */
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

void func_00128E18(int fInitialize, int nPriority)
{
    if (nPriority == 0xFFFF && fInitialize) {
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
    }
}
