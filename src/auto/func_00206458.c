#include "m2c_prelude.h"
s32 func_00206458(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x338) - 1;
    return (s32) ((temp_v0 <= -1) ? 0 : temp_v0) / 10;
}
