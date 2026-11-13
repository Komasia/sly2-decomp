#include "m2c_prelude.h"
extern M2C_UNK D_002DD2AC;

// name: SafeHouse port (CGc::AddRootFrame)
s32 AddRootFrame__3CGc(s32 arg0) {
    s32 temp_v0;

    func_00255770(arg0);
    func_00255588(arg0, (s32) &D_002DD2AC);
    temp_v0 = M2C_FIELD(arg0, s32 *, 4) | 0x8000;
    M2C_FIELD(arg0, s32 *, 4) = temp_v0;
    return temp_v0;
}
