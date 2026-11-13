#include "m2c_prelude.h"
s32 func_0017F170(s32 arg0, s32 arg1) {
    s32 temp_v0;

    func_001CB518(arg0, arg1);
    temp_v0 = M2C_FIELD(arg0, s32 *, 0x180);
    M2C_FIELD(arg0, s32 *, 0x184) = temp_v0;
    return temp_v0;
}
