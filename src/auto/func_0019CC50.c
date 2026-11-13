#include "m2c_prelude.h"
// name: SafeHouse port (OpenBinoc)
void OpenBinoc__FP5ACTORiP2LOT2(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (M2C_FIELD(arg0, s32 *, 4) != -1) {
        if ((M2C_FIELD(arg0, s32 *, 0x20) != 1) && (arg1 == 1)) {
            SetBinocState__FP5ACTORi(arg0, 2);
            SetBinocState__FP5ACTORi(arg0, -1);
            goto block_4;
        }
    } else {
block_4:
        M2C_FIELD(arg0, s32 *, 0x20) = arg1;
        M2C_FIELD(arg0, s32 *, 0x40) = arg2;
        M2C_FIELD(arg0, s32 *, 0x44) = arg3;
        SetBinocState__FP5ACTORi(arg0, 0);
    }
}
