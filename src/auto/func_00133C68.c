#include "m2c_prelude.h"
// name: SafeHouse port (PoxAddSw)
s32 PoxAddSw__FP2SWP3OXAT1(s32 arg0, s32 arg1, s32 arg2) {
    void *temp_v0;

    temp_v0 = func_0011CCC0(arg0 + 0x3CF8);
    M2C_FIELD(temp_v0, s32 *, 0xC) = (s32) M2C_FIELD(arg2, s32 *, 0x60);
    M2C_FIELD(temp_v0, void **, 4) = (void *) M2C_FIELD(arg1, void **, 0x64);
    M2C_FIELD(arg1, void **, 0x64) = temp_v0;
    return (s32) temp_v0;
}
