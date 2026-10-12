#include "m2c_prelude.h"
s32 func_001711F0(s32, s32);                        /* extern */
M2C_UNK func_001EF0D8(void *);                      /* extern */

void func_00171C98(void *arg0, s32 arg1) {
    if (M2C_FIELD(arg0, s32 *, 0x30) != 0) {
        if (M2C_FIELD(arg0, s32 *, 0x40) != 0) {
            func_001EF0D8(arg0 + 0x18);
            M2C_FIELD(arg0, s32 *, 0x40) = 0;
        }
        M2C_FIELD(arg0, s32 *, 0x38) = func_001711F0(M2C_FIELD(arg0, s32 *, 0x30), arg1);
    }
}
