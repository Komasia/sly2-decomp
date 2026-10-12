#include "m2c_prelude.h"
M2C_UNK func_002090D0(s32, s32);                    /* extern */

void func_0020AF38(void *arg0, s32 arg1, s32 arg2) {
    func_002090D0(arg0 + 0xB0, M2C_FIELD(arg0, s32 *, 0xAC));
    M2C_FIELD(arg0, s32 *, 0xB4) = arg1;
    M2C_FIELD(arg0, s32 *, 0xBC) = arg2;
}
