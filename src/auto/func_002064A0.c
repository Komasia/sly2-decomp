#include "m2c_prelude.h"
s32 func_002064A0(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x33C) - 1;
    return ((temp_v0 <= -1) ? 0 : temp_v0) + 1;
}
