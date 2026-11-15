/* class: VEHICLE (SafeHouse vehicle.h: attachments at +0x4F8/+0x4FC): find the vehicle's attachment with the given index
 * (+0x14 of the attachment); NULL if none. */
#include "h3_vehicle.h"

struct VEHICLEATTACH {
    /* 0x00 */ char pad0[0x14];
    /* 0x14 */ int index;             /* field: SafeHouse port */
};
struct VEHICLE {
    /* 0x000 */ char pad0[0x4F8];
    /* 0x4f8 */ int cattach;          /* field: SafeHouse port */
    /* 0x4fc */ struct VEHICLEATTACH *apattach[CVEHICLEATTACH_MAX];
};

struct VEHICLEATTACH *func_001D3FA8(struct VEHICLE *pvehicle, int index)
{
    int iattach;
    for (iattach = 0; iattach < pvehicle->cattach; iattach++) {
        struct VEHICLEATTACH *pattach = pvehicle->apattach[iattach];
        if (pattach->index == index)
            return pattach;
    }
    return 0;
}
