/* class: VEHICLE (SafeHouse vehiclebindings.cpp: the splice method 0x110838): set a resource's count. */
#include "h3_vehicle.h"

typedef struct VEHICLE {
    /* 0x000 */ char pad0[0x574];
    /* 0x574 */ VEHICLERESOURCE aresource[3];   /* field: SafeHouse port */
} VEHICLE;

void func_001D4D18(VEHICLE *pvehicle, int iresource, int count)
{
    pvehicle->aresource[iresource].count = count;
}
