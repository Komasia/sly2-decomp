#include "m2c_prelude.h"
extern M2C_UNK D_003DD08C;

void func_001FB6A8(s32 arg0) {
    void *temp_v0;

    if (FFindDlEntry__FP2DLPv((s32) &D_003DD08C, arg0) == 0) {
        temp_v0 = M2C_FIELD(arg0, void **, 0xC);
        M2C_FIELD(temp_v0, void (**)(s32), 0xC)(arg0 + M2C_FIELD(temp_v0, s16 *, 8));
        AppendDlEntry__FP2DLPv((s32) &D_003DD08C, arg0);
    }
}
