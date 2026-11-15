/* class: VEHICLE (SafeHouse vehicle.h resources): set a resource's maximum and priority. */
#include "h3_vehicle.h"

struct VEHICLE {
    /* 0x000 */ char pad0[0x574];
    /* 0x574 */ VEHICLERESOURCE aresource[3];   /* field: SafeHouse port */
};

void func_001D4CE0(struct VEHICLE *pvehicle, int iresource, float priority, int maximum)
{
    VEHICLERESOURCE *presource = &pvehicle->aresource[iresource];
    presource->maximum = maximum;
    presource->priority = priority;
}
