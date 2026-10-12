#include "m2c_prelude.h"
M2C_UNK func_001AEAA8(void *, M2C_UNK);             /* extern */
M2C_UNK func_001AF660();                            /* extern */

void func_001AE970(void *arg0) {
    func_001AF660();
    func_001AEAA8(arg0, 0);
    M2C_FIELD(arg0, s32 *, 0x20) = 0;
}
