#include "m2c_prelude.h"
M2C_UNK DeactivateTask__FP4TASK(s32);                         /* extern */
s32 FTaskCur__FP4TASK();                                /* extern */

void func_00163CE0(s32 arg0) {
    if (FTaskCur__FP4TASK() != 0) {
        DeactivateTask__FP4TASK(arg0);
    }
}
