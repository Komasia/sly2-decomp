#include "m2c_prelude.h"
M2C_UNK SetB4State__5JOBB4i(void *, M2C_UNK);             /* extern */
M2C_UNK Exit__5AIJOB();                            /* extern */
M2C_UNK SetGuardPursued__FP5GUARDP2LO(s32, M2C_UNK);                /* extern */
M2C_UNK RemoveGuardState__FP5GUARDi(s32, M2C_UNK);                /* extern */

// name: SafeHouse port (JOBB4::Exit)
void Exit__5JOBB4(void *arg0) {
    Exit__5AIJOB();
    SetB4State__5JOBB4i(arg0, -1);
    RemoveGuardState__FP5GUARDi(M2C_FIELD(arg0, s32 *, 0x10), 0x22);
    SetGuardPursued__FP5GUARDP2LO(M2C_FIELD(arg0, s32 *, 0x10), 0);
}
