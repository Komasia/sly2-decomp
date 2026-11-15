/* class: VEHICLEATTACH (SafeHouse vehicle.h): pay the attachment's cost from the owner vehicle's resource (not below
 * zero). */
#include "h3_vehicle.h"

struct VEHICLE {
    /* 0x000 */ char pad0[0x574];
    /* 0x574 */ VEHICLERESOURCE aresource[3];   /* field: SafeHouse port */
};
struct VEHICLEATTACH {                          /* field: SafeHouse port */
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ struct VEHICLE *powner;
    /* 0x14 */ char pad14[0x6C - 0x14];
    /* 0x6c */ int iresource;
    /* 0x70 */ int cost;
};

void func_001D4E30(struct VEHICLEATTACH *pattach)
{
    VEHICLERESOURCE *presource = &pattach->powner->aresource[pattach->iresource];
    int count = presource->count - pattach->cost;
    if (count < 0)
        count = 0;
    presource->count = count;
}
