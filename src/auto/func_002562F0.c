#include "m2c_prelude.h"
M2C_UNK func_001F4BF8(s32);                         /* extern */

void func_002562F0(void *arg0, s16 arg1) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x24), s16 *, 0x14) = arg1;
    func_001F4BF8(M2C_FIELD(arg0, s32 *, 0x20));
}
