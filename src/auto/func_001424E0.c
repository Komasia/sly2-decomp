#include "m2c_prelude.h"
// name: SafeHouse port (StartPrizeInteract)
void StartPrizeInteract__FP5ACTORP4ASEGP2LOi(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 var_a1;

    var_a1 = arg1;
    if (var_a1 == 0) {
        var_a1 = M2C_FIELD(arg0, s32 *, 0x9C8);
    }
    M2C_FIELD(arg0, s32 *, 0x9CC) = var_a1;
    StartInteract__FP5ACTORii3JTL(arg0 + 0x4C0, 0xC, arg2, 0);
    M2C_FIELD(arg0, s32 *, 0x1318) = arg3;
}
