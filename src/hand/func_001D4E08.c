/* class: VEHICLEATTACH (SafeHouse vehicle.h FVehicleAttachmentReady, orig 0x1D4E08): the owner vehicle has enough of
 * the attachment's resource to pay its cost. */
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

// name: SafeHouse port (vehicle.h FVehicleAttachmentReady, orig 0x1D4E08; suggested by h3)
int FVehicleAttachmentReady__FP13VEHICLEATTACH(struct VEHICLEATTACH *pattach)
{
    return pattach->powner->aresource[pattach->iresource].count >= pattach->cost;
}
