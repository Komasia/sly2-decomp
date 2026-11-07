#include "m2c_prelude.h"
M2C_UNK RetractAsegaPp__FPP5ASEGA(s32);                         /* extern */
M2C_UNK ClearJobs__FP5ACTOR(s32);                         /* extern */
M2C_UNK OnSoRemove__FP2SO();                            /* extern */
M2C_UNK SetGuardPursued__FP5GUARDP2LO(s32, M2C_UNK);                /* extern */

void OnStepguardRemove__FP9STEPGUARD(s32 arg0) {
    OnSoRemove__FP2SO();
    SetGuardPursued__FP5GUARDP2LO(arg0, 0);
    ClearJobs__FP5ACTOR(arg0 + 0x26C);
    RetractAsegaPp__FPP5ASEGA(arg0 + 0x34C);
}
