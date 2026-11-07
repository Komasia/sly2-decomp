#include "m2c_prelude.h"
s32 MaskOfList__FPv(s32);                             /* extern */
M2C_UNK SetGuardKinde__FP5GUARD3OIDii(s32, s32, s32, s32);          /* extern */
M2C_UNK ResolveKinde__FP5KINDEP5GUARD(s32, s32);                    /* extern */
s32 PkindeOfMask__FP5GUARDUl(s32, s32);                        /* extern */

void func_00207BC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_s1;

    temp_s1 = PkindeOfMask__FP5GUARDUl(arg0, MaskOfList__FPv(arg1));
    SetGuardKinde__FP5GUARD3OIDii(arg0, arg1, arg2, arg3);
    ResolveKinde__FP5KINDEP5GUARD(temp_s1, arg0);
}
