/* BestContact: of a vehicle wheel's contacts (+0x8, linked by +0xAC), the one with the largest positive support depth
 * (+0x90), or null. Layout: SafeHouse port (vehicle.cpp VEHICLEWHEEL, XP). */
struct XP {
    /* 0x00 */ char pad0[0x90];
    /* 0x90 */ float gDist;       /* field: SafeHouse port */
    /* 0x94 */ char pad94[0xac - 0x94];
    /* 0xac */ struct XP *pxpNext;   /* field: SafeHouse port */
};
struct VEHICLEWHEEL {
    /* 0x0 */ char pad0[8];
    /* 0x8 */ struct XP *contacts;   /* field: SafeHouse port */
};
extern float D_002A7834;   /* 0.0f */

// name: SafeHouse port (BestContact)
struct XP *BestContact__FP12VEHICLEWHEELi(struct VEHICLE *pvehicle, struct VEHICLEWHEEL *pwheel)
{
    struct XP *pxp;
    float gBest = D_002A7834;
    struct XP *pxpBest = 0;
    for (pxp = pwheel->contacts; pxp != 0; pxp = pxp->pxpNext) {
        if (gBest < pxp->gDist) {
            gBest = pxp->gDist;
            pxpBest = pxp;
        }
    }
    return pxpBest;
}
