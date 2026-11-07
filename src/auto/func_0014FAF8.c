#include "m2c_prelude.h"
M2C_UNK FitStepToFloor__FP3ALOP6VECTORiPG9VU_VECTOR(void *, M2C_UNK *, M2C_UNK, M2C_UNK *); /* extern */
M2C_UNK UpdateStepguard__FP9STEPGUARDf();                            /* extern */
extern M2C_UNK D_002BD910;
extern M2C_UNK D_002BD940;

// name: SafeHouse port (UpdateGuard40)
void UpdateGuard40__FP2LO(void *arg0) {
    UpdateStepguard__FP9STEPGUARDf();
    if ((M2C_FIELD(arg0, s32 *, 0xF80) == -1) && (M2C_FIELD(arg0, s32 *, 0x208) != 0)) {
        FitStepToFloor__FP3ALOP6VECTORiPG9VU_VECTOR(arg0, &D_002BD940, 3, &D_002BD910);
    }
}
