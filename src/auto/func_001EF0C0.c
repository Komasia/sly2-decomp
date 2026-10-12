#include "m2c_prelude.h"
void func_001EF0C0(void *arg0, void *arg1) {
    M2C_FIELD(arg1, s32 *, 0x1C) = 0;
    M2C_FIELD(arg1, f32 *, 0x18) = (f32) M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), f32 *, 0x1A8);
}
