#include "m2c_prelude.h"
void func_001E0F98(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_v0;

    temp_v0 = func_001E01F8(arg0, 0x2F, 1);
    M2C_FIELD(temp_v0, s32 *, 0x10) = arg1;
    M2C_FIELD(temp_v0, s32 *, 0x14) = arg2;
}
