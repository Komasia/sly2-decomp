#include "m2c_prelude.h"
M2C_UNK func_001F4BF8(s32);                         /* extern */

void func_00256328(void *arg0, s32 arg1) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x24), s32 *, 0x18) = arg1;
    func_001F4BF8(M2C_FIELD(arg0, s32 *, 0x20));
}
