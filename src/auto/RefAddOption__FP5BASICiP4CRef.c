#include "m2c_prelude.h"
M2C_UNK func_0012A980(s32, s32, s32, s32);          /* extern */
M2C_UNK func_00132B78(void *);                      /* extern */

s32 RefAddOption__FP5BASICiP4CRef(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    func_00132B78(arg1);
    func_0012A980(arg0, M2C_FIELD(arg1, s32 *, 4), arg2, arg3);
    return arg0;
}
