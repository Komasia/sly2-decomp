#include "m2c_prelude.h"
void Decref(M2C_UNK *) asm("Decref__4CRef");                   /* extern */

void func_00133000(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct {
        M2C_UNK m0;
    } fr;
    RefEval__FP5CPairP6CFrame((s32) (void *)&fr, arg1, arg2);
    if (arg3 != 0) {
        __as__4CRefRC4CRef(arg3, (s32) (void *)&fr);
    }
    Decref((void *)&fr);
}
