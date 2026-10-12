#include "m2c_prelude.h"
M2C_UNK func_00154080(void *, s32 *, M2C_UNK);      /* extern */
s32 func_00154180();                                /* extern */

void func_00153F18(void *arg0, s32 arg1) {
    s32 *temp_a1;
    u32 temp_v1;

    if (func_00154180() == 0) {
        temp_v1 = M2C_FIELD(arg0, u32 *, 0xFC);
        if (temp_v1 < 8U) {
            M2C_FIELD(arg0, u32 *, 0xFC) = (u32) (temp_v1 + 1);
            temp_a1 = arg0 + ((temp_v1 * 0x10) + 0x100);
            *temp_a1 = arg1;
            func_00154080(arg0, temp_a1, 0);
        }
    }
}
