#include "m2c_prelude.h"
s32 func_00258B38(s32 arg0, s32 arg1) {
    if (arg1 == 1) {
        SetPositionKind(arg0, 2);
    }
    return M2C_FIELD(arg0, s32 *, 0xE4) + 0x10;
}
