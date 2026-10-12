#include "m2c_prelude.h"
M2C_UNK CopyAb__FPvT0Ui(s32, s32, s32);             /* extern */

void func_001E9828(void *arg0) {
    void *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 0x48);
    CopyAb__FPvT0Ui(M2C_FIELD(arg0, s32 *, 0x5C), M2C_FIELD(temp_v0, s32 *, 0xF0), M2C_FIELD(temp_v0, s32 *, 0xE8) * 4);
}
