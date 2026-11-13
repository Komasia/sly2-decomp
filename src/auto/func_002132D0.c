#include "m2c_prelude.h"
// name: SafeHouse port (FVisible)
s32 FVisible__FP8SCREENRT(s32 arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x7C) == -1) {
        return 0;
    }
    return func_002137F0(arg0) == 0;
}
