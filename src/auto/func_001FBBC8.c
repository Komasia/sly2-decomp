#include "m2c_prelude.h"
extern M2C_UNK D_002D9C70;

s32 func_001FBBC8(s32 arg0, s32 arg1) {
    func_001FAFD0(arg0);
    M2C_FIELD(arg0, s32 *, 0x60) = arg1;
    M2C_FIELD(arg0, M2C_UNK **, 0xC) = &D_002D9C70;
    SetDirty__4CSndUiUi(arg0, 1, 1);
    return arg0;
}
