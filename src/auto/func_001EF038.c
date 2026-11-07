#include "m2c_prelude.h"
s32 FIsBasicDerivedFrom__FP5BASIC3CID(s32, M2C_UNK);                    /* extern */
M2C_UNK UnlockGuardActivation__FP5GUARDi(s32);                         /* extern */

// name: SafeHouse port (UnlockJob)
void UnlockJob__FP5AIJOB(void *arg0) {
    void *var_a0;

    if (M2C_FIELD(arg0, s32 *, 0x1C) != 0) {
        M2C_FIELD(arg0, s32 *, 0x1C) = 0;
        if (FIsBasicDerivedFrom__FP5BASIC3CID(M2C_FIELD(arg0, s32 *, 0x10), 0x38) != 0) {
            UnlockGuardActivation__FP5GUARDi(M2C_FIELD(arg0, s32 *, 0x10));
        }
        var_a0 = M2C_FIELD(arg0, void **, 0x14);
        if (var_a0 != NULL) {
            do {
                M2C_FIELD(var_a0, s32 *, 0x20) = (s32) (M2C_FIELD(var_a0, s32 *, 0x20) - 1);
                var_a0 = M2C_FIELD(var_a0, void **, 0x14);
            } while (var_a0 != NULL);
        }
    }
}
