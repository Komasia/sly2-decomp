/* class: vehicle pickup, class 0x6C (SafeHouse vehicle.h PostLoadVehiclePickup, orig 0x1D4EC8): after the base
 * post-load, bind the pickup's state machine (+0x160) to it and start in state Landing. */
#include "h3_vehicle.h"

struct VEHICLEPICKUP {
    /* 0x000 */ char pad0[0x160];
    /* 0x160 */ void *psm;            /* field: SafeHouse port (machine) */
    /* 0x164 */ void *psma;           /* field: SafeHouse port (binding) */
};
void func_001F36A8(struct VEHICLEPICKUP *ppickup);   /* the base post-load */
void ReplaceSmaHandle__FP2SMi3OIDiPP3SMA(void *psm, struct VEHICLEPICKUP *ppickup, int oid, int n, void **ppsma);
void SetVehiclePickupState__FP2LOi(struct VEHICLEPICKUP *ppickup, int state);

void PostLoadVehiclePickup__FP2LO(struct VEHICLEPICKUP *ppickup)
{
    func_001F36A8(ppickup);
    ReplaceSmaHandle__FP2SMi3OIDiPP3SMA(ppickup->psm, ppickup, -1, 0, &ppickup->psma);
    SetVehiclePickupState__FP2LOi(ppickup, VEHICLEPICKUPSTATE_Landing);
}
