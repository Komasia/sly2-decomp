/* TriggerRumbleRumpat (Sly 1 rumble.c): play a vibration pattern for dt seconds, if vibration is enabled. */
#include "rumble.h"

extern "C" int FVibrationEnabled(void) asm("FVibrationEnabled__Fv");   /* vibration enabled in the options (Sly 1: RumbleUnknown3(g_pgsCur)) */

void TriggerRumbleRumpat(RUMBLE *prumble, RUMPAT *prumpat, float dt)
{
    if (prumble->rums != RUMS_Dead && prumpat->crumins > 0 && FVibrationEnabled() != 0)
    {
        prumble->dtRumble = dt;
        prumble->prumpat = prumpat;
        prumble->irumins = 0;
        prumble->dtRumins = prumpat->arumins[0].dt;
        prumble->rums = RUMS_Nil;
        SetRumbleRums(prumble, RUMS_Rumble);
    }
}
