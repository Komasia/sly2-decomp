#include "m2c_prelude.h"
M2C_UNK SetBentleySubMode__FP7BENTLEYi(void *, M2C_UNK);             /* extern */
extern f32 g_clock;

// name: SafeHouse port (SetBentleyState2)
void SetBentleyState2__FP7BENTLEYi(void *arg0, s32 arg1) {
    if (arg1 != M2C_FIELD(arg0, s32 *, 0x16BC)) {
        M2C_FIELD(arg0, s32 *, 0x16BC) = arg1;
        M2C_FIELD(arg0, f32 *, 0x16C0) = (f32) g_clock;
        if (arg1 == 0) {
            SetBentleySubMode__FP7BENTLEYi(arg0 + 0x1710, -1);
        }
    }
}
