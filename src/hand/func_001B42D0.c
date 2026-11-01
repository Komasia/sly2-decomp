/* func_001B42D0: g++ static initialisation of its translation unit (__static_initialization_and_destruction_0,
 * __initialize_p = 1, __priority = 0xFFFF): sets the global pointer D_002F68A0 to D_002D4240, then the CStructTypeFactory<T>::s_slotheap slot heaps, each
 * guarded by its g++ sentry counter. */
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
extern char D_002D4240[];
extern void *D_002F68A0;

void func_001B42D0(int fInitialize, int nPriority)
{
    if (nPriority == 0xFFFF && fInitialize) {
        D_002F68A0 = D_002D4240;
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
