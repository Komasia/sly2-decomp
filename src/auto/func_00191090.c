#include "m2c_prelude.h"
// name: SafeHouse port (InitInteract)
void InitInteract__FP5ACTORi(s32 arg0, s32 arg1) {
    M2C_FIELD(arg0, s32 *, 0) = arg1;
    M2C_FIELD(arg0, s32 *, 8) = -1;
    M2C_FIELD(arg0, s32 *, 0xC) = -1;
    M2C_FIELD(arg0, s32 *, 0x4FC) = -1;
    InitGait__FP4GAITii(arg0 + 0x180, arg1, 0x6F);
    InitGait__FP4GAITii(arg0 + 0x240, arg1, 0x6F);
    func_001CC158(arg0 + 0x440);
}
