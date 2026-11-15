/* class: VEHICLE (SafeHouse vehicle.h wheels, max 8): add a wheel with its node id, suspension travel and radius. */
#include "h3_vehicle.h"

struct VEHICLE {
    /* 0x000 */ char pad0[0x190];
    /* 0x190 */ unsigned int cwheel;                     /* field: SafeHouse port */
    /* 0x194 */ int pad194[3];
    /* 0x1a0 */ VEHICLEWHEEL awheel[CVEHICLEWHEEL_MAX];  /* field: SafeHouse port */
};

void func_001D4B48(struct VEHICLE *pvehicle, int id, LM *plmTravel, float radius)
{
    if (pvehicle->cwheel < CVEHICLEWHEEL_MAX) {
        VEHICLEWHEEL *pwheel = &pvehicle->awheel[pvehicle->cwheel++];
        pwheel->id = id;
        pwheel->radius = radius;
        pwheel->lmTravel = *plmTravel;
    }
}
