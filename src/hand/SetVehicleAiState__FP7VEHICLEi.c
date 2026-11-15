/* SetVehicleAiState: change a vehicle's AI state (+0x188) and remember when (+0x18C, the game clock). */
#include "clock.h"

struct VEHICLE {
    /* 0x000 */ char pad0[0x188];
    /* 0x188 */ int aiState;     /* field: SafeHouse port */
    /* 0x18c */ float aiTime;    /* field: SafeHouse port */
};

// name: SafeHouse port (SetVehicleAiState)
void SetVehicleAiState__FP7VEHICLEi(struct VEHICLE *pvehicle, int aiState)
{
    if (aiState != pvehicle->aiState) {
        pvehicle->aiState = aiState;
        pvehicle->aiTime = g_clock.t;
    }
}
