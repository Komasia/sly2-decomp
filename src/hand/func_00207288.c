#include "stepguard.h"
extern struct { float t; float dt; } g_clock;
extern float D_002C3D40[3];   /* how long modes 8 / 13, 34 / 37 and 21 last */
void SetGuardMode__FP5GUARDi(struct GUARD *pguard, int nMode);
/* UpdateGuardTimedMode (0x207288): the timed guard modes end (back to -1) once their time (D_002C3D40) is up. */
// name: SafeHouse port (UpdateGuardTimedMode)
void UpdateGuardTimedMode__FP5GUARD(struct GUARD *pguard)
{
    switch (pguard->nMode) {
    case 8:
    case 13:
        if (g_clock.t - pguard->tMode > D_002C3D40[0])
            SetGuardMode__FP5GUARDi(pguard, -1);
        break;
    case 34:
    case 37:
        if (g_clock.t - pguard->tMode > D_002C3D40[1])
            SetGuardMode__FP5GUARDi(pguard, -1);
        break;
    case 21:
        if (g_clock.t - pguard->tMode > D_002C3D40[2])
            SetGuardMode__FP5GUARDi(pguard, -1);
        break;
    }
}
