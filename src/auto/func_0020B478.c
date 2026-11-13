#include "m2c_prelude.h"
// name: SafeHouse port (UnlockGuardActivation)
void UnlockGuardActivation__FP5GUARDi(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0xFFC) - 1;
    M2C_FIELD(arg0, s32 *, 0xFFC) = temp_v0;
    if (temp_v0 == 0) {
        func_001A6CA8(arg0, 0);
    }
}
