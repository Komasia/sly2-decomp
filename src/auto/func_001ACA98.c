#include "m2c_prelude.h"
void CopyAb__FPvT0Ui(s32 arg0, s32 arg1, u32 arg2); /* static */
extern M2C_UNK D_002D3750;

s32 func_001ACA98(s32 arg0) {
    func_001DA728(arg0);
    M2C_FIELD(arg0, M2C_UNK **, 0xC) = &D_002D3750;
    M2C_FIELD(arg0, s32 *, 0x20) = 0x52C;
    M2C_FIELD(arg0, s32 *, 0x40) = -1;
    func_001DA7D0(arg0);
    return arg0;
}
