#include "m2c_prelude.h"
// name: SafeHouse port (DequeueLoRoot)
void DequeueLoRoot__FP2SWP2LO(s32 arg0, s32 arg1) {
    s32 temp_s2;

    temp_s2 = arg0 + 0x20;
    if (FFindDlEntry__FP2DLPv(temp_s2, arg1) != 0) {
        if (M2C_FIELD(arg0, s32 *, 0x39A4) == arg1) {
            M2C_FIELD(arg0, s32 *, 0x39A4) = (s32) M2C_FIELD(arg1, s32 *, 4);
        }
        RemoveDlEntry__FP2DLPv(temp_s2, arg1);
    }
}
