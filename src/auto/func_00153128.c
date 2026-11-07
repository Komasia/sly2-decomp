#include "m2c_prelude.h"
M2C_UNK PauseGame__FP9GAMEPAUSEi(M2C_UNK *, M2C_UNK);          /* extern */
M2C_UNK ResumeGame__FP9GAMEPAUSEi(M2C_UNK *, M2C_UNK);          /* extern */
extern f32 g_clock;
extern M2C_UNK g_sw;

// name: SafeHouse port (SetDanceState)
void SetDanceState__FP5DANCEi(void *arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x50);
    if (temp_v0 != arg1) {
        if (temp_v0 == 1) {
            ResumeGame__FP9GAMEPAUSEi(&g_sw, 3);
        }
        M2C_FIELD(arg0, s32 *, 0x50) = arg1;
        M2C_FIELD(arg0, f32 *, 0x54) = (f32) g_clock;
        M2C_FIELD(arg0, s32 *, 0x1C0) = 0;
        if (arg1 == 1) {
            PauseGame__FP9GAMEPAUSEi(&g_sw, 3);
        }
    }
}
