#include "m2c_prelude.h"
M2C_UNK SetState__5JOBB0i(void *, M2C_UNK);             /* extern */
M2C_UNK Exit__5AIJOB();                            /* extern */
M2C_UNK RemoveGuardState__FP5GUARDi(s32, M2C_UNK);                /* extern */

// name: SafeHouse port (JOBB0::Exit)
void Exit__5JOBB0(void *arg0) {
    Exit__5AIJOB();
    SetState__5JOBB0i(arg0, -1);
    RemoveGuardState__FP5GUARDi(M2C_FIELD(arg0, s32 *, 0x10), 0x16);
}
