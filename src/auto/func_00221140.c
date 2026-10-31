#include "m2c_prelude.h"
s32 func_0013E510(s32, s32);                        /* extern */
M2C_UNK func_002311B0();                            /* extern */

void func_00221140(void *arg0) {
    func_002311B0();
    M2C_FIELD(arg0, s32 *, 0x10C) = func_0013E510(M2C_FIELD(arg0, s32 *, 0x10C), M2C_FIELD(arg0, s32 *, 0x10));
}
