#include "m2c_prelude.h"
void func_001421A0(s32 arg0, s32 arg1) {
    SetActorInteractObject__FP5ACTORi(arg0, 0);
    if (arg1 != 0) {
        AttachReachObject__FP5REACHP2LO(arg0 + 0x900, arg1);
        return;
    }
    ReleaseReachObject__FP5REACH(arg0 + 0x900);
}
