#include "m2c_prelude.h"
M2C_UNK func_001333C0(s32, s32);                    /* extern */
M2C_UNK func_00133448(s32, s32);                    /* extern */

void func_0018D698(s32 arg0, void *arg1, s32 arg2) {
    s32 temp_a0;

    temp_a0 = M2C_FIELD(arg1, s32 *, 8);
    if (temp_a0 != 0) {
        func_00133448(temp_a0, arg0);
        M2C_FIELD(arg1, s32 *, 8) = 0;
    }
    if (arg2 != 0) {
        M2C_FIELD(arg1, s32 *, 8) = arg2;
        func_001333C0(arg2, arg0);
    }
}
