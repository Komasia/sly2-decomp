#include "m2c_prelude.h"
void Decref(M2C_UNK *) asm("Decref__4CRef");                   /* extern */

void func_00132CC8(s32 arg0, s32 arg1, s32 arg2) {
    struct {
        M2C_UNK m0;
        char pad0[0xC];
        M2C_UNK m10;
    } fr;
    func_00129330((s32) (void *)&fr, arg2);
    RefEnsureOption__FP5BASICiP4CRef((s32) &fr.m10, arg0, arg1, (s32) (void *)&fr);
    Decref(&fr.m10);
    Decref((void *)&fr);
}
