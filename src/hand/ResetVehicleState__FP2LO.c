/* ResetVehicleState (the vehicles' post-load / placement): full health, the health display updated, the binding SM
 * snapped to its machine's first state, and mode 0. Layout: SafeHouse port (vehicle.cpp VEHICLE). */
struct SMS {
    /* 0x0 */ int oid;
};
struct SM {
    /* 0x00 */ char pad0[0x54];
    /* 0x54 */ struct SMS *asms;          /* the states */
};
struct SMA {
    /* 0x00 */ char pad0[0x24];
    /* 0x24 */ struct SM *psm;            /* the machine */
};
struct VEHICLE {
    /* 0x000 */ char pad0[0x55c];
    /* 0x55c */ int maxHealth;            /* field: SafeHouse port */
    /* 0x560 */ int health;               /* field: SafeHouse port */
    /* 0x564 */ char pad564[0x570 - 0x564];
    /* 0x570 */ struct SMA *binding;      /* field: SafeHouse port */
};
void UpdateVehicleHealth__FP7VEHICLE(struct VEHICLE *pvehicle);
void SnapSmaGoal__FP3SMA3OID(struct SMA *psma, int oid);
void SetVehicleMode__FP7VEHICLEi(struct VEHICLE *pvehicle, int mode);

// name: SafeHouse port (ResetVehicleState)
void ResetVehicleState__FP2LO(struct VEHICLE *pvehicle)
{
    struct SMA *psma;
    pvehicle->health = pvehicle->maxHealth;
    UpdateVehicleHealth__FP7VEHICLE(pvehicle);
    psma = pvehicle->binding;
    if (psma != 0)
        SnapSmaGoal__FP3SMA3OID(psma, psma->psm->asms->oid);
    SetVehicleMode__FP7VEHICLEi(pvehicle, 0);
}
