/* TriggerRumbleRumk (Sly 1 rumble.c): play one of the standard rumble patterns (s_mprumkrumpat[rumk]) for dt seconds. */
#include "rumble.h"
extern RUMPAT s_mprumkrumpat[];
void TriggerRumbleRumpat(RUMBLE *prumble, RUMPAT *prumpat, float dt);

void TriggerRumbleRumk(RUMBLE *prumble, RUMK rumk, float dt)
{
    TriggerRumbleRumpat(prumble, &s_mprumkrumpat[rumk], dt);
}
