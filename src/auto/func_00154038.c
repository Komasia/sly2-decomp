#include "m2c_prelude.h"
void func_00154038(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;

    temp_v0 = PdetentryFind__FP8DETECTORi(arg0, arg1);
    if (temp_v0 != 0) {
        SetDetentryState__FP8DETECTORP8DETENTRYi(arg0, temp_v0, arg2);
    }
}
