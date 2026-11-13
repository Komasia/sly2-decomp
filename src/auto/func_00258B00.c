#include "m2c_prelude.h"
s32 func_00258B00(s32 arg0, s32 arg1) {
    if (arg1 == 1) {
        SetPositionKind(arg0, 1);
    }
    return M2C_FIELD(M2C_FIELD(arg0, void **, 0xE4), s32 *, 0x30);
}
