#include "m2c_prelude.h"
void *PloPlayerPo__FP2SW(M2C_UNK *);                     /* extern */
M2C_UNK SetZoneForced__FP2LOi(s32, M2C_UNK);                /* extern */
extern M2C_UNK g_sw;

// name: SafeHouse port (SetActorZone)
void SetActorZone__FP5ACTORP2LO(s32 arg0, s32 arg1) {
    s32 temp_a0;
    void *temp_v0;

    temp_v0 = PloPlayerPo__FP2SW(&g_sw);
    if (temp_v0 == arg0) {
        temp_a0 = M2C_FIELD(temp_v0, s32 *, 0x1024);
        if (temp_a0 != 0) {
            SetZoneForced__FP2LOi(temp_a0, 0);
        }
        M2C_FIELD(temp_v0, s32 *, 0x1024) = arg1;
        if (arg1 != 0) {
            SetZoneForced__FP2LOi(arg1, 1);
        }
    }
}
