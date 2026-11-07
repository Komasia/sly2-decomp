#include "m2c_prelude.h"
f32 GFromCrvS__FP3CRVf();                                /* extern */
M2C_UNK EvalCrv__FP3CRVfP6VECTORT2(s32, s32, s32, f32);          /* extern */

void func_001E6F10(s32 arg0, s32 arg1, s32 arg2) {
    EvalCrv__FP3CRVfP6VECTORT2(arg0, arg1, arg2, GFromCrvS__FP3CRVf());
}
