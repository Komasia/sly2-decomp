#include "m2c_prelude.h"
// name: SafeHouse port (ShowCoinCounter)
void ShowCoinCounter__FP2SW(s32 arg0) {
    void *temp_s0;
    void *temp_v0;

    temp_s0 = M2C_FIELD(arg0, void **, 0x3BAC);
    if (temp_s0 != NULL) {
        temp_v0 = M2C_FIELD(temp_s0, void **, 0xC);
        M2C_FIELD(temp_v0, void (**)(void *, M2C_UNK), 0x18C)(temp_s0 + M2C_FIELD(temp_v0, s16 *, 0x188), -1);
        RefreshScreenObj__FP2LO((s32) temp_s0);
    }
}
