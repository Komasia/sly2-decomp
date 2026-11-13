#include "m2c_prelude.h"
s32 func_00116A58(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_a2;
    void *temp_t0;

    temp_t0 = M2C_FIELD(arg0, void **, 0);
    temp_a2 = M2C_FIELD(arg0, s32 *, 4);
    return M2C_FIELD(temp_t0, s32 (**)(s32, s32, s32), 0xC)(arg0 + M2C_FIELD(temp_t0, s16 *, 8), arg2, (~temp_a2 == 0) ? arg3 : temp_a2);
}
