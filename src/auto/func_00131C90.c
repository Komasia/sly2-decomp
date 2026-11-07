#include "m2c_prelude.h"
M2C_UNK func_0012CED8();                            /* extern */

// name: SafeHouse port (CTRLASEG::End)
void End__8CTRLASEG(void *arg0) {
    if (M2C_FIELD(arg0, s32 *, 0x20) != 0) {
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 8), void **, 0xA8), s32 *, 0xD0) = 0;
        M2C_FIELD(M2C_FIELD(M2C_FIELD(arg0, void **, 8), void **, 0xA8), s32 *, 0xD4) = 0;
        return;
    }
    func_0012CED8();
}
