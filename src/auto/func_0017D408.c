#include "m2c_prelude.h"
M2C_UNK SetState__7JOBGOTOi(void *, M2C_UNK);             /* extern */
M2C_UNK Exit__5AIJOB();                            /* extern */
M2C_UNK RemoveGuardState__FP5GUARDi(s32, s32);                    /* extern */

// name: SafeHouse port (JOBGOTO::Exit)
void Exit__7JOBGOTO(void *arg0) {
    s32 temp_a1;

    Exit__5AIJOB();
    SetState__7JOBGOTOi(arg0, -1);
    temp_a1 = M2C_FIELD(arg0, s32 *, 0x38);
    if (temp_a1 != -1) {
        RemoveGuardState__FP5GUARDi(M2C_FIELD(arg0, s32 *, 0x10), temp_a1);
    }
}
