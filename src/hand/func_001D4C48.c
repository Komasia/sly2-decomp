/* class: VEHICLE (SafeHouse vehicle.h sides, max 4): add a steering side with its node id and limits. */
#include "h3_vehicle.h"

struct VEHICLE {
    /* 0x000 */ char pad0[0x4A4];
    /* 0x4a4 */ unsigned int cside;                    /* field: SafeHouse port */
    /* 0x4a8 */ VEHICLESIDE aside[CVEHICLESIDE_MAX];   /* field: SafeHouse port */
};

void func_001D4C48(struct VEHICLE *pvehicle, int id, LM *plmLimits)
{
    if (pvehicle->cside < CVEHICLESIDE_MAX) {
        VEHICLESIDE *pside = &pvehicle->aside[pvehicle->cside++];
        pside->id = id;
        pside->lmLimits = *plmLimits;
    }
}
