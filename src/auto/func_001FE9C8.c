#include "m2c_prelude.h"
M2C_UNK func_00232250(s32);                         /* extern */

void func_001FE9C8(void *arg0, s32 arg1) {
    if (M2C_FIELD(arg0, s32 *, 0x104) != arg1) {
        M2C_FIELD(arg0, s32 *, 0x104) = arg1;
        func_00232250(arg1);
    }
}
