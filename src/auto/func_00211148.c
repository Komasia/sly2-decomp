#include "m2c_prelude.h"
extern M2C_UNK g_sw;

// name: SafeHouse port (StrPhotoScript)
void StrPhotoScript__FPci(s32 arg0, s32 arg1) {
    s32 temp_a0;
    s32 temp_v0;
    s32 var_a1;
    s32 var_v0;

    temp_v0 = PloPlayerPo__FP2SW((s32) &g_sw);
    if ((temp_v0 != 0) && (FIsBasicDerivedFrom__FP5BASIC3CID(temp_v0, 0x34) != 0)) {
        temp_a0 = M2C_FIELD(temp_v0, s32 *, 0xF38);
        var_a1 = 0;
        if (temp_a0 != 0) {
            if (arg1 != 0) {
                if (arg1 == 1) {
                    var_v0 = func_002026F8(temp_a0);
                    goto block_7;
                }
            } else {
                var_v0 = func_00202730(temp_a0);
block_7:
                var_a1 = var_v0;
            }
        }
        if (var_a1 != 0) {
            strcpy(arg0, var_a1);
        }
    }
}
