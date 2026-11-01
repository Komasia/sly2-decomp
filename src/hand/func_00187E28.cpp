/* TriggerJoyRumbleRumk (Sly 1 joy.c): starts a rumble pattern, if rumble is enabled and the pad is a ready shock
 * controller. Sly 2 embeds the RUMBLE in the JOY. */
#include "joy.h"

void TriggerRumbleRumk(RUMBLE *prumble, RUMK rumk, float dt);

void TriggerJoyRumbleRumk(JOY *pjoy, RUMK rumk, float dt)
{
    if (pjoy->fRumbleEnabled && pjoy->joyk > JOYK_Analog && pjoy->joys == JOYS_Ready) {
        TriggerRumbleRumk(&pjoy->rumble, rumk, dt);
    }
}
