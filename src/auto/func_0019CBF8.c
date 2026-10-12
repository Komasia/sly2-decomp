#include "m2c_prelude.h"
M2C_UNK func_0019D4D0(void *, void *);              /* extern */

void func_0019CBF8(void *arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 4) = -1;
    M2C_FIELD(arg0, s32 *, 0x20) = -1;
    func_0019D4D0(arg0 + 0x24, arg0);
}
