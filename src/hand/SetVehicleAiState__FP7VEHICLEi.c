/* SetVehicleAiState: change a vehicle's AI state (+0x188) and remember when (+0x18C, the game clock). */
struct VEHICLE {
    /* 0x000 */ char pad0[0x188];
    /* 0x188 */ int aiState;     /* field: SafeHouse port */
    /* 0x18c */ float aiTime;    /* field: SafeHouse port */
};
extern float g_clock;            /* CLOCK +0x0: t */

// name: SafeHouse port (SetVehicleAiState)
void SetVehicleAiState__FP7VEHICLEi(struct VEHICLE *pvehicle, int aiState)
{
    if (aiState != pvehicle->aiState) {
        pvehicle->aiState = aiState;
        pvehicle->aiTime = g_clock;
    }
}
