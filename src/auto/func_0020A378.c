#include "m2c_prelude.h"
s32 FIsBasicDerivedFrom__FP5BASIC3CID(s32, M2C_UNK);                    /* extern */
s32 FGuardSurprised__FP5GUARDP2LOUl(s32, s32, s32);                   /* extern */
extern s32 D_002DD648;

// name: SafeHouse port (FGuardLaunchAllowed)
s32 FGuardLaunchAllowed__FP5GUARDP2LOi(s32 arg0, s32 arg1, s32 arg2) {
    if ((FIsBasicDerivedFrom__FP5BASIC3CID(arg1, 0x36) != 0) && (FIsBasicDerivedFrom__FP5BASIC3CID(arg0, 0x3A) == 0) && (FIsBasicDerivedFrom__FP5BASIC3CID(arg0, 0x3D) == 0) && (arg0 != D_002DD648)) {
        return 1;
    }
    return FGuardSurprised__FP5GUARDP2LOUl(arg0, arg1, arg2);
}
