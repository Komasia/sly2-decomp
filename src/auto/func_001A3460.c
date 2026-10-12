#include "m2c_prelude.h"
M2C_UNK func_001A3968(void *);                      /* extern */
M2C_UNK func_001A5E80();                            /* extern */

void func_001A3460(void *arg0) {
    s32 var_v1;
    void *temp_v0;

    func_001A5E80();
    temp_v0 = M2C_FIELD(arg0, void **, 0x50);
    var_v1 = 0;
    if (temp_v0 != NULL) {
        var_v1 = M2C_FIELD(temp_v0, s32 *, 0xA4);
    }
    if (M2C_FIELD(arg0, s32 *, 0xE4) < var_v1) {
        M2C_FIELD(arg0, s32 *, 0xE4) = var_v1;
        func_001A3968(arg0);
    }
}
