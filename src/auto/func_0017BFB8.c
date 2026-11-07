#include "m2c_prelude.h"
M2C_UNK SetSurroundState__11JOBSURROUNDi(void *, M2C_UNK);             /* extern */
M2C_UNK Exit__5AIJOB();                            /* extern */
M2C_UNK RemoveGuardState__FP5GUARDi(s32, M2C_UNK);                /* extern */

// name: SafeHouse port (JOBSURROUND::Exit)
void Exit__11JOBSURROUND(void *arg0) {
    Exit__5AIJOB();
    SetSurroundState__11JOBSURROUNDi(arg0, -1);
    RemoveGuardState__FP5GUARDi(M2C_FIELD(arg0, s32 *, 0x10), 0x19);
}
