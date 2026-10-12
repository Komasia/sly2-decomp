#include "m2c_prelude.h"
M2C_UNK func_001F2108();                            /* extern */

void func_0021BB88(void *arg0) {
    void *temp_v0;

    func_001F2108();
    temp_v0 = arg0 + 0x170;
    M2C_FIELD(arg0, f32 *, 0x170) = 1.0f;
    M2C_FIELD(temp_v0, s32 *, 4) = 0;
    M2C_FIELD(temp_v0, s32 *, 8) = 0;
    M2C_FIELD(arg0, f32 *, 0x184) = 100.0f;
}
