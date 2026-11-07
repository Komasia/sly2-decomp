#include "m2c_prelude.h"
M2C_UNK DeactivateJob__FP3JOB(s32);                         /* extern */
s32 FJobCur__FP3JOB();                                /* extern */

void func_00162908(s32 arg0) {
    if (FJobCur__FP3JOB() != 0) {
        DeactivateJob__FP3JOB(arg0);
    }
}
