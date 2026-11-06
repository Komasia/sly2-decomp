#include "m2c_prelude.h"
M2C_UNK SetSurroundState__11JOBSURROUNDi(void *, M2C_UNK);             /* extern */
M2C_UNK func_001EEF78();                            /* extern */
M2C_UNK func_00209970(s32, M2C_UNK);                /* extern */

// name: SafeHouse port (JOBSURROUND::Exit)
void Exit__11JOBSURROUND(void *arg0) {
    func_001EEF78();
    SetSurroundState__11JOBSURROUNDi(arg0, -1);
    func_00209970(M2C_FIELD(arg0, s32 *, 0x10), 0x19);
}
