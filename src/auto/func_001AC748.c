#include "m2c_prelude.h"
s32 FUN_0018bc90(void *, s32, M2C_UNK, M2C_UNK);    /* extern */
s32 func_00244018(s32, s32, s32);                   /* extern */

s32 func_001AC748(void *arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = FUN_0018bc90(arg0 + 0xFD5C, func_00244018(M2C_FIELD(arg0, s32 *, 0), M2C_FIELD(arg0, s32 *, 4), arg1), 0xB, 0);
    return ((temp_v0 ^ 0x18) == 0) ? 0 : temp_v0;
}
