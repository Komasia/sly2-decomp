/* SetRumbleRums (Sly 1 rumble.c): change the rumble state. Rumble starts the pattern's first motor settings; Stop /
 * Kill stop the motors and hold them stopped for 4 frames of real time (dtRumins = 4 * g_clock.dtReal). */
#include "rumble.h"
#include "clock.h"
extern "C" int scePadSetActDirect(int, int, unsigned char *) asm("scePadSetActDirect");
void StopRumbleActuators(RUMBLE *prumble);
void SetRumbleRums(RUMBLE *prumble, RUMS rums)
{
    if (rums == prumble->rums)
        return;
    unsigned char abShockDirect[6];
    switch (rums)
    {
    case RUMS_Rumble:
        abShockDirect[0] = prumble->prumpat->arumins[0].fHighSpeedMotor;
        abShockDirect[1] = prumble->prumpat->arumins[0].bLowSpeedMotor;
        scePadSetActDirect(prumble->nPort, prumble->nSlot, abShockDirect);
        prumble->rums = rums;
        break;
    case RUMS_Stop:
    case RUMS_Kill:
        StopRumbleActuators(prumble);
        prumble->dtRumins = g_clock.dtReal * 4.0f;
    case RUMS_Dead:
    case RUMS_Idle:
    default:
        prumble->rums = rums;
        break;
    }
}
