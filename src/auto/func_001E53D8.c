#include "m2c_prelude.h"
M2C_UNK func_001DFEB8(s32);                         /* extern */

void func_001E53D8(void *arg0) {
    s32 temp_a0;

    temp_a0 = M2C_FIELD(arg0, s32 *, 0x50);
    if (temp_a0 != 0) {
        func_001DFEB8(temp_a0);
        M2C_FIELD(arg0, s32 *, 0x50) = 0;
    }
}
