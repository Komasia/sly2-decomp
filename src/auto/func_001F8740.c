#include "m2c_prelude.h"
extern M2C_UNK D_003E15CC;

void func_001F8740(s32 arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x10) - 1;
    M2C_FIELD(arg0, s32 *, 0x10) = temp_v0;
    if (temp_v0 <= 0) {
        func_00256EE0(arg0, 0);
        func_002580A8(arg0 + 4, 0);
        func_001334A8(arg0);
        func_0011CD98((s32) &D_003E15CC, arg0);
    }
}
