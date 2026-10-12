#include "m2c_prelude.h"
void func_00209840(void *arg0, void *arg1) {
    void *temp_a0;

    if (M2C_FIELD(arg0, s32 *, 4) == 0) {
        temp_a0 = M2C_FIELD(arg0, void **, 0xC);
        M2C_FIELD(temp_a0, s128 *, 0x1B0) = (s128) M2C_FIELD(arg1, s128 *, 0);
        M2C_FIELD(temp_a0, s128 *, 0x1C0) = (s128) M2C_FIELD(arg1, s128 *, 0x10);
        M2C_FIELD(temp_a0, s128 *, 0x1D0) = (s128) M2C_FIELD(arg1, s128 *, 0x20);
    }
}
