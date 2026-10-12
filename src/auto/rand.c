#include "m2c_prelude.h"
extern void *D_002C49D4;

s32 rand(void) {
    s32 temp_v1;

    temp_v1 = (M2C_FIELD(D_002C49D4, s32 *, 0x58) * 0x41C64E6D) + 0x3039;
    M2C_FIELD(D_002C49D4, s32 *, 0x58) = temp_v1;
    return temp_v1 & 0x7FFFFFFF;
}
