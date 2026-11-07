#include "m2c_prelude.h"
M2C_UNK CopyAb__FPvT0Ui(s32, s32, M2C_UNK);         /* extern */

// name: SafeHouse port (TRKPC::Eval)
void Eval__5TRKPCP7VECTOR4T1ff(s32 arg0, s32 arg1, void *arg2) {
    if (arg1 != 0) {
        CopyAb__FPvT0Ui(arg1, arg0 + 4, 0xC);
    }
    if (arg2 != NULL) {
        M2C_FIELD(arg2, s32 *, 8) = 0;
        M2C_FIELD(arg2, s32 *, 4) = 0;
        M2C_FIELD(arg2, s32 *, 0) = 0;
    }
}
