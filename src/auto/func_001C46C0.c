#include "m2c_prelude.h"
s32 func_001C4660();                                /* extern */
M2C_UNK func_001C4738(s32, s32);                    /* extern */

s32 func_001C46C0(s32 arg0) {
    s32 temp_v0;

    temp_v0 = func_001C4660();
    func_001C4738(arg0, temp_v0);
    return temp_v0;
}
