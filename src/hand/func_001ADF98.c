/* func_001ADF98 (0x1ADF98): g++ static initialisation / destruction of its translation unit
 * (__static_initialization_and_destruction_0; func_001AE130 runs the destruction). Initialising constructs the unit's
 * two global objects D_002E6550 (func_001ACA98) and D_002E65A0 (func_001ADDF0), then the slot heaps of the
 * CStructTypeFactory<T>::s_slotheap template statics, each guarded by its g++ sentry counter; destroying runs the
 * two objects' destructor (func_00258348) in reverse order. */
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
extern char D_002E6550[];
extern char D_002E65A0[];
void func_001ACA98(void *p);
void func_001ADDF0(void *p);
void func_00258348(void *p, int grfDelete);

void func_001ADF98(int fInitialize, int nPriority)
{
    if (nPriority == 0xFFFF) {
        if (fInitialize) {
            func_001ACA98(D_002E6550);
            func_001ADDF0(D_002E65A0);
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
            func_00258348(D_002E65A0, 2);
            func_00258348(D_002E6550, 2);
        }
    }
}
