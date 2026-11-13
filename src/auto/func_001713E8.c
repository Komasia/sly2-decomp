#include "m2c_prelude.h"
// name: SafeHouse port (JOBSCRIPT::Update)
s32 Update__9JOBSCRIPT(s32 arg0) {
    s32 temp_a1;
    s32 var_v0;
    void *temp_v0;

    Update__5AIJOB();
    var_v0 = M2C_FIELD(arg0, s32 *, 0x38);
    if (var_v0 != 0) {
loop_1:
        var_v0 = FRunning__9JOBSCRIPT(arg0);
        if (var_v0 == 0) {
            var_v0 = M2C_FIELD(arg0, s32 *, 0x38);
            temp_a1 = M2C_FIELD(var_v0, s32 *, 0x18);
            M2C_FIELD(arg0, s32 *, 0x38) = temp_a1;
            if (temp_a1 != 0) {
                temp_v0 = M2C_FIELD(arg0, void **, 0xC);
                M2C_FIELD(temp_v0, void (**)(s32, s32), 0x7C)(arg0 + M2C_FIELD(temp_v0, s16 *, 0x78), temp_a1);
                var_v0 = M2C_FIELD(arg0, s32 *, 0x38);
                if (var_v0 != 0) {
                    goto loop_1;
                }
            }
        }
    }
    return var_v0;
}
