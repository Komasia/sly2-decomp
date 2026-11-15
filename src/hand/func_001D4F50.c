/* UpdateVehiclePickup (SafeHouse vehiclebindings.cpp UpdatePickup): the SO update; a landing pickup becomes Ready once
 * its position transform (+0x58) is at rest (mode 3). */
#include "h3_vehicle.h"

struct XF { char pad[0x98]; short mode; };   /* the position transform (SafeHouse PxfPos): mode at +0x98 */
struct VEHICLEPICKUP {
    /* 0x000 */ char pad0[0x58];
    /* 0x058 */ struct XF *pxfPos;
    /* 0x05c */ char pad5C[0x150 - 0x5C];
    /* 0x150 */ int state;            /* field: SafeHouse port (VEHICLEPICKUPSTATE) */
};
void UpdateSo__FP2SOf(struct VEHICLEPICKUP *ppickup);
void SetVehiclePickupState__FP2LOi(struct VEHICLEPICKUP *ppickup, int state);

// name: SafeHouse port (UpdateVehiclePickup)
void UpdateVehiclePickup__FP2LO(struct VEHICLEPICKUP *ppickup)
{
    UpdateSo__FP2SOf(ppickup);
    if (ppickup->state == VEHICLEPICKUPSTATE_Landing && ppickup->pxfPos->mode == 3)
        SetVehiclePickupState__FP2LOi(ppickup, VEHICLEPICKUPSTATE_Ready);
}
