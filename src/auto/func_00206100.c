#include "m2c_prelude.h"
void CloneStepguard__FP9STEPGUARDT0(s32 arg0, s32 arg1) {
    void *temp_s1;
    void *temp_v0;

    temp_s1 = M2C_FIELD(arg0, void **, 0xF64);
    func_00203A08(arg0, arg1);
    func_00209770(arg0 + 0xFD0, arg0);
    M2C_FIELD(arg0, void **, 0xF64) = temp_s1;
    temp_v0 = M2C_FIELD(temp_s1, void **, 0xC);
    M2C_FIELD(temp_v0, void (**)(void *, s32), 0x14C)(temp_s1 + M2C_FIELD(temp_v0, s16 *, 0x148), M2C_FIELD(arg1, s32 *, 0xF64));
    func_00208250(arg0);
}
