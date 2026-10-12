#include "m2c_prelude.h"
s32 func_00207B10(s32);                             /* extern */
void *func_00209C18(s32, s32);                      /* extern */

void func_00207B70(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_v0;

    temp_v0 = func_00209C18(arg0, func_00207B10(arg1));
    M2C_FIELD(temp_v0, s32 *, 4) = arg2;
    M2C_FIELD(temp_v0, s32 *, 0xC) = arg3;
}
