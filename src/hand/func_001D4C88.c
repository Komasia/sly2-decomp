/* UpdateVehicleHealth (SafeHouse vehicle.cpp, orig 0x1D4C88): show health / maxHealth (or 1 - that when the
 * display is inverted) on the vehicle's health widget. */
struct VEHICLE {
    /* 0x000 */ char pad0[0x55C];
    /* 0x55c */ int maxHealth;       /* field: SafeHouse port */
    /* 0x560 */ int health;          /* field: SafeHouse port */
    /* 0x564 */ int fInvertHealth;   /* field: SafeHouse port */
    /* 0x568 */ void *pwidgetHealth; /* field: SafeHouse port */
};
#define WID_VEHICLEHEALTH 0x34F
void func_00212E40(void *pwidget, int wid, float g);   /* set a widget's value */

// name: SafeHouse port (UpdateVehicleHealth)
void UpdateVehicleHealth__FP7VEHICLE(struct VEHICLE *pvehicle)
{
    if (pvehicle->pwidgetHealth) {
        float uHealth = (float)pvehicle->health / (float)pvehicle->maxHealth;
        if (pvehicle->fInvertHealth)
            uHealth = 1.0f - uHealth;
        func_00212E40(pvehicle->pwidgetHealth, WID_VEHICLEHEALTH, uHealth);
    }
}
