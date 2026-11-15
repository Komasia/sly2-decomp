/* UpdateRumble (Sly 1 rumble.c): per frame (real time), step the rumble pattern while rumbling, and keep the
 * motors stopped for the stop delay before going Idle (Stop) or Dead (Kill). */
#include "rumble.h"
#include "clock.h"
extern "C" int scePadSetActDirect(int, int, byte *) asm("scePadSetActDirect");
void StopRumbleActuators(RUMBLE *prumble);
void UpdateRumble(RUMBLE *prumble)
{
    byte abShockDirect[6];
    float dtReal = g_clock.dtReal;

    switch (prumble->rums) {
    case RUMS_Rumble:
        if (prumble->dtRumble > 0.0f) {
            prumble->dtRumins -= dtReal;
            if (prumble->dtRumins <= 0.0f) {
                if (++prumble->irumins >= prumble->prumpat->crumins)
                    prumble->irumins = 0;
                abShockDirect[0] = prumble->prumpat->arumins[prumble->irumins].fHighSpeedMotor;
                abShockDirect[1] = prumble->prumpat->arumins[prumble->irumins].bLowSpeedMotor;
                scePadSetActDirect(prumble->nPort, prumble->nSlot, abShockDirect);
                prumble->dtRumins = prumble->prumpat->arumins[prumble->irumins].dt;
            }
            prumble->dtRumble -= dtReal;
        } else {
            SetRumbleRums(prumble, RUMS_Stop);
        }
        break;
    case RUMS_Stop:
    case RUMS_Kill:
        if (prumble->dtRumins > 0.0f) {
            StopRumbleActuators(prumble);
            prumble->dtRumins -= dtReal;
        } else {
            SetRumbleRums(prumble, (prumble->rums == RUMS_Stop) ? RUMS_Idle : RUMS_Dead);
        }
        break;
    default:
        return;
    }
}
