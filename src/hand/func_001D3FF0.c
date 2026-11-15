/* class: vehicle pickup, class 0x6C (SafeHouse vehiclebindings.cpp Collect: the deferred call posted by
 * VehicleContactMaterial 0x1D4050): a vehicle collects a pickup - the pickup's amount is added to the vehicle's
 * resource of the pickup's kind (clamped to its maximum) and the pickup becomes Collected. */
#include "h3_vehicle.h"

struct VEHICLE {
    /* 0x000 */ char pad0[0x574];
    /* 0x574 */ VEHICLERESOURCE aresource[3];       /* field: SafeHouse port */
};
struct VEHICLEPICKUP {
    /* 0x000 */ char pad0[0x150];
    /* 0x150 */ int state;                          /* field: SafeHouse port (VEHICLEPICKUPSTATE) */
    /* 0x154 */ float tState;                       /* field: SafeHouse port */
    /* 0x158 */ int kind;                           /* field: SafeHouse port (resource index) */
    /* 0x15c */ int amount;                         /* field: SafeHouse port */
};
void SetVehiclePickupState__FP2LOi(struct VEHICLEPICKUP *ppickup, int state);
static inline int Min(int a, int b) { return a < b ? a : b; }

void func_001D3FF0(struct VEHICLE *pvehicle, struct VEHICLEPICKUP *ppickup)
{
    if (ppickup->state != VEHICLEPICKUPSTATE_Collected) {
        VEHICLERESOURCE *presource = &pvehicle->aresource[ppickup->kind];
        int count = presource->count + ppickup->amount;
        presource->count = Min(presource->maximum, count);
        SetVehiclePickupState__FP2LOi(ppickup, VEHICLEPICKUPSTATE_Collected);
    }
}
