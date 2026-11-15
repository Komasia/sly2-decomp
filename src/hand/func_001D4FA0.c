/* SetVehiclePickupState (SafeHouse vehiclebindings.cpp SetPickupState): change a pickup's state, remember when, and
 * seek its state machine binding to the state's machine state (D_002C2248[state]). */
#include "clock.h"
#include "h3_vehicle.h"

extern int D_002C2248[];              /* machine state per pickup state */
struct VEHICLEPICKUP {
    /* 0x000 */ char pad0[0x150];
    /* 0x150 */ int state;            /* field: SafeHouse port (VEHICLEPICKUPSTATE) */
    /* 0x154 */ float tState;         /* field: SafeHouse port */
    /* 0x158 */ char pad158[0x164 - 0x158];
    /* 0x164 */ void *psma;           /* field: SafeHouse port (binding) */
};
void SeekSma__FP3SMA3OID(void *psma, int oidState);

// name: SafeHouse port (SetVehiclePickupState)
void SetVehiclePickupState__FP2LOi(struct VEHICLEPICKUP *ppickup, int state)
{
    if (state == ppickup->state)
        return;
    ppickup->state = state;
    ppickup->tState = g_clock.t;
    if (ppickup->psma && state != VEHICLEPICKUPSTATE_Nil)
        SeekSma__FP3SMA3OID(ppickup->psma, D_002C2248[state]);
}
