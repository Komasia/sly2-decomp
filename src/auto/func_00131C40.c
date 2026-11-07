#include "m2c_prelude.h"
M2C_UNK Start__4CTRL(void *, void *);              /* extern */

// name: SafeHouse port (CTRLASEG::Start)
void Start__8CTRLASEG(void *arg0) {
    s32 temp_a0;

    temp_a0 = M2C_FIELD(arg0, s32 *, 0x20);
    if (temp_a0 != 0) {
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 8), void **, 0xA8), s32 *, 0xD0) = temp_a0;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 8), void **, 0xA8), s32 *, 0xD4) = (s32) (M2C_FIELD(arg0, s32 *, 0x24) + 0x1C);
        return;
    }
    Start__4CTRL(arg0, arg0);
}
