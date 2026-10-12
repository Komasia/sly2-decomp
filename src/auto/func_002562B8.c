#include "m2c_prelude.h"
M2C_UNK func_001F4BF8(s32);                         /* extern */

void func_002562B8(void *arg0, f32 fparg0) {
    M2C_FIELD(M2C_FIELD(arg0, void **, 0x24), f32 *, 8) = fparg0;
    func_001F4BF8(M2C_FIELD(arg0, s32 *, 0x20));
}
