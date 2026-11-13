#include "m2c_prelude.h"
extern M2C_UNK g_sw;

// name: SafeHouse port (SetAsegaEventSound)
void SetAsegaEventSound__FP5ASEGAi(s32 arg0, s32 arg1) {
    if ((func_00131968(arg0) == 0) && (arg1 != M2C_FIELD(arg0, s32 *, 0x58))) {
        if (arg1 != 0) {
            PauseGame__FP9GAMEPAUSEi((s32) &g_sw, 3);
        } else {
            ResumeGame__FP9GAMEPAUSEi((s32) &g_sw, 3);
        }
        M2C_FIELD(arg0, s32 *, 0x58) = arg1;
    }
}
