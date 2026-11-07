#include "m2c_prelude.h"
s32 NDamageStatus__FP5ACTOR(s32);                             /* extern */
s32 func_001C41B8();                                /* extern */

// name: SafeHouse port (FActorTakesCharm)
s32 FActorTakesCharm__FP5ACTOR(s32 arg0) {
    if (func_001C41B8() == 0) {
        return 0;
    }
    return NDamageStatus__FP5ACTOR(arg0 + 0xDF0) != 2;
}
