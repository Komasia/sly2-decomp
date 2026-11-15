/* VehicleBounds (SafeHouse vehicle.cpp, orig 0x1D4178): the SO bounds, then grow them by each wheel's lower position
 * (converted to world space) with the wheel radius. */
#include "h3_vehicle.h"

struct VEHICLE {
    /* 0x000 */ char pad0[0x190];
    /* 0x190 */ int cwheel;                              /* field: SafeHouse port */
    /* 0x194 */ int pad194[3];
    /* 0x1a0 */ VEHICLEWHEEL awheel[CVEHICLEWHEEL_MAX];  /* field: SafeHouse port */
};
void UpdateSoBounds__FP2SO(struct VEHICLE *pvehicle);
qword ConvertPos__FP2LOT0G9VU_VECTOR(struct VEHICLE *ploFrom, int ploTo, qword pos);
void func_001F5480(struct VEHICLE *pvehicle, qword pos, float sRadius);   /* grow the bounds by a sphere */

// name: SafeHouse port (VehicleBounds)
void VehicleBounds__FP3ALO(struct VEHICLE *pvehicle)
{
    int iwheel;
    UpdateSoBounds__FP2SO(pvehicle);
    for (iwheel = 0; iwheel < pvehicle->cwheel; iwheel++) {
        VEHICLEWHEEL *pwheel = &pvehicle->awheel[iwheel];
        func_001F5480(pvehicle, ConvertPos__FP2LOT0G9VU_VECTOR(pvehicle, 0, pwheel->lower), pwheel->radius);
    }
}
