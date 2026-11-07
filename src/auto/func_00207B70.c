#include "m2c_prelude.h"
s32 MaskOfList__FPv(s32);                             /* extern */
void *PkindeOfMask__FP5GUARDUl(s32, s32);                      /* extern */

// name: SafeHouse port (SetGuardKinde)
void SetGuardKinde__FP5GUARD3OIDii(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_v0;

    temp_v0 = PkindeOfMask__FP5GUARDUl(arg0, MaskOfList__FPv(arg1));
    M2C_FIELD(temp_v0, s32 *, 4) = arg2;
    M2C_FIELD(temp_v0, s32 *, 0xC) = arg3;
}
