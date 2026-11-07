#include "m2c_prelude.h"
M2C_UNK ResetHackSoBase__FP2LO();                            /* extern */
M2C_UNK SetShipState__FP2LOi(s32, M2C_UNK);                /* extern */
M2C_UNK UpdateHackHud__FP2LO(s32);                         /* extern */
s32 func_001C40F8(s32);                             /* extern */

// name: SafeHouse port (ResetShip)
void ResetShip__FP2LO(s32 arg0) {
    ResetHackSoBase__FP2LO();
    if (func_001C40F8(arg0) != 0) {
        SetShipState__FP2LOi(arg0, 1);
    } else {
        SetShipState__FP2LOi(arg0, 0);
    }
    UpdateHackHud__FP2LO(arg0);
}
