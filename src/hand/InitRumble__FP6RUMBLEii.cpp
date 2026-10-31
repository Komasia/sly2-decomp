/* InitRumble (Sly 1 rumble.c): bind a rumble to a controller port/slot; a live rumble is stopped first. */
#include "rumble.h"

void InitRumble(RUMBLE *prumble, int nPort, int nSlot)
{
    if (prumble->rums == RUMS_Dead)
        SetRumbleRums(prumble, RUMS_Idle);
    else
        SetRumbleRums(prumble, RUMS_Stop);

    prumble->nPort = nPort;
    prumble->nSlot = nSlot;
}
