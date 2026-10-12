#include "m2c_prelude.h"
s32 func_00210120(void *arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x39DC);
    M2C_FIELD(arg0, s32 *, 0x39DC) = (s32) (temp_v1 + 1);
    return M2C_FIELD(arg0, s32 *, 0x39D8) + (temp_v1 * 0xC);
}
