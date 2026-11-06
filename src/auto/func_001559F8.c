#include "m2c_prelude.h"
M2C_UNK SetB5State__5JOBB5i(void *, M2C_UNK);             /* extern */
M2C_UNK func_001EEF78();                            /* extern */
M2C_UNK func_00209970(s32, M2C_UNK);                /* extern */

// name: SafeHouse port (JOBB5::Exit)
void Exit__5JOBB5(void *arg0) {
    func_001EEF78();
    SetB5State__5JOBB5i(arg0, -1);
    func_00209970(M2C_FIELD(arg0, s32 *, 0x10), 0x23);
}
