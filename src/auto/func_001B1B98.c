#include "m2c_prelude.h"
extern M2C_UNK g_sw;

s32 func_001B1B98(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 temp_v0;
    void *temp_v0_2;

    temp_v0 = PloFindSwNearest__FP2LO3OIDii((s32) &g_sw, 1, arg1, arg0, arg4, arg5, arg6);
    if (temp_v0 != 0) {
        temp_v0_2 = M2C_FIELD(temp_v0, void **, 0xC);
        M2C_FIELD(temp_v0_2, void (**)(s32), 0x4C)(temp_v0 + M2C_FIELD(temp_v0_2, s16 *, 0x48));
    }
    return temp_v0;
}
