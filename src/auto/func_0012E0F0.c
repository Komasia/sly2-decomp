#include "m2c_prelude.h"
void func_0012E0F0(void *arg0, s128 arg1, s128 arg2) {
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 8);
    M2C_FIELD(arg0, s128 *, 0x20) = arg1;
    M2C_FIELD(arg0, s128 *, 0x30) = arg2;
    if (arg0 == M2C_FIELD(temp_v1, s32 *, 0x90)) {
        M2C_FIELD(temp_v1, s128 *, 0xC0) = arg1;
        M2C_FIELD(M2C_FIELD(arg0, void **, 8), s128 *, 0xD0) = arg2;
    }
}
