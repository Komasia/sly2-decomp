/* func_0012AEB0: g++ static initialisation of its translation unit (__static_initialization_and_destruction_0,
 * __initialize_p = 1, __priority = 0xFFFF): only the CStructTypeFactory<T>::s_slotheap slot heaps, each guarded by
 * its g++ sentry counter (this Splice unit also uses the vector / matrix / clq / ... heaps D_00452188..D_004521E8). */
#include "slotheap.h"

extern int D_002DD2E0;
extern int D_002DD2E4;
extern int D_002DD2E8;
extern int D_002DD2EC;
extern int D_002DD2F0;
extern int D_002DD2F4;
extern int D_002DD300;
extern int D_002DD304;
extern int D_002DD308;
extern int D_002DD30C;
extern int D_002DD310;
extern SLOTHEAP D_004520A8;
extern SLOTHEAP D_004520D0;
extern SLOTHEAP D_004520F8;
extern SLOTHEAP D_00452120;
extern SLOTHEAP D_00452148;
extern SLOTHEAP D_00452170;
extern SLOTHEAP D_00452188;
extern SLOTHEAP D_004521A0;
extern SLOTHEAP D_004521B8;
extern SLOTHEAP D_004521D0;
extern SLOTHEAP D_004521E8;

void func_0012AEB0(int fInitialize, int nPriority)
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
        if (++D_002DD300 == 1)
            func_0011CCA8(&D_00452188, 0x20, 0x100, 0x10);
        if (++D_002DD304 == 1)
            func_0011CCA8(&D_004521A0, 0x50, 0x100, 0x10);
        if (++D_002DD308 == 1)
            func_0011CCA8(&D_004521B8, 0x20, 0x40, 0x10);
        if (++D_002DD30C == 1)
            func_0011CCA8(&D_004521D0, 0xC, 0x40, 0x10);
        if (++D_002DD310 == 1)
            func_0011CCA8(&D_004521E8, 0x10, 0x20, 0x10);
    }
}
