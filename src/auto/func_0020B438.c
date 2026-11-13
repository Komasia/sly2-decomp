#include "m2c_prelude.h"
// name: SafeHouse port (LockGuardActivation)
s32 LockGuardActivation__FP5GUARDi(s32 arg0, s32 arg1) {
    s32 temp_v0;

    if (M2C_FIELD(arg0, s32 *, 0xFFC) == 0) {
        func_001A6CA8(arg0, 1);
    }
    temp_v0 = M2C_FIELD(arg0, s32 *, 0xFFC) + 1;
    M2C_FIELD(arg0, s32 *, 0xFFC) = temp_v0;
    return temp_v0;
}
