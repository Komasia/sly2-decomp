#include "m2c_prelude.h"
M2C_UNK SetState__5JOBBDi(void *, M2C_UNK);             /* extern */
M2C_UNK func_001EEF70();                            /* extern */
M2C_UNK SetGuardPursued__FP5GUARDP2LO(s32, s32);                    /* extern */

// name: SafeHouse port (JOBBD::Enter)
void Enter__5JOBBD(void *arg0) {
    func_001EEF70();
    SetState__5JOBBDi(arg0, 0);
    SetGuardPursued__FP5GUARDP2LO(M2C_FIELD(arg0, s32 *, 0x10), M2C_FIELD(arg0, s32 *, 0x38));
}
