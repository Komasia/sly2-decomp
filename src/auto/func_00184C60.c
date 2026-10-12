#include "m2c_prelude.h"
s32 sceRead(s32, s32, s32);                         /* extern */

void func_00184C60(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x38);
    M2C_FIELD(arg0, s32 *, 0x10) = temp_v0;
    M2C_FIELD(arg0, s32 *, 0x14) = sceRead(M2C_FIELD(arg0, s32 *, 0x3C), temp_v0, M2C_FIELD(arg0, s32 *, 0x34));
}
