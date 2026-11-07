#include "m2c_prelude.h"
M2C_UNK SetInvestigateState__14JOBINVESTIGATEi(void *, M2C_UNK);             /* extern */
M2C_UNK SetNoise__14JOBINVESTIGATEP5NOISE(void *, M2C_UNK);             /* extern */
M2C_UNK Exit__5AIJOB();                            /* extern */
M2C_UNK RemoveGuardState__FP5GUARDi(s32, M2C_UNK);                /* extern */

// name: SafeHouse port (JOBINVESTIGATE::Exit)
void Exit__14JOBINVESTIGATE(void *arg0) {
    Exit__5AIJOB();
    SetInvestigateState__14JOBINVESTIGATEi(arg0, -1);
    RemoveGuardState__FP5GUARDi(M2C_FIELD(arg0, s32 *, 0x10), 0x1F);
    SetNoise__14JOBINVESTIGATEP5NOISE(arg0, 0);
}
