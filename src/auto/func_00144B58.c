#include "m2c_prelude.h"
M2C_UNK func_001448F0(s32, s128);                   /* extern */
M2C_UNK func_00177EF0();                            /* extern */

void func_00144B58(void *arg0) {
    func_00177EF0();
    func_001448F0(M2C_FIELD(arg0, s32 *, 0x10) + 0xFD0, M2C_FIELD(arg0, s128 *, 0x80));
}
