#include "m2c_prelude.h"
M2C_UNK SetActState__6JOBACTi(s32, M2C_UNK);                /* extern */
M2C_UNK func_001EEF70();                            /* extern */
M2C_UNK func_001EEFC0(s32);                         /* extern */

// name: SafeHouse port (JOBACT::Enter)
void Enter__6JOBACT(s32 arg0) {
    func_001EEF70();
    SetActState__6JOBACTi(arg0, 0);
    func_001EEFC0(arg0);
}
