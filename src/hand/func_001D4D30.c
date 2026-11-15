/* class: VEHICLEATTACH, class 0x99 (SafeHouse vehicle.h VEHICLEATTACH defaults): initialise an attachment of a
 * vehicle - owner, aim angle/speed limits, flight time and limits, gravity -1750, enter range 200..400, exit range
 * 0..500 and fire interval 1..1.5 s. */
#include "h3_vehicle.h"

typedef struct VEHICLEATTACH {        /* field: SafeHouse port */
    /* 0x00 */ char pad0[0x10];
    /* 0x10 */ void *powner;
    /* 0x14 */ char pad14[0x40 - 0x14];
    /* 0x40 */ LM lmAngle;
    /* 0x48 */ LM lmSpeed;
    /* 0x50 */ qword flightTime;
    /* 0x60 */ LM lmFlight;
    /* 0x68 */ float gravity;
    /* 0x6c */ char pad6c[0x88 - 0x6C];
    /* 0x88 */ float sEnterMin;       /* enter range */
    /* 0x8c */ float sEnterMax;
    /* 0x90 */ int sExitMin;          /* exit range (min stored as integer 0) */
    /* 0x94 */ float sExitMax;
    /* 0x98 */ float dtFireMin;       /* fire interval */
    /* 0x9c */ float dtFireMax;
} VEHICLEATTACH;

extern LM D_002C2218;      /* SafeHouse default {-1.57, 1.57} */
extern LM D_002C2220;      /* SafeHouse default {250, 2500} */
extern qword D_002C2230;   /* SafeHouse default {0.5, 0.001, 0} */
extern LM D_002C2240;      /* SafeHouse default {0.5, 1.5} */

void func_001D4D30(VEHICLEATTACH *pattach, void *powner)
{
    pattach->powner = powner;
    pattach->lmAngle = D_002C2218;
    pattach->lmSpeed = D_002C2220;
    pattach->flightTime = D_002C2230;
    pattach->lmFlight = D_002C2240;
    pattach->gravity = -1750.0f;
    pattach->sEnterMin = 200.0f;
    pattach->sEnterMax = 400.0f;
    pattach->sExitMin = 0;
    pattach->sExitMax = 500.0f;
    pattach->dtFireMin = 1.0f;
    pattach->dtFireMax = 1.5f;
}
