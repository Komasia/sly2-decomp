#include "m2c_prelude.h"
M2C_UNK SetPursueState__9JOBPURSUEi(void *, M2C_UNK);             /* extern */
M2C_UNK Exit__5AIJOB();                            /* extern */
M2C_UNK RemoveGuardState__FP5GUARDi(s32, M2C_UNK);                /* extern */

// name: SafeHouse port (JOBPURSUE::Exit)
void Exit__9JOBPURSUE(void *arg0) {
    Exit__5AIJOB();
    SetPursueState__9JOBPURSUEi(arg0, -1);
    RemoveGuardState__FP5GUARDi(M2C_FIELD(arg0, s32 *, 0x10), 0x1D);
}
