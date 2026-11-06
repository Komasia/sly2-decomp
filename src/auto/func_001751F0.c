#include "m2c_prelude.h"
M2C_UNK Enter__7JOBMOVE();                            /* extern */

// name: SafeHouse port (JOBSTRIKE::Enter)
void Enter__9JOBSTRIKE(void *arg0) {
    void *temp_a0;

    M2C_FIELD(M2C_FIELD(arg0, void **, 0x10), s32 *, 0xF3C) = 1;
    Enter__7JOBMOVE();
    temp_a0 = M2C_FIELD(arg0, void **, 0x40);
    if (M2C_FIELD(temp_a0, s32 *, 0) == 2) {
        M2C_FIELD(M2C_FIELD(temp_a0, void **, 8), s32 *, 0x60) = 1;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 0x40), void **, 8), s32 *, 0x64) = 1;
        M2C_FIELD(arg0, s32 *, 0x50) = 1;
    }
}
