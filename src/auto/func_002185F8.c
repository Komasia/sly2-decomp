#include "m2c_prelude.h"
void func_002185F8(s32 arg0, s32 arg1, s32 arg2) {
    s16 temp_v0;

    temp_v0 = M2C_FIELD(((arg1 * 0x18) + M2C_FIELD(arg0, s32 *, 8)), s16 *, 8);
    if (temp_v0 >= 0) {
        func_0021A998(M2C_FIELD(arg0, s32 *, 4) + (temp_v0 * 0x18), arg1, arg2);
    }
}
