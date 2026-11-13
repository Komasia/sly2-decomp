#include "m2c_prelude.h"
extern f32 g_clock;
extern M2C_UNK g_sw;

// name: SafeHouse port (SetExitState)
void SetExitState__FP2LOi(s32 arg0, s32 arg1) {
    if (arg1 != M2C_FIELD(arg0, s32 *, 0x13C)) {
        if (arg1 == 4) {
            func_001A6CA8(arg0, 1);
            PauseGame__FP9GAMEPAUSEi((s32) &g_sw, 3);
            M2C_FIELD(&g_sw, s32 *, 0x3C84) = arg0;
        }
        M2C_FIELD(arg0, s32 *, 0x13C) = arg1;
        M2C_FIELD(arg0, f32 *, 0x140) = (f32) g_clock;
    }
}
