#include "m2c_prelude.h"
M2C_UNK SetState__7JOBGOTOi(void *, M2C_UNK);             /* extern */
M2C_UNK Search__7JOBGOTO(void *);                      /* extern */
M2C_UNK Enter__5AIJOB(void *);                      /* extern */
M2C_UNK AddGuardState__FP5GUARDi(s32, s32);                    /* extern */

// name: SafeHouse port (JOBGOTO::Enter)
void Enter__7JOBGOTO(void *arg0) {
    s32 temp_a1;

    temp_a1 = M2C_FIELD(arg0, s32 *, 0x38);
    if (temp_a1 != -1) {
        AddGuardState__FP5GUARDi(M2C_FIELD(arg0, s32 *, 0x10), temp_a1);
    }
    Enter__5AIJOB(arg0);
    SetState__7JOBGOTOi(arg0, 4);
    Search__7JOBGOTO(arg0);
}
