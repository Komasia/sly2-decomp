#include "m2c_prelude.h"
s32 func_001FAF70();                                /* extern */

s32 PsfxEnsureExpls__FP5EXPLS4ENSK(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0xF0) == 0) {
        M2C_FIELD(arg0, s32 *, 0xF0) = func_001FAF70();
    }
    return M2C_FIELD(arg0, s32 *, 0xF0);
}
