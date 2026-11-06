#include "m2c_prelude.h"
M2C_UNK SetShootState__8JOBSHOOTi(s32, M2C_UNK);                /* extern */
M2C_UNK func_001EEF78();                            /* extern */

// name: SafeHouse port (JOBSHOOT::Exit)
void Exit__8JOBSHOOT(s32 arg0) {
    func_001EEF78();
    SetShootState__8JOBSHOOTi(arg0, -1);
}
