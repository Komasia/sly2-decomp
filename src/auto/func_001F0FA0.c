#include "m2c_prelude.h"
// name: SafeHouse port (EndSmaTransition)
void EndSmaTransition__FP3SMA(s32 arg0) {
    s32 temp_a1;
    s32 temp_a3;

    M2C_FIELD(arg0, s32 *, 0x30) = 0;
    temp_a3 = M2C_FIELD(arg0, s32 *, 0x38);
    temp_a1 = M2C_FIELD(arg0, s32 *, 0x34);
    M2C_FIELD(arg0, s32 *, 0x38) = -1;
    M2C_FIELD(arg0, s32 *, 0x34) = temp_a3;
    NotifySmaState__FP3SMAii(arg0, temp_a1, temp_a3);
}
