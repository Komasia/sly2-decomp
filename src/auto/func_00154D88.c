#include "m2c_prelude.h"
f32 func_00154C90();                                /* extern */
M2C_UNK func_00154DC8(s32, f32);                    /* extern */

void func_00154D88(s32 arg0, f32 fparg0) {
    func_00154DC8(arg0, func_00154C90() + fparg0);
}
