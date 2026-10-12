#include "m2c_prelude.h"
void func_002087C8(void *arg0) {
    void *temp_a1;

    temp_a1 = M2C_FIELD(arg0, void **, 0xF64);
    M2C_FIELD(temp_a1, s32 *, 0xFC) = (s32) (M2C_FIELD(temp_a1, s32 *, 0xFC) - M2C_FIELD(arg0, s32 *, 0x3A4));
    M2C_FIELD(arg0, s32 *, 0x394) = 0;
    M2C_FIELD(arg0, s32 *, 0x3A4) = 0;
}
