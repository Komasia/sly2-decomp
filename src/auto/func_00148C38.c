#include "m2c_prelude.h"
M2C_UNK func_00148740(s32);                         /* extern */
M2C_UNK func_001490A0(s32, M2C_UNK);                /* extern */
M2C_UNK func_001F36A8();                            /* extern */

void PostButtonLoad__FP6BUTTON(s32 arg0) {
    func_001F36A8();
    func_00148740(arg0 + 0x150);
    func_001490A0(arg0, 0);
}
