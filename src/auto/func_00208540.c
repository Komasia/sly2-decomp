#include "m2c_prelude.h"
s32 PtargetrecOf__FP2LO(s32);                             /* extern */
M2C_UNK AddTargetrecGuard__FP9TARGETRECP5GUARD(s32, void *);                 /* extern */
M2C_UNK RemoveTargetrecGuard__FP9TARGETREC(s32, void *);                 /* extern */

// name: SafeHouse port (SetGuardPursued)
void SetGuardPursued__FP5GUARDP2LO(void *arg0, s32 arg1) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x38C);
    if (arg1 != temp_v0) {
        if (temp_v0 != 0) {
            RemoveTargetrecGuard__FP9TARGETREC(M2C_FIELD(arg0, s32 *, 0x3CC), arg0);
            M2C_FIELD(arg0, s32 *, 0x3CC) = 0;
        }
        M2C_FIELD(arg0, s32 *, 0x38C) = arg1;
        if (arg1 != 0) {
            temp_v0_2 = PtargetrecOf__FP2LO(arg1);
            M2C_FIELD(arg0, s32 *, 0x3CC) = temp_v0_2;
            AddTargetrecGuard__FP9TARGETRECP5GUARD(temp_v0_2, arg0);
        }
    }
}
