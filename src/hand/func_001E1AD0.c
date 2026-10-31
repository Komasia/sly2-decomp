/* func_001E1AD0: appends a RELAYCK_Unk59 command to the relay (oidShip, oidActor); fAsync from the caller. Called from the Splice binding func_0010A620. */
#include "relay.h"

void func_001E1AD0(RELAY *prelay, int oidShip, int oidActor, int fAsync)
{
    RELAYCMD *prelaycmd = func_001E01F8(prelay, RELAYCK_Unk59, fAsync);
    prelaycmd->u.unk59.oidShip = oidShip;
    prelaycmd->u.unk59.oidActor = oidActor;
}
