#include "m2c_prelude.h"
extern M2C_UNK D_002A8A98;

M2C_UNK *func_00210CA8(void *arg0, s32 arg1) {
    M2C_UNK *var_v0;
    s32 temp_a2;
    s32 var_v1;
    void *var_a0;

    temp_a2 = M2C_FIELD(arg0, s32 *, 0);
    var_v1 = 0;
    if (temp_a2 > 0) {
        var_a0 = M2C_FIELD(arg0, void **, 4);
loop_2:
        var_v1 += 1;
        if ((arg1 != M2C_FIELD(var_a0, s32 *, 0)) || (var_v0 = M2C_FIELD(var_a0, M2C_UNK **, 4), (var_v0 == NULL))) {
            var_a0 += 8;
            if (var_v1 >= temp_a2) {
                goto block_5;
            }
            goto loop_2;
        }
    } else {
block_5:
        var_v0 = &D_002A8A98;
    }
    return var_v0;
}
