#include "m2c_prelude.h"
M2C_UNK SetVehicleMode__FP7VEHICLEi(void *, M2C_UNK);             /* extern */
M2C_UNK UpdateVehicleHealth__FP7VEHICLE();                            /* extern */
M2C_UNK SnapSmaGoal__FP3SMA3OID(void *, s32);                 /* extern */

// name: SafeHouse port (ResetVehicleState)
void ResetVehicleState__FP2LO(void *arg0) {
    void *temp_a0;

    M2C_FIELD(arg0, s32 *, 0x560) = (s32) M2C_FIELD(arg0, s32 *, 0x55C);
    UpdateVehicleHealth__FP7VEHICLE();
    temp_a0 = M2C_FIELD(arg0, void **, 0x570);
    if (temp_a0 != NULL) {
        SnapSmaGoal__FP3SMA3OID(temp_a0, *M2C_FIELD(M2C_FIELD(temp_a0, void **, 0x24), s32 **, 0x54));
    }
    SetVehicleMode__FP7VEHICLEi(arg0, 0);
}
