#include "m2c_prelude.h"
M2C_UNK SetState__7JOBLINKi(void *, M2C_UNK);             /* extern */
M2C_UNK func_001EF038(void *);                      /* extern */

// name: SafeHouse port (JOBLINK::NextRecord)
void NextRecord__7JOBLINK(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x34) + 1;
    M2C_FIELD(arg0, s32 *, 0x34) = temp_v0;
    if (temp_v0 < M2C_FIELD(M2C_FIELD(arg0, void **, 0x30), s32 *, 0x50)) {
        SetState__7JOBLINKi(arg0, -1);
        SetState__7JOBLINKi(arg0, 0);
        return;
    }
    SetState__7JOBLINKi(arg0, -1);
    func_001EF038(arg0);
}
