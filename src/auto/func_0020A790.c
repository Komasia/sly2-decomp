#include "m2c_prelude.h"
M2C_UNK CopyAb__FPvT0Ui(void *, void *, s32);       /* extern */
s32 func_0020A658();                                /* extern */

void func_0020A790(void *arg0) {
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v1;
    void *temp_a0;

    temp_v0 = func_0020A658();
    temp_v1 = M2C_FIELD(arg0, s32 *, 0x28) - 1;
    temp_a0 = arg0 + ((temp_v0 * 4) + 0x2C);
    temp_v0_2 = temp_v1 - temp_v0;
    M2C_FIELD(arg0, s32 *, 0x28) = temp_v1;
    CopyAb__FPvT0Ui(temp_a0, temp_a0 + 4, temp_v0_2 * 4);
}
