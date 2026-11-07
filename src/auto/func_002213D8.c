#include "m2c_prelude.h"
M2C_UNK func_001A6150();                            /* extern */
M2C_UNK UpdateZoneCamera__FP2LOi(s32, M2C_UNK);                /* extern */

// name: SafeHouse port (OnZoneUnregistered)
void OnZoneUnregistered__FP2LO(s32 arg0) {
    func_001A6150();
    UpdateZoneCamera__FP2LOi(arg0, 0);
}
