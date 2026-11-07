#include "m2c_prelude.h"
M2C_UNK SetLadderState__9JOBLADDERi(void *, M2C_UNK);             /* extern */
M2C_UNK Exit__5AIJOB();                            /* extern */
M2C_UNK RemoveGuardState__FP5GUARDi(s32, M2C_UNK);                /* extern */

// name: SafeHouse port (JOBLADDER::Exit)
void Exit__9JOBLADDER(void *arg0) {
    Exit__5AIJOB();
    SetLadderState__9JOBLADDERi(arg0, -1);
    RemoveGuardState__FP5GUARDi(M2C_FIELD(arg0, s32 *, 0x10), 0x27);
}
