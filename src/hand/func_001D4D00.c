/* class: VEHICLE (SafeHouse vehiclebindings.cpp: the splice method 0x1107B8): a resource's count. */
#include "h3_vehicle.h"

typedef struct VEHICLE {
    /* 0x000 */ char pad0[0x574];
    /* 0x574 */ VEHICLERESOURCE aresource[3];   /* field: SafeHouse port */
} VEHICLE;

int func_001D4D00(VEHICLE *pvehicle, int iresource)
{
    return pvehicle->aresource[iresource].count;
}
