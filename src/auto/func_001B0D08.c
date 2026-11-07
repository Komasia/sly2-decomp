#include "m2c_prelude.h"
M2C_UNK PlaceBird__FP2LO(void *);                      /* extern */
M2C_UNK FStepLength__FP4ASEGP3ALOPf(void *, s32, void *);         /* extern */
M2C_UNK BindStepSegs__FP8STEPSEGS(void *);                      /* extern */
M2C_UNK func_001F36A8();                            /* extern */

// name: SafeHouse port (StartBird)
void StartBird__FP2LO(void *arg0) {
    func_001F36A8();
    BindStepSegs__FP8STEPSEGS(arg0);
    FStepLength__FP4ASEGP3ALOPf(arg0, M2C_FIELD(arg0, s32 *, 0x18C), arg0 + 0x1CC);
    FStepLength__FP4ASEGP3ALOPf(arg0, M2C_FIELD(arg0, s32 *, 0x1B0), arg0 + 0x1D0);
    PlaceBird__FP2LO(arg0);
}
