#include "m2c_prelude.h"
M2C_UNK SetMoveState__7JOBMOVEi(void *, M2C_UNK);             /* extern */
M2C_UNK func_001EEF78();                            /* extern */
M2C_UNK RemoveGuardState__FP5GUARDi(s32, s32);                    /* extern */

// name: SafeHouse port (JOBMOVE::Exit)
void Exit__7JOBMOVE(void *arg0) {
    func_001EEF78();
    SetMoveState__7JOBMOVEi(arg0, 1);
    RemoveGuardState__FP5GUARDi(M2C_FIELD(arg0, s32 *, 0x10), M2C_FIELD(arg0, s32 *, 0x3C));
}
